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
            layout->SetBkColor (0xFFFFFFFF);
            layout->SetChildPadding(10);
            layout->SetInset(RECT{ 10, 10, 10, 10 });
            {
                auto button = new CButtonUI;
                button->SetBkColor(0xFFFF0000);
                button->SetFixedHeight(40);
                layout->Add(button);
            }
            {
                auto button = new CButtonUI;
                button->SetFixedHeight(40);
                button->SetBkColor(0xFFFF0000);
                button->SetBkColor2(0xFF00FF00);
                layout->Add(button);
            }
            {
                auto button = new CButtonUI;
                button->SetFixedHeight(40);
                button->SetBkColor(0xFFFF0000);
                button->SetBkColor2(0xFF00FF00);
                button->SetBkColor3(0xFF0000FF);
                layout->Add(button);
            }
            {
                auto button = new CButtonUI;
                button->SetBorderSize(2);
                button->SetBorderColor(0xFFFF0000);
                button->SetFixedHeight(40);
                button->SetBkColor(0xFFD6DBE9);
                layout->Add(button);
            }
            {
                auto button = new CButtonUI;
                button->SetBorderSize(5);
                button->SetBorderRound(SIZE{ 5, 5 });
                button->SetBorderColor(0xFF00FF00);
                button->SetFocusBorderColor(0xFFFF0000);
                button->SetBkColor(0xFFD6DBE9);
                button->SetFixedHeight(40);
                layout->Add(button);
            }
            {
                auto button = new CButtonUI;
                button->SetBkColor(0xFFD6DBE9);
                button->SetLeftBorderSize(1);
                button->SetTopBorderSize(2);
                button->SetRightBorderSize(3);
                button->SetBottomBorderSize(24);
                button->SetBorderStyle(2);
                button->SetBorderColor(0xFFFF0000);
                button->SetFocusBorderColor(0xFF00FF00);
                button->SetFixedHeight(40);
                // button->SetFixedWidth(200);
                button->SetPadding(RECT{ 10, 10, 10, 10 });
                button->SetText(_T("Button"));
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
	duiFrame.Create(NULL, _T("Hello DuiGallery"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE, 0, 0, 500, 800);
	duiFrame.ShowModal();
	return 0;
}