// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef GALLERY_08_CEFCLIENTIMPL_HPP
#define GALLERY_08_CEFCLIENTIMPL_HPP
#include "include/base/cef_lock.h"
#include "include/cef_client.h"

#include <list>
#include <map>
class CefClientImpl : public CefClient,
    public CefDisplayHandler,
    public CefLifeSpanHandler,
    public CefLoadHandler {
public:
    CefClientImpl();
    ~CefClientImpl();

    // Provide access to the single global instance of this object.
    static CefClientImpl* GetInstance();

    // CefClient methods:
    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE{
        return this;
    }
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE{
        return this;
    }
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE{
        return this;
    }

    // CefDisplayHandler methods:
    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
        const CefString& title) OVERRIDE;

    // CefLifeSpanHandler methods:
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

    // CefLoadHandler methods:
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        ErrorCode errorCode,
        const CefString& errorText,
        const CefString& failedUrl) OVERRIDE;

    bool IsClosing() const { return is_closing_; }

    CefRefPtr<CefBrowser> GetBrowser(HWND hwnd) {
        if (browsers_.find(hwnd) != browsers_.end()) {
            return browsers_[hwnd];
        }
        return NULL;
    }

private:
    // List of existing browser windows. Only accessed on the CEF UI thread.
    typedef std::map<HWND, CefRefPtr<CefBrowser> > BrowserMap;
    BrowserMap browsers_;
    bool is_closing_;

    mutable base::Lock lock_;
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(CefClientImpl);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
