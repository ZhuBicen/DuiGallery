#include <UIlib.h>
using namespace DuiLib;
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
            CVerticalLayoutUI* layout = new CVerticalLayoutUI;
            layout->SetBkColor(0xFFFFFFFF);

            {
                auto button = new CButtonUI;
                button->SetBorderSize(8);
                button->SetBorderColor(0xFF1122cc);
                button->SetPadding(RECT{ 10, 10, 10, 0 });
                button->SetFixedHeight(40);
                button->SetText(_T("Hello Button1!"));
                button->SetFocusBorderColor(0x11FF33);
                button->SetBorderRound(SIZE{ 5, 5 });
                layout->Add(button);
            }
            {
                auto button = new CLabelUI;
                button->SetBorderSize(2);
                button->SetBorderColor(0xFF1122cc);
                button->SetFixedHeight(40);
                button->SetPadding(RECT{ 10, 10, 10, 10 });
                button->SetText(_T("    Hello Label!"));
                button->SetBkColor(0xFF33FFF0);
                layout->Add(button);
            }
			m_PaintManager.Init(m_hWnd);
			m_PaintManager.AttachDialog(layout);
            // m_PaintManager.SetShowUpdateRect(true);
			return lRes;
		}
		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}
private:
	CPaintManagerUI m_PaintManager;
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("Hello DuiGallery"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.ShowModal();
	return 0;
}