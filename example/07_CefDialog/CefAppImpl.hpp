// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef GALLERY_08_CEFAPPIMPL_HPP
#define GALLERY_08_CEFAPPIMPL_HPP

#include "include/cef_app.h"

class CefAppImpl : public CefApp,
    public CefBrowserProcessHandler {
public:
    CefAppImpl();

    // CefApp methods:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
        OVERRIDE{ return this; }

    // CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE;

private:
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(CefAppImpl);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
