#include "CefDialog.hpp"
#include "CefBrowserWrapper.hpp"

LRESULT CefDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lRes = 0;

    if (uMsg == WM_CREATE) {
        CVerticalLayoutUI* layout = new CVerticalLayoutUI;
        layout->SetBkColor(0xFFFFFFFF);
        layout->SetChildPadding(10);
        layout->SetInset(RECT{ 2, 2, 2, 2 });
        {
            auto button = new CButtonUI;
            button->SetBkColor(0xFFFF0000);
            button->SetFixedHeight(40);
            layout->Add(button);
        }
        {
            auto browser = new CefBrowserWrapper(m_hWnd);
            layout->Add(browser);
        }
        {
            auto edit = new CRichEditUI;
            edit->SetMinHeight(50);
            layout->Add(edit);
        }
        m_PaintManager.Init(m_hWnd);
        m_PaintManager.AttachDialog(layout);
        // m_PaintManager.SetShowUpdateRect(true);
        return lRes;
    }
    if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) {
        return lRes;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

void CefDialog::Notify(TNotifyUI& msg) {
}