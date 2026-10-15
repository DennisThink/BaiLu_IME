#include "BaiLuInputMethodClass.hpp"
#include "GlobalValues.hpp"
#include "BaiLuInputProcessorProfileAgent.hpp"
#include "CommonFunction.hpp"
#include "BaiLuInputCore.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
CBaiLuInputMethodClass::CBaiLuInputMethodClass()
{
    //g_logger.Info("CBaiLuInputMethodClass::CBaiLuInputMethodClass");
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
            g_logger.Error("{} {}", __FILE__, __LINE__);
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
            g_logger.Error("{} {}", __FILE__, __LINE__);
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
            g_logger.Error("{} {}", __FILE__, __LINE__);
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
            g_logger.Error("{} {}", __FILE__, __LINE__);
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
            g_logger.Error("{} {}", __FILE__, __LINE__);
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
            g_logger.Error("{} {}", __FILE__, __LINE__);
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
            g_logger.Error("{} {}", __FILE__, __LINE__);
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
            g_logger.Error("{} {}", __FILE__, __LINE__);
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
            g_logger.Error("{} {}", __FILE__, __LINE__);
        }
    }
    AddRef();
}

CBaiLuInputMethodClass::~CBaiLuInputMethodClass()
{
    //g_logger.Info("CBaiLuInputMethodClass::~CBaiLuInputMethodClass");
}

// IUnknown
STDMETHODIMP CBaiLuInputMethodClass::QueryInterface(REFIID riid, _Outptr_ void** ppvObj)
{
    //g_logger.Info("CBaiLuInputMethodClass::QueryInterface Begin");
    if (ppvObj == NULL)
    {
        g_logger.Error("{} {}", __FILE__, __LINE__);
        return E_INVALIDARG;
    }

    *ppvObj = NULL;

    if (IsEqualIID(riid, IID_IUnknown) ||
        IsEqualIID(riid, IID_ITfTextInputProcessor))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        AddRef();
        *ppvObj = (ITfTextInputProcessor*)this;
    }
    else if (IsEqualIID(riid, IID_ITfTextInputProcessorEx))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        AddRef();
        *ppvObj = (ITfTextInputProcessorEx*)this;
    }
    else if (IsEqualIID(riid, IID_ITfKeyEventSink))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        if (nullptr != this->m_pKeyEventSink)
        {
            m_pKeyEventSink->AddRef();
            *ppvObj = (m_pKeyEventSink);
        }
    }
    else if (IsEqualIID(riid, IID_ITfThreadMgrEventSink))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        if (nullptr != this->m_pThreadMgrEventSink)
        {
            this->m_pThreadMgrEventSink->AddRef();
            *ppvObj = this->m_pThreadMgrEventSink;
        }
        else
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
        }
    }
    else if (IsEqualIID(riid, IID_ITfTextEditSink))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        if (nullptr != this->m_pTextEditSink)
        {
            this->m_pTextEditSink->AddRef();
            *ppvObj = this->m_pTextEditSink;
        }
        else
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
        }
    }

    else if (IsEqualIID(riid, IID_ITfActiveLanguageProfileNotifySink))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        if (nullptr != m_pNotifySink)
        {
            m_pNotifySink->AddRef();
            *ppvObj = m_pNotifySink;
        }
        else
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
        }
    }
    else if (IsEqualIID(riid, IID_ITfCompositionSink))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        if (nullptr != this->m_pCompositionSink)
        {
            m_pCompositionSink->AddRef();
            *ppvObj =m_pCompositionSink;
        }
        else
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
        }
    }
    else if (IsEqualIID(riid, IID_ITfDisplayAttributeProvider))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        if (nullptr != this->m_pDispalyAttributeProvider)
        {
            *ppvObj = m_pDispalyAttributeProvider;
            m_pDispalyAttributeProvider->AddRef();
        }
        else
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
        }
    }
    else if (IsEqualIID(riid, IID_ITfThreadFocusSink))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        if (nullptr != m_pThreadFocusSink)
        {
            *ppvObj = m_pThreadFocusSink;
            m_pThreadFocusSink->AddRef();
        }
        else
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
        }
    }
    else if (IsEqualIID(riid, IID_ITfFunctionProvider))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        if (nullptr != m_pFunctionProvider)
        {
            *ppvObj = m_pFunctionProvider;
            m_pFunctionProvider->AddRef();
        }
        else
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
        }
    }
    else if (IsEqualIID(riid, IID_ITfFunction))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        if (nullptr != m_pBoarderLayout)
        {
            *ppvObj = m_pBoarderLayout;
            m_pBoarderLayout->AddRef();
        }
        else
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
        }
    }
    else if (IsEqualIID(riid, IID_ITfFnGetPreferredTouchKeyboardLayout))
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        if (nullptr != m_pBoarderLayout)
        {
            *ppvObj = m_pBoarderLayout;
            m_pBoarderLayout->AddRef();
        }
        else
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
        }
    }
    else
    {
        GUID gid = riid;
        //g_logger.Info("UnKnown IID %x %x %x",gid.Data1,gid.Data2,gid.Data3);
    }

    if (*ppvObj != NULL)
    {
        //g_logger.Debug("{} {}", __FILE__, __LINE__);
        return S_OK;
    }

    //g_logger.Info("CBaiLuInputMethodClass::QueryInterface End");
    g_logger.Error("{} {}", __FILE__, __LINE__);
    *ppvObj = nullptr;
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) CBaiLuInputMethodClass::AddRef(void)
{
    m_refCount++;
    //g_logger.Info("CBaiLuInputMethodClass::AddRef {}",m_refCount);
    return 0;
}

