#include "BaiLuDisplayAttributeProvider.hpp"
#include "Log.hpp"
CBaiLuDisplayAttributeProvider::CBaiLuDisplayAttributeProvider()
{
    LogUtil::LogInfo("CBaiLuDisplayAttributeProvider::CBaiLuDisplayAttributeProvider");
    m_refCount = 0;
}
CBaiLuDisplayAttributeProvider::~CBaiLuDisplayAttributeProvider()
{
    LogUtil::LogInfo("CBaiLuDisplayAttributeProvider::~CBaiLuDisplayAttributeProvider");
}
HRESULT STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    LogUtil::LogInfo("CBaiLuDisplayAttributeProvider::QueryInterface");
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::AddRef(void)
{
    m_refCount++;
    LogUtil::LogInfo("CBaiLuDisplayAttributeProvider::AddRef %d", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::Release(void)
{
    m_refCount--;
    LogUtil::LogInfo("CBaiLuDisplayAttributeProvider::Release %d", m_refCount);
    return m_refCount;
}
HRESULT STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::EnumDisplayAttributeInfo(
    /* [out] */ __RPC__deref_out_opt IEnumTfDisplayAttributeInfo** ppEnum)
{
    LogUtil::LogInfo("CBaiLuDisplayAttributeProvider::EnumDisplayAttributeInfo");
    return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::GetDisplayAttributeInfo(
    /* [in] */ __RPC__in REFGUID guid,
    /* [out] */ __RPC__deref_out_opt ITfDisplayAttributeInfo** ppInfo)
{
    LogUtil::LogInfo("CBaiLuDisplayAttributeProvider::GetDisplayAttributeInfo");
    return 0;
}