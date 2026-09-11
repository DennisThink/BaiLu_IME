#include "BaiLuCompositionSink.hpp"
#include "Log.hpp"

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
    m_refCount = 0;
    LogUtil::LogInfo("CBaiLuCompositionSink::CBaiLuCompositionSink %d", m_refCount);
}
CBaiLuCompositionSink::~CBaiLuCompositionSink()
{
    LogUtil::LogInfo("CBaiLuCompositionSink::~CBaiLuCompositionSink %d", m_refCount);
}
HRESULT STDMETHODCALLTYPE CBaiLuCompositionSink::QueryInterface(
/* [in] */ REFIID riid,
/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    LogUtil::LogInfo("CBaiLuCompositionSink::QueryInterface %d", m_refCount);
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuCompositionSink::AddRef(void)
{
    m_refCount++;
    LogUtil::LogInfo("CBaiLuCompositionSink::AddRef %d", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuCompositionSink::Release(void)
{
    m_refCount--;
    LogUtil::LogInfo("CBaiLuCompositionSink::Release %d", m_refCount);
    return m_refCount;
}

HRESULT STDMETHODCALLTYPE CBaiLuCompositionSink::OnCompositionTerminated(
    /* [in] */ TfEditCookie ecWrite,
    /* [in] */ __RPC__in_opt ITfComposition* pComposition)
{
    LogUtil::LogInfo("CBaiLuCompositionSink::OnCompositionTerminated %d", m_refCount);
    return 0;
}