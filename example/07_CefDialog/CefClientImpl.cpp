#include "CefClientImpl.hpp"

#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

namespace {

    CefClientImpl* g_instance = NULL;

}  // namespace
CefClientImpl::CefClientImpl()
: is_closing_(false) {
    DCHECK(!g_instance);
    g_instance = this;
}

CefClientImpl::~CefClientImpl() {
    g_instance = NULL;
}

CefClientImpl* CefClientImpl::GetInstance() {
    return g_instance;
}

void CefClientImpl::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    browsers_[::GetParent(browser->GetHost()->GetWindowHandle())] = browser;
    //std::stringstream ss;
    //ss << "<html><body bgcolor=\"white\"><h1>Chatting with xxx</h1>Text:<pre>" << "XXXYY" <<
    //    "</pre></body></html>";
    //browser->GetMainFrame()->LoadString(ss.str(), "http://tests/gettext");
}

bool CefClientImpl::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    is_closing_ = true;
    return false;
}

void CefClientImpl::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
}

void CefClientImpl::OnLoadError(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    ErrorCode errorCode,
    const CefString& errorText,
    const CefString& failedUrl) {
    CEF_REQUIRE_UI_THREAD();


}

void CefClientImpl::OnTitleChange(CefRefPtr<CefBrowser> browser,
    const CefString& title) {
    CEF_REQUIRE_UI_THREAD();
}