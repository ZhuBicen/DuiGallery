#include <UIlib.h>
using namespace DuiLib;
#include "MainWindow.hpp"
#include "NativeWindow.hpp"
#undef GetNextSibling
#include <windows.h>
#include "SimpleApp.hpp"
#include "include/cef_sandbox_win.h"


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    void* sandbox_info = NULL;

#if CEF_ENABLE_SANDBOX
    // Manage the life span of the sandbox information object. This is necessary
    // for sandbox support on Windows. See cef_sandbox_win.h for complete details.
    CefScopedSandboxInfo scoped_sandbox;
    sandbox_info = scoped_sandbox.sandbox_info();
#endif

    // Provide CEF with command-line arguments.
    CefMainArgs main_args(hInstance);

    // SimpleApp implements application-level callbacks. It will create the first
    // browser instance in OnContextInitialized() after CEF has initialized.
    CefRefPtr<SimpleApp> app(new SimpleApp);


    // CEF applications have multiple sub-processes (render, plugin, GPU, etc)
    // that share the same executable. This function checks the command-line and,
    // if this is a sub-process, executes the appropriate logic.
    int exit_code = CefExecuteProcess(main_args, app.get(), sandbox_info);
    if (exit_code >= 0) {
        // The sub-process has completed so return here.
        return exit_code;
    }

    // Specify CEF global settings here.
    CefSettings settings;

#if !CEF_ENABLE_SANDBOX
    settings.no_sandbox = true;
#endif

    settings.multi_threaded_message_loop = true;
    // Initialize CEF.
    CefInitialize(main_args, settings, app.get(), sandbox_info);


    CPaintManagerUI::SetInstance(hInstance);

    CDuiFrameWnd duiFrame;
    duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    duiFrame.ShowWindow();

    // Run the CEF message loop. This will block until CefQuitMessageLoop() is
    // called.

    // CefRunMessageLoop();

    CPaintManagerUI::MessageLoop();
    CPaintManagerUI::Term();

    // Shut down CEF.
    CefShutdown();

    return 0;
}