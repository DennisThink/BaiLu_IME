#ifndef _BAIDLU_INPUT_METHOD_CLASS_H_
#define _BAIDLU_INPUT_METHOD_CLASS_H_
#include "private.hpp"
#include "BaiLuKeyEventSink.hpp"
#include "BaiLuThreadMgrEventSink.hpp"
#include <string>
class CBaiLuInputMethodClass : public ITfTextInputProcessorEx,
    public ITfTextEditSink,
    public ITfCompositionSink,
    public ITfDisplayAttributeProvider,
    public ITfActiveLanguageProfileNotifySink,
    public ITfThreadFocusSink,
    public ITfFunctionProvider,
    public ITfFnGetPreferredTouchKeyboardLayout
{
public:
    // IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, _Outptr_ void** ppvObj) override;
    STDMETHODIMP_(ULONG) AddRef(void) override;
    STDMETHODIMP_(ULONG) Release(void) override;

    // ITfTextInputProcessor
    STDMETHODIMP Activate(ITfThreadMgr* pThreadMgr, TfClientId tfClientId) override;
    // ITfTextInputProcessorEx
    STDMETHODIMP ActivateEx(ITfThreadMgr* pThreadMgr, TfClientId tfClientId, DWORD dwFlags) override;
    STDMETHODIMP Deactivate() override;

    // ITfTextEditSink
    STDMETHODIMP OnEndEdit(__RPC__in_opt ITfContext* pContext, TfEditCookie ecReadOnly, __RPC__in_opt ITfEditRecord* pEditRecord) override;

    // ITfCompositionSink
    STDMETHODIMP OnCompositionTerminated(TfEditCookie ecWrite, _In_ ITfComposition* pComposition) override;

    // ITfDisplayAttributeProvider
    STDMETHODIMP EnumDisplayAttributeInfo(__RPC__deref_out_opt IEnumTfDisplayAttributeInfo** ppEnum) override;
    STDMETHODIMP GetDisplayAttributeInfo(__RPC__in REFGUID guidInfo, __RPC__deref_out_opt ITfDisplayAttributeInfo** ppInfo) override;

    // ITfActiveLanguageProfileNotifySink
    STDMETHODIMP OnActivated(_In_ REFCLSID clsid, _In_ REFGUID guidProfile, _In_ BOOL isActivated) override;

    // ITfThreadFocusSink
    STDMETHODIMP OnSetThreadFocus() override;
    STDMETHODIMP OnKillThreadFocus() override;

    // ITfFunctionProvider
    STDMETHODIMP GetType(__RPC__out GUID* pguid) override;
    STDMETHODIMP GetDescription(__RPC__deref_out_opt BSTR* pbstrDesc) override;
    STDMETHODIMP GetFunction(__RPC__in REFGUID rguid, __RPC__in REFIID riid, __RPC__deref_out_opt IUnknown** ppunk) override;

    // ITfFunction
    STDMETHODIMP GetDisplayName(_Out_ BSTR* pbstrDisplayName) override;

    // ITfFnGetPreferredTouchKeyboardLayout, it is the Optimized layout feature.
    STDMETHODIMP GetLayout(_Out_ TKBLayoutType* ptkblayoutType, _Out_ WORD* pwPreferredLayoutId) override;

    static CBaiLuInputMethodClass* GetSingleInstance();
private:
    static CBaiLuInputMethodClass* m_pInstance;
    CBaiLuInputMethodClass();
    virtual ~CBaiLuInputMethodClass();

protected:
    bool InitThreadMgrEventSink();
    bool InitKeyEventSink();
    bool InitTextEditSink();
    bool InitActiveLanguageProfileNotifySink();
    bool InitThreadFocusSink();
    bool InitDisplayAttributeGuidAtomSink();
    bool InitFunctionProviderSink();
    bool InitTextProcessorEngineSink();

    void UnInitThreadMgrEventSink();
    void UnInitKeyEventSink();
    void UnInitActiveLanguageProfileNotifySink();
    void UnInitThreadFocusSink();
    void UnInitDisplayAttributeGuidAtomSink();
    void UnInitFunctionProviderSink();
    void UnInitTextProcessorEngineSink();
    void LogKeyDownAndUp(WPARAM wParam, LPARAM lParam,const std::string method);
private:
    CBaiLuKeyEventSink* m_pKeyEventSink;
    CBaiLuThreadMgrEventSink* m_pThreadMgrEventSink;
    int m_refCount;
    ITfThreadMgr* m_pThreadMgr;
    TfClientId m_tfClientId;
    DWORD m_dwFlags;

    DWORD m_threadMgrEventSinkCookie;
    DWORD m_textEditSinkCookie;
    //
    ITfDocumentMgr* m_pPrevTfDocumentMgr;
    ITfDocumentMgr* m_pCurTfDocumentMgr;

    ITfContext* m_pCurTfContext;
    DWORD m_activeLanguageProfileNotifySinkCookie;
    DWORD m_dwThreadFocusSinkCookie;


    // guidatom for the display attibute.
    TfGuidAtom m_gaDisplayAttributeInput;
    TfGuidAtom m_gaDisplayAttributeConverted;
};
#endif