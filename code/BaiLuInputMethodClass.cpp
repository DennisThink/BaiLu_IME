#include "BaiLuInputMethodClass.hpp"
#include "Log.hpp"
CBaiLuInputMethodClass::CBaiLuInputMethodClass()
{
    m_refCount = 0;
}

CBaiLuInputMethodClass::~CBaiLuInputMethodClass()
{
}

// IUnknown
STDMETHODIMP CBaiLuInputMethodClass::QueryInterface(REFIID riid, _Outptr_ void** ppvObj)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::QueryInterface");
    if (ppvObj == nullptr)
    {
        return E_INVALIDARG;
    }

    *ppvObj = nullptr;

    if (IsEqualIID(riid, IID_IUnknown) ||
        IsEqualIID(riid, IID_ITfTextInputProcessor))
    {
        *ppvObj = (ITfTextInputProcessor*)this;
    }
    else if (IsEqualIID(riid, IID_ITfTextInputProcessorEx))
    {
        *ppvObj = (ITfTextInputProcessorEx*)this;
    }
    else if (IsEqualIID(riid, IID_ITfThreadMgrEventSink))
    {
        *ppvObj = (ITfThreadMgrEventSink*)this;
    }
    else if (IsEqualIID(riid, IID_ITfTextEditSink))
    {
        *ppvObj = (ITfTextEditSink*)this;
    }
    else if (IsEqualIID(riid, IID_ITfKeyEventSink))
    {
        *ppvObj = (ITfKeyEventSink*)this;
    }
    else if (IsEqualIID(riid, IID_ITfActiveLanguageProfileNotifySink))
    {
        *ppvObj = (ITfActiveLanguageProfileNotifySink*)this;
    }
    else if (IsEqualIID(riid, IID_ITfCompositionSink))
    {
        *ppvObj = (ITfKeyEventSink*)this;
    }
    else if (IsEqualIID(riid, IID_ITfDisplayAttributeProvider))
    {
        *ppvObj = (ITfDisplayAttributeProvider*)this;
    }
    else if (IsEqualIID(riid, IID_ITfThreadFocusSink))
    {
        *ppvObj = (ITfThreadFocusSink*)this;
    }
    else if (IsEqualIID(riid, IID_ITfFunctionProvider))
    {
        *ppvObj = (ITfFunctionProvider*)this;
    }
    else if (IsEqualIID(riid, IID_ITfFunction))
    {
        *ppvObj = (ITfFunction*)this;
    }
    else if (IsEqualIID(riid, IID_ITfFnGetPreferredTouchKeyboardLayout))
    {
        *ppvObj = (ITfFnGetPreferredTouchKeyboardLayout*)this;
    }

    if (*ppvObj)
    {
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
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
            goto ExitError;
        }
        if (!InitKeyEventSink())
        {
            goto ExitError;
        }
        if (!InitActiveLanguageProfileNotifySink())
        {
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
    return 0;
}
STDMETHODIMP CBaiLuInputMethodClass::Deactivate()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::Deactivate");
    UnInitThreadMgrEventSink();
    UnInitKeyEventSink();
    UnInitActiveLanguageProfileNotifySink();
    UnInitThreadFocusSink();
    UnInitDisplayAttributeGuidAtomSink();
    UnInitFunctionProviderSink();
    UnInitTextProcessorEngineSink();
    return 0;
}

// ITfThreadMgrEventSink
STDMETHODIMP CBaiLuInputMethodClass::OnInitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnInitDocumentMgr");
    this->m_pCurTfDocumentMgr = pDocMgr;
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnUninitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnUninitDocumentMgr");
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnSetFocus(_In_ ITfDocumentMgr* pDocMgrFocus, _In_ ITfDocumentMgr* pDocMgrPrevFocus)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnSetFocus");
    this->m_pPrevTfDocumentMgr = pDocMgrPrevFocus;
    this->m_pCurTfDocumentMgr = pDocMgrFocus;
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnPushContext(_In_ ITfContext* pContext)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnPushContext");
    m_pCurTfContext = pContext;
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnPopContext(_In_ ITfContext* pContext)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnPopContext");
    m_pCurTfContext = pContext;
    return 0;
}

// ITfTextEditSink
STDMETHODIMP CBaiLuInputMethodClass::OnEndEdit(__RPC__in_opt ITfContext* pContext, TfEditCookie ecReadOnly, __RPC__in_opt ITfEditRecord* pEditRecord)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnEndEdit");
    return 0;
}

