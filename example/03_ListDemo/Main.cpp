/*
* Code By Tojen (qq:342269237)
* 界面设计图片资源80%原创，布局完全原创,学习作品，不好请拍砖
*/
#include <objbase.h>
#include <zmouse.h>
#include <exdisp.h>
#include <comdef.h>
#include <vector>
#include <sstream>

#include "..\DuiLib\UIlib.h"

using namespace DuiLib;

#define WM_ADDLISTITEM WM_USER + 50
/*
* 存放第二列数据
*/
std::vector<std::string> domain;
/*
* 存放第三列数据
*/
std::vector<std::string> desc;
/*
*  线程函数中传入的结构体变量，使用线程为了使界面线程立即返回，防止卡住，你们懂得。
*/
struct Prama
{
    HWND hWnd;
    CListUI* pList;
    CButtonUI* pSearch;
    CDuiString tDomain;
};

#include "MenuWnd.h"

class ListMainForm : public CWindowWnd, public INotifyUI, public IListCallbackUI
{
public:
    ListMainForm() {
    };

    LPCTSTR GetWindowClassName() const 
    { 
        return _T("ScanMainForm"); 
    };

    UINT GetClassStyle() const
    { 
        return CS_DBLCLKS; 
    };

    void OnFinalMessage(HWND /*hWnd*/) 
    { 
        delete this;
    };

