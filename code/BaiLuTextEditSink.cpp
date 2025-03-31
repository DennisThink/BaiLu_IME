#include "BaiLuTextEditSink.hpp"
CBaiLuTextEditSink::CBaiLuTextEditSink()
{

}

CBaiLuTextEditSink::~CBaiLuTextEditSink()
{

}

HRESULT STDMETHODCALLTYPE CBaiLuTextEditSink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuTextEditSink::AddRef(void)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuTextEditSink::Release(void)
{
    return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuTextEditSink::OnEndEdit(
    /* [in] */ __RPC__in_opt ITfContext* pic,
    /* [in] */ TfEditCookie ecReadOnly,
    /* [in] */ __RPC__in_opt ITfEditRecord* pEditRecord)
{
    return 0;
}