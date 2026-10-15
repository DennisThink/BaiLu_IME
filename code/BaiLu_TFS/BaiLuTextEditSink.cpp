#include "BaiLuTextEditSink.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
HRESULT CBaiLuTextEditSink::CreateInstance(CBaiLuTextEditSink** pOut)
{
    CBaiLuTextEditSink* pInst = new CBaiLuTextEditSink();
    if ((nullptr != pInst) && 
        (pOut != nullptr))
    {
        *pOut = pInst;
        return S_OK;
    }
    return -1;
}
CBaiLuTextEditSink::CBaiLuTextEditSink()
{
    //g_logger.Info("CBaiLuKeyEventSink::CBaiLuTextEditSink");
    m_refCount = 1;
}

CBaiLuTextEditSink::~CBaiLuTextEditSink()
{
    //g_logger.Info("CBaiLuKeyEventSink::~CBaiLuTextEditSink {}",this->m_refCount);
}

HRESULT STDMETHODCALLTYPE CBaiLuTextEditSink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    //g_logger.Info("CBaiLuKeyEventSink::QueryInterface");
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuTextEditSink::AddRef(void)
{
    m_refCount++;
    //g_logger.Info("CBaiLuTextEditSink::AddRef {}", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuTextEditSink::Release(void)
{
    m_refCount--;
    //g_logger.Info("CBaiLuTextEditSink::Release {}", m_refCount);
	ULONG nRet = m_refCount;
    if (m_refCount == 0)
    {
        delete this;
    }
    return nRet;
}

HRESULT STDMETHODCALLTYPE CBaiLuTextEditSink::OnEndEdit(
    /* [in] */ __RPC__in_opt ITfContext* pic,
    /* [in] */ TfEditCookie ecReadOnly,
    /* [in] */ __RPC__in_opt ITfEditRecord* pEditRecord)
{
    //g_logger.Info("CBaiLuKeyEventSink::OnEndEdit");
    return 0;
}