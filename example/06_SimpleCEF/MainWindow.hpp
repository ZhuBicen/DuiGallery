#ifndef GALLERY_MAINWINDOW_HPP
#define GALLERY_MAINWINDOW_HPP
#pragma once
#undef GetNextSibling
#include <sstream>
#include <UIlib.h>
#include "SimpleHandler.hpp"
using namespace DuiLib;

#include "NativeWindow.hpp"
extern SimpleHandler* g_sh;
class CDuiFrameWnd : public WindowImplBase {
public:
    virtual LPCTSTR    GetWindowClassName() const   { return _T("DUIMainFrame"); }
    virtual CDuiString GetSkinFile()                { return _T("06_SimpleCEF.xml"); }
    virtual CDuiString GetSkinFolder()              { return _T(""); }
    virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BOOL bZoomed = ::IsZoomed(m_hWnd);
        LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
        if (::IsZoomed(m_hWnd) != bZoomed) {
            if (!bZoomed) {
                CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
                if (pControl) pControl->SetVisible(false);
                pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
                if (pControl) pControl->SetVisible(true);
            }
            else {
                CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
                if (pControl) pControl->SetVisible(true);
                pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
                if (pControl) pControl->SetVisible(false);
            }
        }
        return 0;
    }
    virtual CControlUI* CreateControl(LPCTSTR pstrClassName)
    {
        if (_tcsicmp(pstrClassName, _T("NativeButton")) == 0) {
            CNativeButtonWrapper  *pUI = new CNativeButtonWrapper(m_hWnd);
            return pUI;
        }

        return NULL;
    }
    LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        std::ostringstream oss;

        
        if (!g_sh->IsClosing()) {
            bHandled = true;
            CefRefPtr<CefBrowser> browser = g_sh->GetBrowser();
            if (browser.get()) {
                // Notify the browser window that we would like to close it. This
                // will result in a call to ClientHandler::DoClose() if the
                // JavaScript 'onbeforeunload' event handler allows it.
                browser->GetHost()->CloseBrowser(false);

                oss << __FUNCTION__ << " trying to close all browsers.\n";
                OutputDebugStringA(oss.str().c_str());
                return 0;
            }
        }
        bHandled = false;
        oss << __FUNCTION__ << " permit to close.\n";
        OutputDebugStringA(oss.str().c_str());
        // ::PostQuitMessage(0);
        // ::DestroyWindow(m_hWnd);
        return 1;
    }
};

#endif