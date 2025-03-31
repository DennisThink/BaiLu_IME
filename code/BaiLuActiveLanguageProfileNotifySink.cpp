#include "BaiLuActiveLanguageProfileNotifySink.hpp"
CBaiLuActiveLanguageProfileNotifySink::CBaiLuActiveLanguageProfileNotifySink()
{
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
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuActiveLanguageProfileNotifySink::Release(void)
{
    return 0;
}


HRESULT STDMETHODCALLTYPE CBaiLuActiveLanguageProfileNotifySink::OnActivated(
    /* [in] */ __RPC__in REFCLSID clsid,
    /* [in] */ __RPC__in REFGUID guidProfile,
    /* [in] */ BOOL fActivated)
{
    return 0;
}