STDMETHODIMP_(ULONG) CBaiLuInputMethodClass::Release(void)
{
    m_refCount--;
    //g_logger.Info("CBaiLuInputMethodClass::Release {}",m_refCount);
	ULONG nRet = m_refCount;
    if (m_refCount == 0)
    {
        delete this;
	}
    return nRet;
}

// ITfTextInputProcessor
STDMETHODIMP CBaiLuInputMethodClass::Activate(ITfThreadMgr* pThreadMgr, TfClientId tfClientId)  {
    return ActivateEx(pThreadMgr, tfClientId, 0);
}
// ITfTextInputProcessorEx
STDMETHODIMP CBaiLuInputMethodClass::ActivateEx(ITfThreadMgr* pThreadMgr, TfClientId tfClientId, DWORD dwFlags)
{
    //g_logger.Info("CBaiLuInputMethodClass::ActivateEx");
    this->m_pThreadMgr = pThreadMgr;
    m_pThreadMgr->AddRef();
    this->m_tfClientId = tfClientId;
    this->m_dwFlags = dwFlags;
    
    {
        if (!InitThreadMgrEventSink())
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
            goto ExitError;
        }
        if (!InitKeyEventSink())
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
            goto ExitError;
        }
        /*if (!InitActiveLanguageProfileNotifySink())
        {
            g_logger.Error((__FILE__, __LINE__);
            goto ExitError;
        }*/
        if (!InitThreadFocusSink())
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
            goto ExitError;
        }
        if (!InitDisplayAttributeGuidAtomSink())
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
            goto ExitError;
        }
        if (!InitFunctionProviderSink())
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
            goto ExitError;
        }
        if (!InitTextProcessorEngineSink())
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
            goto ExitError;
        }
        
        {
			CBaiLuInputCore* pInputCore = CBaiLuInputCore::GetInstance();
            pInputCore->SetClientID(tfClientId);
        }
        return S_OK;

    ExitError:
        g_logger.Error("{} {}", __FILE__, __LINE__);
        Deactivate();
        return E_FAIL;
    }
    {
        CBaiLuInputCore* pInputCore = CBaiLuInputCore::GetInstance();
        if (pInputCore)
        {
            pInputCore->DealActiveEx(pThreadMgr, tfClientId, dwFlags);
        }
    }
    return S_OK;
}
STDMETHODIMP CBaiLuInputMethodClass::Deactivate()
{
    //g_logger.Info("CBaiLuInputMethodClass::Deactivate");
    UnInitThreadMgrEventSink();
    UnInitKeyEventSink();
    UnInitThreadFocusSink();
    UnInitActiveLanguageProfileNotifySink();
    UnInitDisplayAttributeGuidAtomSink();
    UnInitFunctionProviderSink();
    UnInitTextProcessorEngineSink();
    {
        CBaiLuInputCore* pInputCore = CBaiLuInputCore::GetInstance();
        if (pInputCore)
        {
            pInputCore->DealDeactivate();
        }
    }

    return S_OK;
}




