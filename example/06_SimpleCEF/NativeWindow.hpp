#ifndef GALLERY_NATIVE_WINDOW_HPP
#define GALLERY_NATIVE_WINDOW_HPP
#include <UIlib.h>
using namespace DuiLib;


class CNativeButtonWrapper : public CControlUI
{
public:
    CNativeButtonWrapper() : m_hWnd(NULL){}

    virtual void SetInternVisible(bool bVisible = true)
    {
        __super::SetInternVisible(bVisible);
        ::ShowWindow(m_hWnd, bVisible);
    }

    virtual void SetPos(RECT rc);

    BOOL Attach(HWND hWndNew)
    {
        if (!::IsWindow(hWndNew)) {
            return FALSE;
        }

        m_hWnd = hWndNew;
        return TRUE;
    }

    HWND Detach()
    {
        HWND hWnd = m_hWnd;
        m_hWnd = NULL;
        return hWnd;
    }

private:
    HWND m_hWnd;
};

#endif