#include "BaiLuThreadMgrEventSink.hpp"
#include "Log.hpp"

HRESULT CBaiLuThreadMgrEventSink::CreateInstance(CBaiLuThreadMgrEventSink** pInst)
{
    CBaiLuThreadMgrEventSink* pOut = new CBaiLuThreadMgrEventSink();
    if (nullptr != pOut && pInst != nullptr)
    {
        *pInst = pOut;
        return S_OK;
    }
    return -1;
}
CBaiLuThreadMgrEventSink::CBaiLuThreadMgrEventSink()
{
    LogUtil::LogInfo("CBaiLuThreadMgrEventSink::CBaiLuThreadMgrEventSink");
    m_refCount = 0;
    m_pPrevTfDocumentMgr = nullptr;
    m_pCurTfDocumentMgr = nullptr;
    m_pCurTfContext = nullptr;
}

CBaiLuThreadMgrEventSink::~CBaiLuThreadMgrEventSink()
{
    LogUtil::LogInfo("CBaiLuThreadMgrEventSink::~CBaiLuThreadMgrEventSink");
}

//IUnKnown
HRESULT STDMETHODCALLTYPE CBaiLuThreadMgrEventSink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    LogUtil::LogInfo("CBaiLuThreadMgrEventSink::QueryInterface");
    return -1;
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
void CBaiLuThreadMgrEventSink::CheckRefCount() const
{
    LogUtil::LogInfo("CBaiLuThreadMgrEventSink::CheckRefCount %d", m_refCount);
}
// ITfThreadMgrEventSink
STDMETHODIMP CBaiLuThreadMgrEventSink::OnInitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr)
{
    
    if (nullptr != pDocMgr)
    {
        LogUtil::LogInfo("CBaiLuInputMethodClass::OnInitDocumentMgr Succeed");
        //this->m_pCurTfDocumentMgr = pDocMgr;
        //this->m_pCurTfDocumentMgr->AddRef();
        return S_OK;
    }
    else
    {
        LogUtil::LogInfo("CBaiLuInputMethodClass::OnInitDocumentMgr Param Error");
        return -1;
    }
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnUninitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnUninitDocumentMgr");
    /*if (nullptr != this->m_pCurTfDocumentMgr)
    {
        this->m_pCurTfDocumentMgr->Release();
    }*/
    return 0;
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnSetFocus(_In_ ITfDocumentMgr* pDocMgrFocus, _In_ ITfDocumentMgr* pDocMgrPrevFocus)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnSetFocus");
    //this->m_pPrevTfDocumentMgr = pDocMgrPrevFocus;
    //this->m_pCurTfDocumentMgr = pDocMgrFocus;
    return S_OK;
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnPushContext(_In_ ITfContext* pContext)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnPushContext");
    //m_pCurTfContext = pContext;
    return 0;
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnPopContext(_In_ ITfContext* pContext)
{
    LogUtil::LogInfo("CBaiLuInputMethodClass::OnPopContext");
    //m_pCurTfContext = pContext;
    return 0;
}