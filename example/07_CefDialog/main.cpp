#include "CefDialog.hpp"
#undef GetNextSibling
#undef GetFirstChild
#include "CefAppImpl.hpp"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

    // Provide CEF with command-line arguments.
    CefMainArgs main_args(hInstance);

    // SimpleApp implements application-level callbacks. It will create the first
    // browser instance in OnContextInitialized() after CEF has initialized.
    CefRefPtr<CefAppImpl> app(new CefAppImpl);


    // CEF applications have multiple sub-processes (render, plugin, GPU, etc)
    // that share the same executable. This function checks the command-line and,
    // if this is a sub-process, executes the appropriate logic.
    int exit_code = CefExecuteProcess(main_args, app.get(), NULL);
    if (exit_code >= 0) {
        // The sub-process has completed so return here.
        return exit_code;
    }

    // Specify CEF global settings here.
    CefSettings settings;

#if !CEF_ENABLE_SANDBOX
    settings.no_sandbox = true;
#endif

    settings.multi_threaded_message_loop = false;
    // Initialize CEF.
    CefInitialize(main_args, settings, app.get(), NULL);


    CPaintManagerUI::SetInstance(hInstance);

    CefDialog d;
    d.Create(NULL, _T("CefDialog"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE, 0, 0, 500, 800);
    d.ShowWindow();

    CefRunMessageLoop();
    // CPaintManagerUI::MessageLoop();
    CPaintManagerUI::Term();

    // TODO: Cef can't be shutdown successfully.
    CefShutdown();
    return 0;
}