#include "BaiLuCompositionSink.hpp"
#include "Log.hpp"
CBaiLuCompositionSink::CBaiLuCompositionSink()
{
    m_refCount = 0;
}
CBaiLuCompositionSink::~CBaiLuCompositionSink()
{

}
HRESULT STDMETHODCALLTYPE CBaiLuCompositionSink::QueryInterface(
/* [in] */ REFIID riid,
/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
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
    return 0;
}