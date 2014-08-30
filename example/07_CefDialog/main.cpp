#include "CefDialog.hpp"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);

    CefDialog duiFrame;
    duiFrame.Create(NULL, _T("CefDialog"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE, 0, 0, 500, 800);
    duiFrame.ShowModal();
    return 0;
}