// ITfKeyEventSink
STDMETHODIMP CBaiLuInputMethodClass::OnSetFocus(BOOL fForeground)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnSetFocus");
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnTestKeyDown(ITfContext* pContext, WPARAM wParam, LPARAM lParam, BOOL* pIsEaten)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnTestKeyDown");
    LogKeyDownAndUp(wParam, lParam, "OnTestKeyDown");
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnKeyDown(ITfContext* pContext, WPARAM wParam, LPARAM lParam, BOOL* pIsEaten)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnKeyDown");
    LogKeyDownAndUp(wParam, lParam, "OnKeyDown");
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnTestKeyUp(ITfContext* pContext, WPARAM wParam, LPARAM lParam, BOOL* pIsEaten)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnTestKeyUp");
    LogKeyDownAndUp(wParam, lParam, "OnTestKeyUp");
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnKeyUp(ITfContext* pContext, WPARAM wParam, LPARAM lParam, BOOL* pIsEaten)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnKeyUp");
    LogKeyDownAndUp(wParam, lParam, "OnKeyUp");
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnPreservedKey(ITfContext* pContext, REFGUID rguid, BOOL* pIsEaten)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnPreservedKey");
    return 0;
}

// ITfCompositionSink
STDMETHODIMP CBaiLuInputMethodClass::OnCompositionTerminated(TfEditCookie ecWrite, _In_ ITfComposition* pComposition)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnCompositionTerminated");
    return 0;
}

// ITfDisplayAttributeProvider
STDMETHODIMP CBaiLuInputMethodClass::EnumDisplayAttributeInfo(__RPC__deref_out_opt IEnumTfDisplayAttributeInfo** ppEnum)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::EnumDisplayAttributeInfo");
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::GetDisplayAttributeInfo(__RPC__in REFGUID guidInfo, __RPC__deref_out_opt ITfDisplayAttributeInfo** ppInfo)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::GetDisplayAttributeInfo");
    return 0;
}

// ITfActiveLanguageProfileNotifySink
STDMETHODIMP CBaiLuInputMethodClass::OnActivated(_In_ REFCLSID clsid, _In_ REFGUID guidProfile, _In_ BOOL isActivated)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnActivated");
    return 0;
}

// ITfThreadFocusSink
STDMETHODIMP CBaiLuInputMethodClass::OnSetThreadFocus()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnSetThreadFocus");
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnKillThreadFocus()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnKillThreadFocus");
    return 0;
}

// ITfFunctionProvider
STDMETHODIMP CBaiLuInputMethodClass::GetType(__RPC__out GUID* pguid)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::GetType");
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::GetDescription(__RPC__deref_out_opt BSTR* pbstrDesc)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::GetDescription");
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::GetFunction(__RPC__in REFGUID rguid, __RPC__in REFIID riid, __RPC__deref_out_opt IUnknown** ppunk)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::GetFunction");
    return 0;
}

// ITfFunction
STDMETHODIMP CBaiLuInputMethodClass::GetDisplayName(_Out_ BSTR* pbstrDisplayName)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::GetDisplayName");
    return 0;
}

// ITfFnGetPreferredTouchKeyboardLayout, it is the Optimized layout feature.
STDMETHODIMP CBaiLuInputMethodClass::GetLayout(_Out_ TKBLayoutType* ptkblayoutType, _Out_ WORD* pwPreferredLayoutId)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::GetLayout");
    return 0;
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
    auto qResult = m_pThreadMgr->QueryInterface(IID_ITfSource, (void**)(&pSource));
    if (FAILED(qResult))
    {
        return bRet;
    }
    DWORD cookie= TF_INVALID_COOKIE;
    qResult = pSource->AdviseSink(IID_ITfThreadMgrEventSink,
        (ITfThreadMgrEventSink*)(this),
        &cookie);
    if (FAILED(qResult))
    {
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
    hR = pKeyStrokeMgr->AdviseKeyEventSink(this->m_tfClientId,
        (ITfKeyEventSink*)(this),
        TRUE);
    pKeyStrokeMgr->Release();
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
        if (SUCCEEDED(pSource->AdviseSink(IID_ITfTextEditSink, (ITfTextEditSink*)this, &m_textEditSinkCookie)))
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

    if (pSource->AdviseSink(IID_ITfActiveLanguageProfileNotifySink, (ITfActiveLanguageProfileNotifySink*)this, &m_activeLanguageProfileNotifySinkCookie) != S_OK)
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

    if (FAILED(pSource->AdviseSink(IID_ITfThreadFocusSink, (ITfThreadFocusSink*)this, &m_dwThreadFocusSinkCookie)))
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
    return false;
}

bool CBaiLuInputMethodClass::InitFunctionProviderSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::InitFunctionProviderSink");
    return false;
}

bool CBaiLuInputMethodClass::InitTextProcessorEngineSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::InitTextProcessorEngineSink");
    return false;
}

void CBaiLuInputMethodClass::UnInitThreadMgrEventSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::UnInitThreadMgrEventSink");
    return;
}

void CBaiLuInputMethodClass::UnInitKeyEventSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::UnInitKeyEventSink");
    return;
}
void CBaiLuInputMethodClass::UnInitActiveLanguageProfileNotifySink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::UnInitActiveLanguageProfileNotifySink");
    return;
}
void CBaiLuInputMethodClass::UnInitThreadFocusSink()
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::UnInitThreadFocusSink");
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