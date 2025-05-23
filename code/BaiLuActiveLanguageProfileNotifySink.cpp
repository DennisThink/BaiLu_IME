#include "BaiLuActiveLanguageProfileNotifySink.hpp"
#include "Log.hpp"

HRESULT CBaiLuActiveLanguageProfileNotifySink::CreateInstance(CBaiLuActiveLanguageProfileNotifySink** ppOut)
{
    CBaiLuActiveLanguageProfileNotifySink* pInst = new CBaiLuActiveLanguageProfileNotifySink();
    if (nullptr != pInst && nullptr != ppOut)
    {
        *ppOut = pInst;
        return S_OK;
    }
    return -1;
}

CBaiLuActiveLanguageProfileNotifySink::CBaiLuActiveLanguageProfileNotifySink()
{
    m_refCount = 0;
    LogUtil::LogInfo("CBaiLuActiveLanguageProfileNotifySink::CBaiLuActiveLanguageProfileNotifySink %d", m_refCount);
}

CBaiLuActiveLanguageProfileNotifySink::~CBaiLuActiveLanguageProfileNotifySink()
{
    LogUtil::LogInfo("CBaiLuActiveLanguageProfileNotifySink::~CBaiLuActiveLanguageProfileNotifySink %d", m_refCount);
}

HRESULT STDMETHODCALLTYPE CBaiLuActiveLanguageProfileNotifySink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    LogUtil::LogInfo("CBaiLuActiveLanguageProfileNotifySink::QueryInterface %d", m_refCount);
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