    void Init() 
    {
        m_pSearch = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn")));
    }
    static DWORD WINAPI Search(LPVOID lpParameter)
    {
        try
        {
            struct Prama* prama = (struct Prama *)lpParameter;
            CListUI* pList = prama->pList;
            CButtonUI* pSearch = prama->pSearch;
            CDuiString tDomain = prama->tDomain;
            //-------------------------------------
            /*
            * 添加数据循环
            */
            for(int i=0; i<100; i++)
            {
                std::stringstream ss;
                ss << "www." << i << ".com";
                domain.push_back(ss.str());
                ss.clear();
                ss << "it's " << i;
                desc.push_back(ss.str());
                CListTextElementUI* pListElement = new CListTextElementUI;
                pListElement->SetTag(i);
                if (pListElement != NULL)
                {
                    ::PostMessage(prama->hWnd, WM_ADDLISTITEM, 0L, (LPARAM)pListElement);
                }
                /*
                *	Sleep 为了展示添加的动态效果，故放慢了添加速度，同时可以看到添加过程中界面仍然可以响应
                */
                ::Sleep(100);
            }
            //------------------------------------------
            delete prama;

            pSearch->SetEnabled(true);
            return 0;
        }
        catch(...)
        {
            return 0;
        }
    }
    void OnSearch()
    {
        struct Prama *prama = new Prama;

        CListUI* pList = static_cast<CListUI*>(m_pm.FindControl(_T("domainlist")));
        CEditUI* pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("input")));
        pEdit->SetEnabled(false);
        CDuiString input = pEdit->GetText();
        m_pSearch->SetEnabled(false);
        pList->RemoveAll();
        domain.empty();
        domain.resize(0);
        desc.empty();
        desc.resize(0);
        DWORD dwThreadID = 0;
        pList->SetTextCallback(this);//[1]

        prama->hWnd = GetHWND();
        prama->pList = pList;
        prama->pSearch = m_pSearch;
        prama->tDomain = input;

        HANDLE hThread = CreateThread(NULL,0,&ListMainForm::Search, (LPVOID)prama,  0,&dwThreadID);
    }
    /*
    * 关键的回调函数，IListCallbackUI 中的一个虚函数，渲染时候会调用,在[1]中设置了回调对象
    */
    LPCTSTR GetItemText(CControlUI* pControl, int iIndex, int iSubItem)
    {
        TCHAR szBuf[MAX_PATH] = {0};
        switch (iSubItem)
        {
        case 0:
            _stprintf(szBuf, _T("%d"), iIndex);
            break;
        case 1:
            {
#ifdef _UNICODE		
            int iLen = domain[iIndex].length();
            LPWSTR lpText = new WCHAR[iLen + 1];
            ::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
            ::MultiByteToWideChar(CP_ACP, 0, domain[iIndex].c_str(), -1, (LPWSTR)lpText, iLen) ;
            _stprintf(szBuf, lpText);
            delete[] lpText;
#else
            _stprintf(szBuf, domain[iIndex].c_str());
#endif
            }
            break;
        case 2:
            {
#ifdef _UNICODE		
            int iLen = desc[iIndex].length();
            LPWSTR lpText = new WCHAR[iLen + 1];
            ::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
            ::MultiByteToWideChar(CP_ACP, 0, desc[iIndex].c_str(), -1, (LPWSTR)lpText, iLen) ;
            _stprintf(szBuf, lpText);
            delete[] lpText;
#else
            _stprintf(szBuf, desc[iIndex].c_str());
#endif
            }
            break;
        }
        pControl->SetUserData(szBuf);
        return pControl->GetUserData();
    }

    void Notify(TNotifyUI& msg)
    {
		if (msg.sType == _T("windowinit"))
		{
			// OnPrepare(msg);
		}
        else if( msg.sType == _T("click") ) 
        {
            if(msg.pSender == m_pSearch)
            {
                OnSearch();
            }
        }
        else if(msg.sType==_T("setfocus"))
        {
        }
        else if( msg.sType == _T("itemclick") ) 
        {
        }
        else if( msg.sType == _T("itemactivate") ) 
        {
            int iIndex = msg.pSender->GetTag();
            CDuiString sMessage = _T("Click: ");;
#ifdef _UNICODE		
            int iLen = domain[iIndex].length();
            LPWSTR lpText = new WCHAR[iLen + 1];
            ::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
            ::MultiByteToWideChar(CP_ACP, 0, domain[iIndex].c_str(), -1, (LPWSTR)lpText, iLen) ;
            sMessage += lpText;
            delete[] lpText;
#else
            sMessage += domain[iIndex].c_str();

#endif
            ::MessageBox(NULL, sMessage.GetData(), _T("提示(by tojen)"), MB_OK);
        }
        else if(msg.sType == _T("menu")) 
        {
            if( msg.pSender->GetName() != _T("domainlist") ) return;
            CMenuWnd* pMenu = new CMenuWnd();
            if( pMenu == NULL ) { return; }
            POINT pt = {msg.ptMouse.x, msg.ptMouse.y};
            ::ClientToScreen(*this, &pt);
            pMenu->Init(msg.pSender, pt);
        }
        else if( msg.sType == _T("menu_Delete") ) {
            CListUI* pList = static_cast<CListUI*>(msg.pSender);
            int nSel = pList->GetCurSel();
            if( nSel < 0 ) return;
            pList->RemoveAt(nSel);
            domain.erase(domain.begin() + nSel);
            desc.erase(desc.begin() + nSel);   
        }
    }

    LRESULT OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        CListTextElementUI* pListElement = (CListTextElementUI*)lParam;
        CListUI* pList = static_cast<CListUI*>(m_pm.FindControl(_T("domainlist")));
        if( pList ) pList->Add(pListElement);
        return 0;
    }

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
        ::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
        m_pm.Init(m_hWnd);
        // m_pm.SetTransparent(100);
        CDialogBuilder builder;
        CControlUI* pRoot = builder.Create(_T("skin.xml"), (UINT)0, NULL, &m_pm);
        ASSERT(pRoot && "Failed to parse XML");
        m_pm.AttachDialog(pRoot);
        m_pm.AddNotifier(this);
        Init();
        return 0;
    }

    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        bHandled = FALSE;
        return 0;
    }

    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        ::PostQuitMessage(0L);
        bHandled = FALSE;
        return 0;
    }

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lRes = 0;
        BOOL bHandled = TRUE;
        switch( uMsg ) {
            case WM_ADDLISTITEM:   lRes = OnAddListItem(uMsg, wParam, lParam, bHandled); break;
            case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
            case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
            default:
                bHandled = FALSE;
        }
        if( bHandled ) return lRes;
        if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
        return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
    }
public:
    CPaintManagerUI m_pm;

private:
    CButtonUI* m_pSearch;

    //...
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
    ListMainForm* pFrame = new ListMainForm();
    if( pFrame == NULL ) return 0;
    pFrame->Create(NULL, _T("ListDemo"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW , 0, 0, 600, 320);
    pFrame->CenterWindow();
    ::ShowWindow(*pFrame, SW_SHOW);

    CPaintManagerUI::MessageLoop();

	return 0;
}