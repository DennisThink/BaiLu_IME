#include "BaiLuInputMethodClass.hpp"
#include "Log.hpp"
CBaiLuInputMethodClass::CBaiLuInputMethodClass()
{

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
    return 0;
}

STDMETHODIMP_(ULONG) CBaiLuInputMethodClass::AddRef(void)
{
    return 0;
}

STDMETHODIMP_(ULONG) CBaiLuInputMethodClass::Release(void)
{
    return 0;
}

// ITfTextInputProcessor
STDMETHODIMP CBaiLuInputMethodClass::Activate(ITfThreadMgr* pThreadMgr, TfClientId tfClientId)  {
    return ActivateEx(pThreadMgr, tfClientId, 0);
}
// ITfTextInputProcessorEx
STDMETHODIMP CBaiLuInputMethodClass::ActivateEx(ITfThreadMgr* pThreadMgr, TfClientId tfClientId, DWORD dwFlags)
{
    return 0;
}
STDMETHODIMP CBaiLuInputMethodClass::Deactivate()
{
    return 0;
}

// ITfThreadMgrEventSink
STDMETHODIMP CBaiLuInputMethodClass::OnInitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnUninitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnSetFocus(_In_ ITfDocumentMgr* pDocMgrFocus, _In_ ITfDocumentMgr* pDocMgrPrevFocus)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnPushContext(_In_ ITfContext* pContext)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnPopContext(_In_ ITfContext* pContext)
{
    return 0;
}

// ITfTextEditSink
STDMETHODIMP CBaiLuInputMethodClass::OnEndEdit(__RPC__in_opt ITfContext* pContext, TfEditCookie ecReadOnly, __RPC__in_opt ITfEditRecord* pEditRecord)
{
    return 0;
}

// ITfKeyEventSink
STDMETHODIMP CBaiLuInputMethodClass::OnSetFocus(BOOL fForeground)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnTestKeyDown(ITfContext* pContext, WPARAM wParam, LPARAM lParam, BOOL* pIsEaten)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnKeyDown(ITfContext* pContext, WPARAM wParam, LPARAM lParam, BOOL* pIsEaten)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnTestKeyUp(ITfContext* pContext, WPARAM wParam, LPARAM lParam, BOOL* pIsEaten)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnKeyUp(ITfContext* pContext, WPARAM wParam, LPARAM lParam, BOOL* pIsEaten)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnPreservedKey(ITfContext* pContext, REFGUID rguid, BOOL* pIsEaten)
{
    return 0;
}

// ITfCompositionSink
STDMETHODIMP CBaiLuInputMethodClass::OnCompositionTerminated(TfEditCookie ecWrite, _In_ ITfComposition* pComposition)
{
    return 0;
}

// ITfDisplayAttributeProvider
STDMETHODIMP CBaiLuInputMethodClass::EnumDisplayAttributeInfo(__RPC__deref_out_opt IEnumTfDisplayAttributeInfo** ppEnum)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::GetDisplayAttributeInfo(__RPC__in REFGUID guidInfo, __RPC__deref_out_opt ITfDisplayAttributeInfo** ppInfo)
{
    return 0;
}

// ITfActiveLanguageProfileNotifySink
STDMETHODIMP CBaiLuInputMethodClass::OnActivated(_In_ REFCLSID clsid, _In_ REFGUID guidProfile, _In_ BOOL isActivated)
{
    return 0;
}

// ITfThreadFocusSink
STDMETHODIMP CBaiLuInputMethodClass::OnSetThreadFocus()
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::OnKillThreadFocus()
{
    return 0;
}

// ITfFunctionProvider
STDMETHODIMP CBaiLuInputMethodClass::GetType(__RPC__out GUID* pguid)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::GetDescription(__RPC__deref_out_opt BSTR* pbstrDesc)
{
    return 0;
}

STDMETHODIMP CBaiLuInputMethodClass::GetFunction(__RPC__in REFGUID rguid, __RPC__in REFIID riid, __RPC__deref_out_opt IUnknown** ppunk)
{
    return 0;
}

// ITfFunction
STDMETHODIMP CBaiLuInputMethodClass::GetDisplayName(_Out_ BSTR* pbstrDisplayName)
{
    return 0;
}

// ITfFnGetPreferredTouchKeyboardLayout, it is the Optimized layout feature.
STDMETHODIMP CBaiLuInputMethodClass::GetLayout(_Out_ TKBLayoutType* ptkblayoutType, _Out_ WORD* pwPreferredLayoutId)
{
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