#include "BaiLuInputMethodClass.hpp"
#include "GlobalValues.hpp"
#include "BaiLuInputProcessorProfileAgent.hpp"
#include "Log.hpp"
CBaiLuInputMethodClass::CBaiLuInputMethodClass()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::CBaiLuInputMethodClass");
    m_refCount = 0;
    m_pKeyEventSink=nullptr;
    m_pThreadMgrEventSink=nullptr;
    m_pTextEditSink=nullptr;
    m_pCompositionSink=nullptr;
    m_pDispalyAttributeProvider=nullptr;
    m_pThreadFocusSink=nullptr;
    m_pFunctionProvider=nullptr;
    m_pBoarderLayout=nullptr;
    m_pNotifySink=nullptr;

    {
        CBaiLuKeyEventSink* pSink = nullptr;
        HRESULT hr = CBaiLuKeyEventSink::CreateInstance(&pSink);
        if ( SUCCEEDED(hr) && 
             (nullptr != pSink) )
        {
            m_pKeyEventSink = pSink;
            m_pKeyEventSink->AddRef();
            pSink = nullptr;
        }
        else
        {
            LogUtil::LogError(__FILE__, __LINE__);
        }
    }
    {
        CBaiLuThreadMgrEventSink* pSink = nullptr;
        HRESULT hr = CBaiLuThreadMgrEventSink::CreateInstance(&pSink);
        if (nullptr != pSink)
        {
            m_pThreadMgrEventSink = pSink;
            m_pThreadMgrEventSink->AddRef();
            pSink = nullptr;
        }
        else
        {
            LogUtil::LogError(__FILE__, __LINE__);
        }
    }
    {
        CBaiLuTextEditSink* pSink = nullptr;
        HRESULT hr = CBaiLuTextEditSink::CreateInstance(&pSink);
        if (nullptr != pSink)
        {
            m_pTextEditSink = pSink;
            m_pTextEditSink->AddRef();
            pSink = nullptr;
        }
        else
        {
            LogUtil::LogError(__FILE__, __LINE__);
        }
    }
    {
        CBaiLuCompositionSink* pSink = nullptr;
        HRESULT hr = CBaiLuCompositionSink::CreateInstance(&pSink);
        if (nullptr != pSink)
        {
            m_pCompositionSink = pSink;
            m_pCompositionSink->AddRef();
            pSink = nullptr;
        }
        else
        {
            LogUtil::LogError(__FILE__, __LINE__);
        }
    }

    {
        CBaiLuDisplayAttributeProvider* pProvider = nullptr;
        HRESULT hr = CBaiLuDisplayAttributeProvider::CreateInstance(&pProvider);
        if (nullptr != pProvider)
        {
            m_pDispalyAttributeProvider = pProvider;
            m_pDispalyAttributeProvider->AddRef();
            pProvider = nullptr;
        }
        else
        {
            LogUtil::LogError(__FILE__, __LINE__);
        }
    }
    {
        CBaiLuThreadFocusSink* pSink = nullptr;
        HRESULT hr = CBaiLuThreadFocusSink::CreateInstance(&pSink);
        if (nullptr != pSink)
        { 
            m_pThreadFocusSink = pSink;
            this->m_pThreadFocusSink->AddRef();
            pSink = nullptr;
        }
        else
        {
            LogUtil::LogError(__FILE__, __LINE__);
        }
    }

    {
        CBaiLuFunctionProvider* pSink = nullptr;
        HRESULT hr = CBaiLuFunctionProvider::CreateInstance(&pSink);
        if (nullptr != pSink)
        {
            m_pFunctionProvider = pSink;
            this->m_pFunctionProvider->AddRef();
            pSink = nullptr;
        }
        else
        {
            LogUtil::LogError(__FILE__, __LINE__);
        }
    }
    {
        CBaiLuFnGetPreferredTouchKeyBoardLayout* pLayout = nullptr;
        HRESULT hr = CBaiLuFnGetPreferredTouchKeyBoardLayout::CreateInstance(&pLayout);
        if (nullptr != pLayout)
        {
            m_pBoarderLayout = pLayout;
            m_pBoarderLayout->AddRef();
            pLayout = nullptr;
        }
        else
        {
            LogUtil::LogError(__FILE__, __LINE__);
        }

    }
    {
        CBaiLuActiveLanguageProfileNotifySink* pSink = nullptr;
        HRESULT hr = CBaiLuActiveLanguageProfileNotifySink::CreateInstance(&pSink);
        if (nullptr != pSink)
        {
            m_pNotifySink = pSink;
            m_pNotifySink->AddRef();
            pSink = nullptr;
        }
        else
        {
            LogUtil::LogError(__FILE__, __LINE__);
        }
    }
    AddRef();
}

