#ifndef _BAI_LU_FUNCTION_PROVIDER_H_
#define _BAI_LU_FUNCTION_PROVIDER_H_
#include "private.hpp"
class CBaiLuFunctionProvider :public ITfFunctionProvider
{
public:
    static HRESULT CreateInstance(CBaiLuFunctionProvider** ppOut);
protected:
    CBaiLuFunctionProvider();
    virtual ~CBaiLuFunctionProvider();
public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)override;

    virtual ULONG STDMETHODCALLTYPE AddRef(void)override;

    virtual ULONG STDMETHODCALLTYPE Release(void)override;
public:
    virtual HRESULT STDMETHODCALLTYPE GetType(
        /* [out] */ __RPC__out GUID* pguid) override;

    virtual HRESULT STDMETHODCALLTYPE GetDescription(
        /* [out] */ __RPC__deref_out_opt BSTR* pbstrDesc) override;

    virtual HRESULT STDMETHODCALLTYPE GetFunction(
        /* [in] */ __RPC__in REFGUID rguid,
        /* [in] */ __RPC__in REFIID riid,
        /* [iid_is][out] */ __RPC__deref_out_opt IUnknown** ppunk) override;
private:
    int m_refCount;
};
#endif