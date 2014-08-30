#include "CefBrowserWrapper.hpp"
#include <string>
#undef GetNextSibling
#include "CefClientImpl.hpp"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"
CefClientImpl* g_sh = nullptr;
void CefBrowserWrapper::SetPos(RECT rc) {

    __super::SetPos(rc);
    if (g_sh == nullptr) {
        g_sh = new CefClientImpl;
    }
    if (g_sh->GetBrowser(parent_window_) != nullptr) {
        HWND brower_wnd = g_sh->GetBrowser(parent_window_)->GetHost()->GetWindowHandle();
        ::SetWindowPos(brower_wnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
        return;
    }

    CefWindowInfo window_info;

    window_info.SetAsChild(parent_window_, rc);

    // SimpleHandler implements browser-level callbacks.
    CefRefPtr<CefClientImpl> handler(g_sh);

    // Specify CEF browser settings here.
    CefBrowserSettings browser_settings;

    std::string url;

    // Check if a "--url=" value was provided via the command-line. If so, use
    // that instead of the default URL.
    CefRefPtr<CefCommandLine> command_line =
        CefCommandLine::GetGlobalCommandLine();
    url = command_line->GetSwitchValue("url");
    if (url.empty())
        url = "http://www.baidu.com";

    // Create the first browser window.
    CefBrowserHost::CreateBrowser(window_info, handler.get(), url, browser_settings, NULL);

}