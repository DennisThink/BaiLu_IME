#include "BaiLuCompositionSink.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
HRESULT CBaiLuCompositionSink::CreateInstance(CBaiLuCompositionSink** pOut)
{
    CBaiLuCompositionSink* pInst = new CBaiLuCompositionSink();
    if (nullptr != pOut && nullptr != pInst)
    {
        *pOut = pInst;
        return S_OK;
    }
    return -1;
}

CBaiLuCompositionSink::CBaiLuCompositionSink()
{
    m_refCount = 1;
   //g_logger.Info("CBaiLuCompositionSink::CBaiLuCompositionSink {}", m_refCount);
}
CBaiLuCompositionSink::~CBaiLuCompositionSink()
{
   //g_logger.Info("CBaiLuCompositionSink::~CBaiLuCompositionSink {}", m_refCount);
}
HRESULT STDMETHODCALLTYPE CBaiLuCompositionSink::QueryInterface(
/* [in] */ REFIID riid,
/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
   //g_logger.Info("CBaiLuCompositionSink::QueryInterface {}", m_refCount);
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuCompositionSink::AddRef(void)
{
    m_refCount++;
   //g_logger.Info("CBaiLuCompositionSink::AddRef {}", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuCompositionSink::Release(void)
{
    m_refCount--;
   //g_logger.Info("CBaiLuCompositionSink::Release {}", m_refCount);
	ULONG nRet = m_refCount;
    if(m_refCount == 0)
    {
        delete this;
	}
    return nRet;
}

HRESULT STDMETHODCALLTYPE CBaiLuCompositionSink::OnCompositionTerminated(
    /* [in] */ TfEditCookie ecWrite,
    /* [in] */ __RPC__in_opt ITfComposition* pComposition)
{
   //g_logger.Info("CBaiLuCompositionSink::OnCompositionTerminated {}", m_refCount);
    return 0;
}