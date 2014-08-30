#include "CefDialog.hpp"
#include "CefBrowserWrapper.hpp"
#include "CefClientImpl.hpp"

extern CefClientImpl* g_sh;
LRESULT CefDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lRes = 0;

    if (uMsg == WM_CREATE) {
        CVerticalLayoutUI* layout = new CVerticalLayoutUI;
        layout->SetBkColor(0xFFFFFFFF);
        layout->SetChildPadding(10);
        layout->SetInset(RECT{ 2, 2, 2, 2 });
        {
            auto browser = new CefBrowserWrapper(m_hWnd);
            layout->Add(browser);
        }
        {
            m_edit = new CRichEditUI;
            m_edit->SetMinHeight(50);
            m_edit->SetBorderColor(0xFF112233);
            m_edit->SetBorderSize(3);
            m_edit->SetText(L"How are you doing?");
            layout->Add(m_edit);
        }
        {
            auto button = new CButtonUI;
            button->SetName(L"sendmessage");
            button->SetBkColor(0xFFFF0000);
            button->SetFixedHeight(40);
            button->SetText(L"Send Message");
            layout->Add(button);
        }
        m_PaintManager.Init(m_hWnd);
        m_PaintManager.AddNotifier(this);
        m_PaintManager.AttachDialog(layout);
        // m_PaintManager.SetShowUpdateRect(true);
        return lRes;
    }
    if (uMsg == WM_CLOSE) {
        if (!g_sh->IsClosing()) {
            g_sh->GetBrowser(m_hWnd)->GetHost()->CloseBrowser(true);
            return 0;
        }
        ::PostQuitMessage(0);
    }
    if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) {
        return lRes;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

void CefDialog::Notify(TNotifyUI& msg) {
    if (msg.sType == L"click") {
        if (msg.pSender->GetName() == L"sendmessage")
        {

            std::wstring js = 
                L"var msgs = document.getElementById(\"messages\");"
                L"var msg = document.createElement(\"li\");"
                L"var newDate = new Date();"
                L"msg.appendChild(document.createTextNode(newDate.getTime() + \": @M@\"));"
                L"msgs.appendChild(msg);"
                L"window.scrollTo(0,document.body.scrollHeight);";

            js.replace(js.find(L"@M@"), 3, m_edit->GetText().GetData());
            g_sh->GetBrowser(m_hWnd)->GetMainFrame()->ExecuteJavaScript(
                js,
                "appendMessageJs",
                1);
        }
    }
}