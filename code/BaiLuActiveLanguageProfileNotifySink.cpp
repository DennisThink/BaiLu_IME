#include "BaiLuActiveLanguageProfileNotifySink.hpp"
#include "Log.hpp"
CBaiLuActiveLanguageProfileNotifySink::CBaiLuActiveLanguageProfileNotifySink()
{
    m_refCount = 0;
}

CBaiLuActiveLanguageProfileNotifySink::~CBaiLuActiveLanguageProfileNotifySink()
{

}

HRESULT STDMETHODCALLTYPE CBaiLuActiveLanguageProfileNotifySink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuActiveLanguageProfileNotifySink::AddRef(void)
{
    m_refCount++;
    LogUtil::LogInfo("CBaiLuActiveLanguageProfileNotifySink::AddRef %d", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuActiveLanguageProfileNotifySink::Release(void)
{
    m_refCount--;
    LogUtil::LogInfo("CBaiLuActiveLanguageProfileNotifySink::Release %d", m_refCount);
    return m_refCount;
}


HRESULT STDMETHODCALLTYPE CBaiLuActiveLanguageProfileNotifySink::OnActivated(
    /* [in] */ __RPC__in REFCLSID clsid,
    /* [in] */ __RPC__in REFGUID guidProfile,
    /* [in] */ BOOL fActivated)
{
    LogUtil::LogInfo("CBaiLuActiveLanguageProfileNotifySink::OnActivated");
    return 0;
}