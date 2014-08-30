// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "SimpleHandler.hpp"

#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

namespace {

    SimpleHandler* g_instance = NULL;

}  // namespace
int SimpleHandler::browser_count_ = 0;
SimpleHandler::SimpleHandler()
: is_closing_(false), browser_id_(0) {
    DCHECK(!g_instance);
    g_instance = this;
}

SimpleHandler::~SimpleHandler() {
    g_instance = NULL;
}

// static
SimpleHandler* SimpleHandler::GetInstance() {
    return g_instance;
}

void SimpleHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    if (!GetBrowser()) {
        base::AutoLock lock_scope(lock_);
        // We need to keep the main child window, but not popup windows
        browser_ = browser;
        browser_id_ = browser->GetIdentifier();
    }
    else if (browser->IsPopup()) {
        // Add to the list of popup browsers.
        popup_browsers_.push_back(browser);

        // Give focus to the popup browser. Perform asynchronously because the
        // parent window may attempt to keep focus after launching the popup.
        CefPostTask(TID_UI,
            base::Bind(&CefBrowserHost::SetFocus, browser->GetHost().get(), true));
    }
    browser_count_++;
}

bool SimpleHandler::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    // Closing the main window requires special handling. See the DoClose()
    // documentation in the CEF header for a detailed destription of this
    // process.
    if (GetBrowserId() == browser->GetIdentifier()) {
        base::AutoLock lock_scope(lock_);
        // Set a flag to indicate that the window close should be allowed.
        is_closing_ = true;
    }

    // Allow the close. For windowed browsers this will result in the OS close
    // event being sent.
    return false;
}

void SimpleHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    if (GetBrowserId() == browser->GetIdentifier()) {
        {
            base::AutoLock lock_scope(lock_);
            // Free the browser pointer so that the browser can be destroyed
            browser_ = NULL;
        }
    }
    else if (browser->IsPopup()) {
        // Remove from the browser popup list.
        BrowserList::iterator bit = popup_browsers_.begin();
        for (; bit != popup_browsers_.end(); ++bit) {
            if ((*bit)->IsSame(browser)) {
                popup_browsers_.erase(bit);
                break;
            }
        }
    }

    if (--browser_count_ == 0) {
        // Quit the application message loop.
        CefQuitMessageLoop();
        //PostQuitMessage(1);
    }
}

void SimpleHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    ErrorCode errorCode,
    const CefString& errorText,
    const CefString& failedUrl) {
    CEF_REQUIRE_UI_THREAD();

    // Don't display an error for downloaded files.
    if (errorCode == ERR_ABORTED)
        return;

    // Display a load error message.
    std::stringstream ss;
    ss << "<html><body bgcolor=\"white\">"
        "<h2>Failed to load URL " << std::string(failedUrl) <<
        " with error " << std::string(errorText) << " (" << errorCode <<
        ").</h2></body></html>";
    frame->LoadString(ss.str(), failedUrl);
}

void SimpleHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
    const CefString& title) {
    CEF_REQUIRE_UI_THREAD();

    CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
    SetWindowText(hwnd, std::wstring(title).c_str());
}