CBaiLuInputMethodClass::~CBaiLuInputMethodClass()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::~CBaiLuInputMethodClass");
}

// IUnknown
STDMETHODIMP CBaiLuInputMethodClass::QueryInterface(REFIID riid, _Outptr_ void** ppvObj)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::QueryInterface Begin");
    if (ppvObj == NULL)
    {
        LogUtil::LogError(__FILE__, __LINE__);
        return E_INVALIDARG;
    }

    *ppvObj = NULL;

    if (IsEqualIID(riid, IID_IUnknown) ||
        IsEqualIID(riid, IID_ITfTextInputProcessor))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        AddRef();
        *ppvObj = (ITfTextInputProcessor*)this;
    }
    else if (IsEqualIID(riid, IID_ITfTextInputProcessorEx))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        AddRef();
        *ppvObj = (ITfTextInputProcessorEx*)this;
    }
    else if (IsEqualIID(riid, IID_ITfKeyEventSink))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        if (nullptr != this->m_pKeyEventSink)
        {
            m_pKeyEventSink->AddRef();
            *ppvObj = (m_pKeyEventSink);
        }
    }
    else if (IsEqualIID(riid, IID_ITfThreadMgrEventSink))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        if (nullptr != this->m_pThreadMgrEventSink)
        {
            this->m_pThreadMgrEventSink->AddRef();
            *ppvObj = this->m_pThreadMgrEventSink;
        }
    }
    else if (IsEqualIID(riid, IID_ITfTextEditSink))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        if (nullptr != this->m_pTextEditSink)
        {
            this->m_pTextEditSink->AddRef();
            *ppvObj = this->m_pTextEditSink;
        }
    }

    else if (IsEqualIID(riid, IID_ITfActiveLanguageProfileNotifySink))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        if (nullptr != m_pNotifySink)
        {
            m_pNotifySink->AddRef();
            *ppvObj = m_pNotifySink;
        }
    }
    else if (IsEqualIID(riid, IID_ITfCompositionSink))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        if (nullptr != this->m_pCompositionSink)
        {
            m_pCompositionSink->AddRef();
            *ppvObj =m_pCompositionSink;
        }
    }
    else if (IsEqualIID(riid, IID_ITfDisplayAttributeProvider))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        if (nullptr != this->m_pDispalyAttributeProvider)
        {
            *ppvObj = m_pDispalyAttributeProvider;
            m_pDispalyAttributeProvider->AddRef();
        }
    }
    else if (IsEqualIID(riid, IID_ITfThreadFocusSink))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        if (nullptr != m_pThreadFocusSink)
        {
            *ppvObj = m_pThreadFocusSink;
            m_pThreadFocusSink->AddRef();
        }
    }
    else if (IsEqualIID(riid, IID_ITfFunctionProvider))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        if (nullptr != m_pFunctionProvider)
        {
            *ppvObj = m_pFunctionProvider;
            m_pFunctionProvider->AddRef();
        }
    }
    else if (IsEqualIID(riid, IID_ITfFunction))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        if (nullptr != m_pBoarderLayout)
        {
            *ppvObj = m_pBoarderLayout;
            m_pBoarderLayout->AddRef();
        }
    }
    else if (IsEqualIID(riid, IID_ITfFnGetPreferredTouchKeyboardLayout))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        if (nullptr != m_pBoarderLayout)
        {
            *ppvObj = m_pBoarderLayout;
            m_pBoarderLayout->AddRef();
        }
    }
    else
    {
        GUID gid = riid;
        LogUtil::LogInfo("UnKnown IID %x %x %x",gid.Data1,gid.Data2,gid.Data3);
    }

    if (*ppvObj != NULL)
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        return S_OK;
    }
    HRESULT hr = E_NOINTERFACE;
    LogUtil::LogInfo("CBaiLuInputMethodClass::QueryInterface End");
    return hr;
}

