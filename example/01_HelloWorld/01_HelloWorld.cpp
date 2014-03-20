#define UILIB_API

#include <UIlib.h>
using namespace DuiLib;
#pragma comment(lib, "../../Build/Debug/Lib/DuiLib.lib")
class CDuiFrameWnd : public CWindowWnd, public INotifyUI
{
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }
	virtual void    Notify(TNotifyUI& msg) {}

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;

		if (uMsg == WM_CREATE)
		{
			CControlUI *pWnd = new CButtonUI;
			pWnd->SetText(_T("Hello World"));   // ��������
			pWnd->SetBkColor(0xFF00FF00);       // ���ñ���ɫ

			m_PaintManager.Init(m_hWnd);
			m_PaintManager.AttachDialog(pWnd);
			return lRes;
		}
		if (uMsg == WM_GETMINMAXINFO) {
			LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
			lpMMI->ptMaxTrackSize.x = 800;// rcWork.GetWidth();
			lpMMI->ptMaxTrackSize.y = 800;// rcWork.GetHeight();
			lpMMI->ptMaxSize.x = 800;
			lpMMI->ptMaxSize.y = 800;
			OutputDebugStringA("WM_GETMINMAXINFO\n");
			return 0;
		}

		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}

protected:
	CPaintManagerUI m_PaintManager;
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.ShowModal();
	return 0;
}