#ifndef GALLERY_NATIVE_WINDOW_HPP
#define GALLERY_NATIVE_WINDOW_HPP
#include <UIlib.h>
using namespace DuiLib;


class CNativeButtonWrapper : public CControlUI
{
public:
    CNativeButtonWrapper(HWND parent):parent_window_(parent) {}
    virtual void SetPos(RECT rc);
private:
    HWND parent_window_;
};

#endif