STDMETHODIMP_(ULONG) CBaiLuInputMethodClass::AddRef(void)
{
    m_refCount++;
    LogUtil::LogInfo("CBaiLuInputMethodClass::AddRef %d",m_refCount);
    return 0;
}

STDMETHODIMP_(ULONG) CBaiLuInputMethodClass::Release(void)
{
    m_refCount--;
    LogUtil::LogInfo("CBaiLuInputMethodClass::Release %d",m_refCount);
    return 0;
}

// ITfTextInputProcessor
STDMETHODIMP CBaiLuInputMethodClass::Activate(ITfThreadMgr* pThreadMgr, TfClientId tfClientId)  {
    return ActivateEx(pThreadMgr, tfClientId, 0);
}
// ITfTextInputProcessorEx
STDMETHODIMP CBaiLuInputMethodClass::ActivateEx(ITfThreadMgr* pThreadMgr, TfClientId tfClientId, DWORD dwFlags)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::ActivateEx");
    this->m_pThreadMgr = pThreadMgr;
    this->m_tfClientId = tfClientId;
    this->m_dwFlags = dwFlags;
    {
        if (!InitThreadMgrEventSink())
        {
            LogUtil::LogError(__FILE__, __LINE__);
            goto ExitError;
        }
        if (!InitKeyEventSink())
        {
            LogUtil::LogError(__FILE__, __LINE__);
            goto ExitError;
        }
        if (!InitActiveLanguageProfileNotifySink())
        {
            LogUtil::LogError(__FILE__, __LINE__);
            goto ExitError;
        }
        if (!InitThreadFocusSink())
        {
            goto ExitError;
        }
        if (!InitDisplayAttributeGuidAtomSink())
        {
            goto ExitError;
        }
        if (!InitFunctionProviderSink())
        {
            goto ExitError;
        }
        if (!InitTextProcessorEngineSink())
        {
            goto ExitError;
        }
        return S_OK;

ExitError:
        Deactivate();
        return E_FAIL;
    }
    return S_OK;
}
STDMETHODIMP CBaiLuInputMethodClass::Deactivate()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::Deactivate");
    UnInitThreadMgrEventSink();
    UnInitKeyEventSink();
    UnInitThreadFocusSink();
    UnInitActiveLanguageProfileNotifySink();
    UnInitDisplayAttributeGuidAtomSink();
    UnInitFunctionProviderSink();
    UnInitTextProcessorEngineSink();
    return S_OK;
}




CBaiLuInputMethodClass* CBaiLuInputMethodClass::m_pInstance = nullptr;
CBaiLuInputMethodClass* CBaiLuInputMethodClass::GetSingleInstance()
{
    LogUtil::LogInfo("GetSingleInstance");
    if (nullptr == m_pInstance)
    {
        m_pInstance = new CBaiLuInputMethodClass();
        return m_pInstance;
    }
    else
    {
        return m_pInstance;
    }
}

