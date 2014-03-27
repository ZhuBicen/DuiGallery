#include <UIlib.h>
using namespace DuiLib;

class CDuiFrameWnd : public WindowImplBase {
public:
	virtual LPCTSTR    GetWindowClassName() const   { return _T("DUIMainFrame"); }
	virtual CDuiString GetSkinFile()                { return _T("02_TitleBar.xml"); }
	virtual CDuiString GetSkinFolder()              { return _T(""); }
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		BOOL bZoomed = ::IsZoomed(m_hWnd);
		LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		if (::IsZoomed(m_hWnd) != bZoomed)
		{
			if (!bZoomed)
			{
				CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
				if (pControl) pControl->SetVisible(false);
				pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
				if (pControl) pControl->SetVisible(true);
			}
			else
			{
				CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
				if (pControl) pControl->SetVisible(true);
				pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
				if (pControl) pControl->SetVisible(false);
			}
		}
		return 0;
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();
	return 0;
}