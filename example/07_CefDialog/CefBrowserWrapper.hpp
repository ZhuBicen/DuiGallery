#ifndef GALLERY_08_CEFBROWSER_HPP
#define GALLERY_08_CEFBROWSER_HPP
#include <UIlib.h>
using namespace DuiLib;
#undef GetNextSibling
#undef GetFirstChild
#include "include/cef_base.h"
#include "include/cef_browser.h"

class CefBrowserWrapper : public CControlUI
{
public:
    CefBrowserWrapper(HWND parent) :parent_window_(parent) {}
    virtual void SetPos(RECT rc);
private:
    HWND parent_window_;
    CefRefPtr<CefBrowser> browser_;
};

#endif