bool CBaiLuInputMethodClass::InitThreadMgrEventSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::InitThreadMgrEventSink");
    ITfSource* pSource = nullptr;
    bool bRet = false;
    HRESULT qResult = m_pThreadMgr->QueryInterface(IID_ITfSource, (void**)(&pSource));
    if (FAILED(qResult) && (nullptr != pSource))
    {
        LogUtil::LogError(__FILE__, __LINE__);
        return bRet;
    }

    if (m_pThreadMgrEventSink)
    {
        m_pThreadMgrEventSink->CheckRefCount();
    }
    DWORD cookie= TF_INVALID_COOKIE;
    qResult = pSource->AdviseSink(IID_ITfThreadMgrEventSink,
        m_pThreadMgrEventSink,
        &cookie);
    if (m_pThreadMgrEventSink)
    {
        m_pThreadMgrEventSink->CheckRefCount();
    }
    if (FAILED(qResult))
    {
        LogUtil::LogError(__FILE__, __LINE__);
        LogUtil::LogInfo("HRESULT %ld", (long)(qResult));
        cookie = TF_INVALID_COOKIE;
    }
    else
    {
        bRet = true;
    }
    m_threadMgrEventSinkCookie = cookie;
    pSource->Release();
    return bRet;
}
bool CBaiLuInputMethodClass::InitKeyEventSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::InitKeyEventSink");
    ITfKeystrokeMgr* pKeyStrokeMgr = nullptr;
    bool bRet = false;
    auto qResult = m_pThreadMgr->QueryInterface(IID_ITfKeystrokeMgr, (void**)(&pKeyStrokeMgr));
    if (FAILED(qResult))
    {
        return bRet;
    }
    HRESULT hR = S_OK;
    if (m_pKeyEventSink)
    {
        m_pKeyEventSink->CheckRefCount();
    }
    hR = pKeyStrokeMgr->AdviseKeyEventSink(this->m_tfClientId,
        m_pKeyEventSink,
        TRUE);
    if (m_pKeyEventSink)
    {
        m_pKeyEventSink->CheckRefCount();
    }
    pKeyStrokeMgr->Release();
    if (m_pKeyEventSink)
    {
        m_pKeyEventSink->CheckRefCount();
    }
    return (hR == S_OK);
}

bool CBaiLuInputMethodClass::InitTextEditSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::InitTextEditSink");
    ITfDocumentMgr* pDocMgrFocus = nullptr;
    auto result = m_pThreadMgr->GetFocus(&pDocMgrFocus);
    if (SUCCEEDED(result) && (pDocMgrFocus != nullptr))
    {
        pDocMgrFocus->Release();
    }

    ITfSource* pSource = nullptr;
    BOOL ret = TRUE;

    // clear out any previous sink first
    if (m_textEditSinkCookie != TF_INVALID_COOKIE)
    {
        if (SUCCEEDED(m_pCurTfContext->QueryInterface(IID_ITfSource, (void**)&pSource)))
        {
            pSource->UnadviseSink(m_textEditSinkCookie);
            pSource->Release();
        }

        m_pCurTfContext->Release();
        m_pCurTfContext = nullptr;
        m_textEditSinkCookie = TF_INVALID_COOKIE;
    }

    if (m_pCurTfDocumentMgr == nullptr)
    {
        return TRUE; // caller just wanted to clear the previous sink
    }

    if (FAILED(m_pCurTfDocumentMgr->GetTop(&m_pCurTfContext)))
    {
        return FALSE;
    }

    if (m_pCurTfContext == nullptr)
    {
        return TRUE; // empty document, no sink possible
    }

    ret = FALSE;
    if (SUCCEEDED(m_pCurTfContext->QueryInterface(IID_ITfSource, (void**)&pSource)))
    {
        if (SUCCEEDED(pSource->AdviseSink(IID_ITfTextEditSink, m_pTextEditSink, &m_textEditSinkCookie)))
        {
            ret = TRUE;
        }
        else
        {
            m_textEditSinkCookie = TF_INVALID_COOKIE;
        }
        pSource->Release();
    }

    if (ret == FALSE)
    {
        m_pCurTfContext->Release();
        m_pCurTfContext = nullptr;
    }
    return false;
}

bool CBaiLuInputMethodClass::InitActiveLanguageProfileNotifySink()
{
    LogUtil::LogInfo(TEXT("CBaiLuInputMethodClass::_InitActiveLanguageProfileNotifySink"));
    ITfSource* pSource = nullptr;
    BOOL ret = FALSE;

    if (m_pThreadMgr->QueryInterface(IID_ITfSource, (void**)&pSource) != S_OK)
    {
        return ret;
    }

    if (pSource->AdviseSink(IID_ITfActiveLanguageProfileNotifySink, 
        m_pNotifySink, 
        &m_activeLanguageProfileNotifySinkCookie) != S_OK)
    {
        m_activeLanguageProfileNotifySinkCookie = TF_INVALID_COOKIE;
        goto Exit;
    }

    ret = TRUE;

Exit:
    pSource->Release();
    return ret;
}

