#ifndef GALLERY_MAINWINDOW_HPP
#define GALLERY_MAINWINDOW_HPP
#pragma once
#include <UIlib.h>
using namespace DuiLib;

#include "NativeWindow.hpp"

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
};

#endif