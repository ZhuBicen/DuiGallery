#pragma once
#include <UIlib.h>
#include "NativeWindow.hpp"
using namespace DuiLib;

class CDuiFrameWnd : public WindowImplBase {
public:
    virtual LPCTSTR    GetWindowClassName() const   { return _T("DUIMainFrame"); }
    virtual CDuiString GetSkinFile()                { return _T("SimpleCEF.xml"); }
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
            CNativeButtonWrapper  *pUI = new CNativeButtonWrapper;
            HWND    hWnd = CreateWindow(_T("STATIC"), _T("This is Win32 Native Button!!!"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, m_PaintManager.GetPaintWindow(), NULL, NULL, NULL);
            pUI->Attach(hWnd);

            //// 上面用的是win32的按钮，下面这段用MFC的按钮
            //CButton *pBtn = new CButton;    // 记得释放内存
            //pBtn->Create(_T("MFC"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, CRect(0, 0, 0, 0), CWnd::FromHandle(m_PaintManager.GetPaintWindow()), 0);
            //pUI->Attach(*pBtn);            
            return pUI;
        }

        return NULL;
    }
};