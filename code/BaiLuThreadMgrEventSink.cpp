#include "BaiLuThreadMgrEventSink.hpp"
#include "Log.hpp"


CBaiLuThreadMgrEventSink::CBaiLuThreadMgrEventSink()
{
    m_refCount = 0;
}

CBaiLuThreadMgrEventSink::~CBaiLuThreadMgrEventSink()
{

}

//IUnKnown
HRESULT STDMETHODCALLTYPE CBaiLuThreadMgrEventSink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuThreadMgrEventSink::AddRef(void)
{
    m_refCount++;
    LogUtil::LogInfo("CBaiLuThreadMgrEventSink::AddRef %d", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuThreadMgrEventSink::Release(void)
{
    m_refCount--;
    LogUtil::LogInfo("CBaiLuThreadMgrEventSink::Release %d", m_refCount);
    return m_refCount;
}

// ITfThreadMgrEventSink
STDMETHODIMP CBaiLuThreadMgrEventSink::OnInitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnInitDocumentMgr");
    this->m_pCurTfDocumentMgr = pDocMgr;
    return 0;
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnUninitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnUninitDocumentMgr");
    return 0;
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnSetFocus(_In_ ITfDocumentMgr* pDocMgrFocus, _In_ ITfDocumentMgr* pDocMgrPrevFocus)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnSetFocus");
    this->m_pPrevTfDocumentMgr = pDocMgrPrevFocus;
    this->m_pCurTfDocumentMgr = pDocMgrFocus;
    return 0;
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnPushContext(_In_ ITfContext* pContext)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnPushContext");
    m_pCurTfContext = pContext;
    return 0;
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnPopContext(_In_ ITfContext* pContext)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnPopContext");
    m_pCurTfContext = pContext;
    return 0;
}