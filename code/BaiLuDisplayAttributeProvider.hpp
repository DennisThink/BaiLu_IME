#ifndef _BAI_LU_DISPLAY_ATTRIBUTE_PROVIDER_H_
#define _BAI_LU_DISPLAY_ATTRIBUTE_PROVIDER_H_
#include "private.hpp"
class CBaiLuDisplayAttributeProvider :public ITfDisplayAttributeProvider
{
public:
	CBaiLuDisplayAttributeProvider();
	virtual ~CBaiLuDisplayAttributeProvider();
public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)override;

    virtual ULONG STDMETHODCALLTYPE AddRef(void)override;

    virtual ULONG STDMETHODCALLTYPE Release(void)override;
public:
    virtual HRESULT STDMETHODCALLTYPE EnumDisplayAttributeInfo(
        /* [out] */ __RPC__deref_out_opt IEnumTfDisplayAttributeInfo** ppEnum) override;

    virtual HRESULT STDMETHODCALLTYPE GetDisplayAttributeInfo(
        /* [in] */ __RPC__in REFGUID guid,
        /* [out] */ __RPC__deref_out_opt ITfDisplayAttributeInfo** ppInfo) override;
private:
    int m_refCount;
};
#endif