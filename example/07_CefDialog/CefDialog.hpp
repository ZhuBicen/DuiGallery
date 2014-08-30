#ifndef GALLERY_08_CEFDIALOG_HPP
#define GALLERY_08_CEFDIALOG_HPP
#include <UIlib.h>
using namespace DuiLib;
class CefDialog : public CWindowWnd, public INotifyUI
{
public:
    virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }
    virtual void    Notify(TNotifyUI& msg);
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    CPaintManagerUI m_PaintManager;
};

#endif