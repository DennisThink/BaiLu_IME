#ifndef _BAI_LU_THREAD_EVENT_SINK_H_
#define _BAI_LU_THREAD_EVENT_SINK_H_
#include "private.hpp"
class CBaiLuThreadMgrEventSink:public ITfThreadMgrEventSink
{
public:
    CBaiLuThreadMgrEventSink();
    virtual ~CBaiLuThreadMgrEventSink();
public:
    //IUnKnown
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)override;

    virtual ULONG STDMETHODCALLTYPE AddRef(void)override;

    virtual ULONG STDMETHODCALLTYPE Release(void)override;
public:
    // ITfThreadMgrEventSink
    STDMETHODIMP OnInitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr) override;
    STDMETHODIMP OnUninitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr) override;
    STDMETHODIMP OnSetFocus(_In_ ITfDocumentMgr* pDocMgrFocus, _In_ ITfDocumentMgr* pDocMgrPrevFocus) override;
    STDMETHODIMP OnPushContext(_In_ ITfContext* pContext) override;
    STDMETHODIMP OnPopContext(_In_ ITfContext* pContext) override;
protected:
    //
    ITfDocumentMgr* m_pPrevTfDocumentMgr;
    ITfDocumentMgr* m_pCurTfDocumentMgr;

    ITfContext* m_pCurTfContext;
};
#endif