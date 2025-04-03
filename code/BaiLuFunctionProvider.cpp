#include "BaiLuFunctionProvider.hpp"
#include "Log.hpp"
CBaiLuFunctionProvider::CBaiLuFunctionProvider()
{
    LogUtil::LogInfo("CBaiLuFunctionProvider::CBaiLuFunctionProvider");
    m_refCount = 0;
}
CBaiLuFunctionProvider::~CBaiLuFunctionProvider()
{
    LogUtil::LogInfo("CBaiLuFunctionProvider::~CBaiLuFunctionProvider");
}

HRESULT STDMETHODCALLTYPE CBaiLuFunctionProvider::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    LogUtil::LogInfo("CBaiLuFunctionProvider::QueryInterface");
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuFunctionProvider::AddRef(void)
{
    m_refCount++;
    LogUtil::LogInfo("CBaiLuFunctionProvider::AddRef %d", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuFunctionProvider::Release(void)
{
    m_refCount--;
    LogUtil::LogInfo("CBaiLuFunctionProvider::Release %d", m_refCount);
    return m_refCount;
}

HRESULT STDMETHODCALLTYPE  CBaiLuFunctionProvider::GetType(
    /* [out] */ __RPC__out GUID* pguid)
{
    LogUtil::LogInfo("CBaiLuFunctionProvider::GetType");
    return 0;
}

HRESULT STDMETHODCALLTYPE  CBaiLuFunctionProvider::GetDescription(
    /* [out] */ __RPC__deref_out_opt BSTR* pbstrDesc)
{
    LogUtil::LogInfo("CBaiLuFunctionProvider::GetDescription");
    return 0;
}

HRESULT STDMETHODCALLTYPE  CBaiLuFunctionProvider::GetFunction(
    /* [in] */ __RPC__in REFGUID rguid,
    /* [in] */ __RPC__in REFIID riid,
    /* [iid_is][out] */ __RPC__deref_out_opt IUnknown** ppunk)
{
    LogUtil::LogInfo("CBaiLuFunctionProvider::GetFunction");
    return 0;
}