bool CBaiLuInputMethodClass::InitThreadFocusSink()
{
    LogUtil::LogInfo(TEXT("CBaiLuInputMethodClass::_InitThreadFocusSink"));
    ITfSource* pSource = nullptr;

    if (FAILED(m_pThreadMgr->QueryInterface(IID_ITfSource, (void**)&pSource)))
    {
        return FALSE;
    }

    if (FAILED(pSource->AdviseSink(IID_ITfThreadFocusSink,
        m_pThreadFocusSink, 
        &m_dwThreadFocusSinkCookie)))
    {
        pSource->Release();
        return FALSE;
    }

    pSource->Release();

    return TRUE;
}

bool CBaiLuInputMethodClass::InitDisplayAttributeGuidAtomSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::InitDisplayAttributeGuidAtomSink");
    ITfCategoryMgr* pCategoryMgr = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_TF_CategoryMgr,
        nullptr, 
        CLSCTX_INPROC_SERVER, 
        IID_ITfCategoryMgr, 
        (void**)&pCategoryMgr);

    if (FAILED(hr))
    {
        return FALSE;
    }

    // register the display attribute for input text.
    hr = pCategoryMgr->RegisterGUID(GlobalValue::GetSampleIMEGuidDisplayAttributeInput(), &m_gaDisplayAttributeInput);
    if (FAILED(hr))
    {
        goto Exit;
    }
    // register the display attribute for the converted text.
    hr = pCategoryMgr->RegisterGUID(GlobalValue::GetSampleIMEGuidDisplayAttributeConverted(), &m_gaDisplayAttributeConverted);
    if (FAILED(hr))
    {
        goto Exit;
    }

Exit:
    pCategoryMgr->Release();

    return (hr == S_OK);
}

bool CBaiLuInputMethodClass::InitFunctionProviderSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::InitFunctionProviderSink");
    ITfSourceSingle* pSourceSingle = nullptr;
    BOOL ret = FALSE;
    if (SUCCEEDED(m_pThreadMgr->QueryInterface(IID_ITfSourceSingle, (void**)&pSourceSingle)))
    {
        IUnknown* punk = nullptr;
        if (SUCCEEDED(QueryInterface(IID_IUnknown, (void**)&punk)))
        {
            if (SUCCEEDED(pSourceSingle->AdviseSingleSink(m_tfClientId,
                IID_ITfFunctionProvider, 
                punk)))
            {
                //if (SUCCEEDED(CSearchCandidateProvider::CreateInstance(&m_pITfFnSearchCandidateProvider, (ITfTextInputProcessorEx*)this)))
                {
                    ret = TRUE;
                }
            }
            punk->Release();
        }
        pSourceSingle->Release();
    }
    return ret;
}

bool CBaiLuInputMethodClass::InitTextProcessorEngineSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::InitTextProcessorEngineSink");
    LANGID langid = 0;
    CLSID clsid = GUID_NULL;
    GUID guidProfile = GUID_NULL;

    // Get default profile.
    CBaiLuInputProcessorProfileAgent profile;

    if (FAILED(profile.CreateInstance()))
    {
        return FALSE;
    }

    if (FAILED(profile.GetCurrentLanguage(&langid)))
    {
        return FALSE;
    }

    if (FAILED(profile.GetDefaultLanguageProfile(langid, GUID_TFCAT_TIP_KEYBOARD, &clsid, &guidProfile)))
    {
        return FALSE;
    }

    // Is this already added?
    /*if (_pCompositionProcessorEngine != nullptr)
    {
        LANGID langidProfile = 0;
        GUID guidLanguageProfile = GUID_NULL;

        guidLanguageProfile = _pCompositionProcessorEngine->GetLanguageProfile(&langidProfile);
        if ((langid == langidProfile) && IsEqualGUID(guidProfile, guidLanguageProfile))
        {
            return TRUE;
        }
    }

    // Create composition processor engine
    if (_pCompositionProcessorEngine == nullptr)
    {
        _pCompositionProcessorEngine = new (std::nothrow) CCompositionProcessorEngine();
    }
    if (!_pCompositionProcessorEngine)
    {
        return FALSE;
    }

    // setup composition processor engine
    if (FALSE == _pCompositionProcessorEngine->SetupLanguageProfile(langid, guidProfile, _GetThreadMgr(), _GetClientId(), _IsSecureMode(), _IsComLess()))
    {
        return FALSE;
    }

    return TRUE;
    return false;*/
    return true;
}