CBaiLuInputMethodClass* CBaiLuInputMethodClass::m_pInstance = nullptr;
CBaiLuInputMethodClass* CBaiLuInputMethodClass::GetSingleInstance()
{
    //g_logger.Info("GetSingleInstance");
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
    //g_logger.Info("CBaiLuInputMethodClass::InitThreadMgrEventSink");
    ITfSource* pSource = nullptr;
    bool bRet = false;
    HRESULT qResult = m_pThreadMgr->QueryInterface(IID_ITfSource, (void**)(&pSource));
    if (FAILED(qResult))
    {
        g_logger.Error("{} {}", __FILE__, __LINE__);
        return bRet;
    }

    if (m_pThreadMgrEventSink)
    {
        m_pThreadMgrEventSink->CheckRefCount();
    }
    else
    {
        g_logger.Error("{} {}", __FILE__, __LINE__);
        return bRet;
    }

    if (m_pThreadMgrEventSink)
    {
        m_pThreadMgrEventSink->CheckRefCount();
    }
    DWORD cookie= TF_INVALID_COOKIE;
    qResult = pSource->AdviseSink(IID_ITfThreadMgrEventSink,
        this,
        &cookie);
    if (m_pThreadMgrEventSink)
    {
        m_pThreadMgrEventSink->CheckRefCount();
    }
    if (FAILED(qResult))
    {
        g_logger.Error("{} {}", __FILE__, __LINE__);
        //g_logger.Info("HRESULT {} Cookie {}", (unsigned long)(qResult),cookie);
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
    //g_logger.Info("CBaiLuInputMethodClass::InitKeyEventSink");
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
    //g_logger.Info("CBaiLuInputMethodClass::InitTextEditSink");
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
        if (SUCCEEDED(pSource->AdviseSink(IID_ITfTextEditSink, this, &m_textEditSinkCookie)))
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
    //g_logger.Info("CBaiLuInputMethodClass::_InitActiveLanguageProfileNotifySink");
    ITfSource* pSource = nullptr;
    BOOL ret = FALSE;

    if (m_pThreadMgr->QueryInterface(IID_ITfSource, (void**)&pSource) != S_OK)
    {
        return ret;
    }

    if (pSource->AdviseSink(IID_ITfActiveLanguageProfileNotifySink, 
        this, 
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
    //g_logger.Info("CBaiLuInputMethodClass::InitThreadFocusSink");
    ITfSource* pSource = nullptr;
    //g_logger.Info("CBaiLuInputMethodClass::InitThreadFocusSink {} {}",__FILE__,__LINE__);
    if (FAILED(m_pThreadMgr->QueryInterface(IID_ITfSource, (void**)&pSource)))
    {
        //g_logger.Info("CBaiLuInputMethodClass::InitThreadFocusSink {} {}", __FILE__, __LINE__);
        return FALSE;
    }
    //g_logger.Info("CBaiLuInputMethodClass::InitThreadFocusSink {} {}", __FILE__, __LINE__);

    if (FAILED(pSource->AdviseSink(IID_ITfThreadFocusSink,
        this, 
        &m_dwThreadFocusSinkCookie)))
    {
        //g_logger.Info("CBaiLuInputMethodClass::InitThreadFocusSink {} {}", __FILE__, __LINE__);
        pSource->Release();
        return FALSE;
    }
    //g_logger.Info("CBaiLuInputMethodClass::InitThreadFocusSink {} {}", __FILE__, __LINE__);
    pSource->Release();

    return TRUE;
}

bool CBaiLuInputMethodClass::InitDisplayAttributeGuidAtomSink()
{
    //g_logger.Info("CBaiLuInputMethodClass::InitDisplayAttributeGuidAtomSink");
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
    //g_logger.Info("CBaiLuInputMethodClass::InitFunctionProviderSink");
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
    //g_logger.Info("CBaiLuInputMethodClass::InitTextProcessorEngineSink");
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
    //g_logger.Info("CBaiLuInputMethodClass::UnInitThreadMgrEventSink");

    return;
}

void CBaiLuInputMethodClass::UnInitKeyEventSink()
{
    //g_logger.Info("CBaiLuInputMethodClass::UnInitKeyEventSink");
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
    //g_logger.Info("CBaiLuInputMethodClass::UnInitActiveLanguageProfileNotifySink");
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
    //g_logger.Info("CBaiLuInputMethodClass::UnInitThreadFocusSink");
    ITfSource* pSource = nullptr;

    if (FAILED(m_pThreadMgr->QueryInterface(IID_ITfSource, (void**)&pSource)))
    {
        return;
    }

    /*
    *NOTIE: we should not comment this function ,but it lead to crash,we do not find the reason yet.
    *TODO:
    */
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
    //g_logger.Info("CBaiLuInputMethodClass::UnInitDisplayAttributeGuidAtomSink");
    return;
}
void CBaiLuInputMethodClass::UnInitFunctionProviderSink()
{
    //g_logger.Info("CBaiLuInputMethodClass::UnInitFunctionProviderSink");
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
    //g_logger.Info("CBaiLuInputMethodClass::UnInitTextProcessorEngineSink");
    return;
}


/*void CBaiLuInputMethodClass::LogKeyDownAndUp(WPARAM wParam, LPARAM lParam, const std::string method)
{
    UINT vCode = UINT(wParam);
    std::string strCodeName = VirtualKeyCodeToString(vCode);
    char buff[1024] = { 0 };
    sprintf(buff, "CBaiLuInputMethodClass Key %s  Name:%s  Code:%d  Code2: %d\n",method.c_str(), strCodeName.c_str(), vCode, (UINT)(lParam));
    std::string strLog(buff);
    //g_logger.Info("%s",strLog.c_str());
}*/