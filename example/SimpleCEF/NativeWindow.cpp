#include "NativeWindow.hpp"

#include <string>

#undef GetNextSibling
#include "cefsimple/simple_handler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"
void CNativeButtonWrapper::SetPos(RECT rc) {
    __super::SetPos(rc);
    ::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
    CefWindowInfo window_info;

    window_info.SetAsChild(m_hWnd, RECT{ 0, 0, rc.right - rc.left, rc.bottom - rc.top });


    // SimpleHandler implements browser-level callbacks.
    CefRefPtr<SimpleHandler> handler(new SimpleHandler());

    // Specify CEF browser settings here.
    CefBrowserSettings browser_settings;

    std::string url;

    // Check if a "--url=" value was provided via the command-line. If so, use
    // that instead of the default URL.
    CefRefPtr<CefCommandLine> command_line =
        CefCommandLine::GetGlobalCommandLine();
    url = command_line->GetSwitchValue("url");
    if (url.empty())
        url = "http://www.163.com";

    // Create the first browser window.
    CefBrowserHost::CreateBrowser(window_info, handler.get(), url, browser_settings, NULL);

}