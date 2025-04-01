#include "BaiLuFunctionProvider.hpp"
CBaiLuFunctionProvider::CBaiLuFunctionProvider()
{
    
}
CBaiLuFunctionProvider::~CBaiLuFunctionProvider()
{

}

HRESULT STDMETHODCALLTYPE CBaiLuFunctionProvider::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuFunctionProvider::AddRef(void)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuFunctionProvider::Release(void)
{
    return 0;
}

HRESULT STDMETHODCALLTYPE  CBaiLuFunctionProvider::GetType(
    /* [out] */ __RPC__out GUID* pguid)
{
    return 0;
}

HRESULT STDMETHODCALLTYPE  CBaiLuFunctionProvider::GetDescription(
    /* [out] */ __RPC__deref_out_opt BSTR* pbstrDesc)
{
    return 0;
}

HRESULT STDMETHODCALLTYPE  CBaiLuFunctionProvider::GetFunction(
    /* [in] */ __RPC__in REFGUID rguid,
    /* [in] */ __RPC__in REFIID riid,
    /* [iid_is][out] */ __RPC__deref_out_opt IUnknown** ppunk)
{
    return 0;
}