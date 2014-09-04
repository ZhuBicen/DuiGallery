#include "CefClientImpl.hpp"

#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

namespace {

    CefClientImpl* g_instance = NULL;

}  // namespace
// Handle messages in the browser process.
class Handler : public CefMessageRouterBrowserSide::Handler {
public:
    Handler() {}

    // Called due to cefQuery execution in binding.html.
    virtual bool OnQuery(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        int64 query_id,
        const CefString& request,
        bool persistent,
        CefRefPtr<Callback> callback) OVERRIDE{
        //// Only handle messages from the test URL.
        //const std::string& url = frame->GetURL();
        //if (url.find(kTestUrl) != 0)
        //    return false;

        //const std::string& message_name = request;
        //if (message_name.find(kTestMessageName) == 0) {
        //    // Reverse the string and return.
        //    std::string result = message_name.substr(sizeof(kTestMessageName));
        //    std::reverse(result.begin(), result.end());
        //    callback->Success(result);
        //    return true;
        //}

        return false;
    }
};
CefClientImpl::CefClientImpl()
: is_closing_(false) {
    DCHECK(!g_instance);
    g_instance = this;
}

CefClientImpl::~CefClientImpl() {
    g_instance = NULL;
}

CefClientImpl* CefClientImpl::GetInstance() {
    return g_instance;
}

void CefClientImpl::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    if (!message_router_) {
        // Create the browser-side router for query handling.
        CefMessageRouterConfig config;
        message_router_ = CefMessageRouterBrowserSide::Create(config);

        // Register handlers with the router.
        message_router_->AddHandler(new Handler(), false);
    }
    browsers_[::GetParent(browser->GetHost()->GetWindowHandle())] = browser;
    //std::stringstream ss;
    //ss << "<html><body bgcolor=\"white\"><h1>Chatting with xxx</h1>Text:<pre>" << "XXXYY" <<
    //    "</pre></body></html>";
    //browser->GetMainFrame()->LoadString(ss.str(), "http://tests/gettext");
}

bool CefClientImpl::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    is_closing_ = true;
    return false;
}

void CefClientImpl::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
}

void CefClientImpl::OnLoadError(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    ErrorCode errorCode,
    const CefString& errorText,
    const CefString& failedUrl) {
    CEF_REQUIRE_UI_THREAD();


}

void CefClientImpl::OnTitleChange(CefRefPtr<CefBrowser> browser,
    const CefString& title) {
    CEF_REQUIRE_UI_THREAD();
}