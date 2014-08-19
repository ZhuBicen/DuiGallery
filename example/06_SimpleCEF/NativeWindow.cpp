#include "NativeWindow.hpp"

#include <string>

#undef GetNextSibling
#include "SimpleHandler.hpp"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"
SimpleHandler* g_sh = nullptr;
void CNativeButtonWrapper::SetPos(RECT rc) {
    static bool first = true;
    
    __super::SetPos(rc);
    if (g_sh != nullptr) {
        HWND brower_wnd = g_sh->GetBrowser()->GetHost()->GetWindowHandle();
        ::SetWindowPos(brower_wnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
    }
    if (!first) {
        return;
    }
    first = false;
    CefWindowInfo window_info;

    window_info.SetAsChild(parent_window_, rc);

    g_sh = new SimpleHandler();
    // SimpleHandler implements browser-level callbacks.
    CefRefPtr<SimpleHandler> handler(g_sh);

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