void CBaiLuInputMethodClass::UnInitThreadMgrEventSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::UnInitThreadMgrEventSink");

    return;
}

void CBaiLuInputMethodClass::UnInitKeyEventSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::UnInitKeyEventSink");
    ITfKeystrokeMgr* pKeyStrokeMgr = nullptr;
    bool bRet = false;
    auto qResult = m_pThreadMgr->QueryInterface(IID_ITfKeystrokeMgr, (void**)(&pKeyStrokeMgr));
    if (FAILED(qResult))
    {
        return;
    }
    HRESULT hR = S_OK;
    hR = pKeyStrokeMgr->UnadviseKeyEventSink(this->m_tfClientId);
    pKeyStrokeMgr->Release();
    return;
}
void CBaiLuInputMethodClass::UnInitActiveLanguageProfileNotifySink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::UnInitActiveLanguageProfileNotifySink");
    ITfSource* pSource = nullptr;

    if (m_activeLanguageProfileNotifySinkCookie == TF_INVALID_COOKIE)
    {
        return; // never Advised
    }

    if (m_pThreadMgr->QueryInterface(IID_ITfSource, (void**)&pSource) == S_OK)
    {
        pSource->UnadviseSink(m_activeLanguageProfileNotifySinkCookie);
        pSource->Release();
    }

    m_activeLanguageProfileNotifySinkCookie = TF_INVALID_COOKIE;
    return;
}
void CBaiLuInputMethodClass::UnInitThreadFocusSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::UnInitThreadFocusSink");
    ITfSource* pSource = nullptr;

    if (FAILED(m_pThreadMgr->QueryInterface(IID_ITfSource, (void**)&pSource)))
    {
        return;
    }

    if (FAILED(pSource->UnadviseSink(m_dwThreadFocusSinkCookie)))
    {
        pSource->Release();
        return;
    }

    pSource->Release();
    return;
}
void CBaiLuInputMethodClass::UnInitDisplayAttributeGuidAtomSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::UnInitDisplayAttributeGuidAtomSink");
    return;
}
void CBaiLuInputMethodClass::UnInitFunctionProviderSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::UnInitFunctionProviderSink");
    ITfSourceSingle* pSourceSingle = nullptr;
    if (SUCCEEDED(m_pThreadMgr->QueryInterface(IID_ITfSourceSingle, (void**)&pSourceSingle)))
    {
        pSourceSingle->UnadviseSingleSink(m_tfClientId, IID_ITfFunctionProvider);
        pSourceSingle->Release();
    }
    return;
}
void CBaiLuInputMethodClass::UnInitTextProcessorEngineSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::UnInitTextProcessorEngineSink");
    return;
}

std::string VirtualKeyCodeToString(UINT vkCode) {
    // 用于存储键名的缓冲区
    char keyName[256] = { 0 };

    // 将虚拟键码转换为扫描码
    UINT scanCode = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);

    // 构造lParam用于GetKeyNameText函数
    // 高16位放扫描码，低16位中的第25位（bit24）用于指示扩展键
    LONG lParam = (scanCode << 16);

    // 获取键名
    if (GetKeyNameTextA(lParam, keyName, sizeof(keyName)) > 0) {
        return std::string(keyName);
    }

    return "Unknown Key";
}

void CBaiLuInputMethodClass::LogKeyDownAndUp(WPARAM wParam, LPARAM lParam,const std::string method)
{
    UINT vCode = UINT(wParam);
    std::string strCodeName = VirtualKeyCodeToString(vCode);
    char buff[1024] = { 0 };
    sprintf(buff, "CBaiLuInputMethodClass Key %s  Name:%s  Code:%d  Code2: %d\n",method.c_str(), strCodeName.c_str(), vCode, (UINT)(lParam));
    std::string strLog(buff);
    LogUtil::LogInfo("%s",strLog.c_str());
}