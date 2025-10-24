#ifndef _BAIDLU_INPUT_METHOD_CLASS_H_
#define _BAIDLU_INPUT_METHOD_CLASS_H_
#include "private.hpp"
#include "BaiLuKeyEventSink.hpp"
#include "BaiLuThreadMgrEventSink.hpp"
#include "BaiLuTextEditSink.hpp"
#include "BaiLuCompositionSink.hpp"
#include "BaiLuDisplayAttributeProvider.hpp"
#include "BaiLuThreadFocusSink.hpp"
#include "BaiLuFunctionProvider.hpp"
#include "BaiLuFnGetPreferredTouchKeyboardLayout.hpp"
#include "BaiLuActiveLanguageProfileNotifySink.hpp"
#include <string>
class CBaiLuInputMethodClass : public ITfTextInputProcessorEx
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
    CBaiLuTextEditSink* m_pTextEditSink;
    CBaiLuCompositionSink* m_pCompositionSink;
    CBaiLuDisplayAttributeProvider* m_pDispalyAttributeProvider;
    CBaiLuThreadFocusSink* m_pThreadFocusSink;
    CBaiLuFunctionProvider* m_pFunctionProvider;
    CBaiLuFnGetPreferredTouchKeyBoardLayout* m_pBoarderLayout;
    CBaiLuActiveLanguageProfileNotifySink* m_pNotifySink;


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