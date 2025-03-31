#include "BaiLuCompositionSink.hpp"

CBaiLuCompositionSink::CBaiLuCompositionSink()
{

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
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuCompositionSink::Release(void)
{
    return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuCompositionSink::OnCompositionTerminated(
    /* [in] */ TfEditCookie ecWrite,
    /* [in] */ __RPC__in_opt ITfComposition* pComposition)
{
    return 0;
}