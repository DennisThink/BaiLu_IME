#include "BaiLuDisplayAttributeProvider.hpp"
CBaiLuDisplayAttributeProvider::CBaiLuDisplayAttributeProvider()
{

}
CBaiLuDisplayAttributeProvider::~CBaiLuDisplayAttributeProvider()
{

}
HRESULT STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::AddRef(void)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::Release(void)
{
    return 0;
}
HRESULT STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::EnumDisplayAttributeInfo(
    /* [out] */ __RPC__deref_out_opt IEnumTfDisplayAttributeInfo** ppEnum)
{
    return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::GetDisplayAttributeInfo(
    /* [in] */ __RPC__in REFGUID guid,
    /* [out] */ __RPC__deref_out_opt ITfDisplayAttributeInfo** ppInfo)
{
    return 0;
}