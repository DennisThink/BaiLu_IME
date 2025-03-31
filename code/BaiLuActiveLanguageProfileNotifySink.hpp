#ifndef _BAI_LU_ACTIVE_LANGUAGE_PROFILE_NOTIFY_SINK_H_
#define _BAI_LU_ACTIVE_LANGUAGE_PROFILE_NOTIFY_SINK_H_
#include "private.hpp"
class CBaiLuActiveLanguageProfileNotifySink :public ITfActiveLanguageProfileNotifySink
{
public:
    CBaiLuActiveLanguageProfileNotifySink();
    virtual ~CBaiLuActiveLanguageProfileNotifySink();
public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)override;

    virtual ULONG STDMETHODCALLTYPE AddRef(void)override;

    virtual ULONG STDMETHODCALLTYPE Release(void)override;
public:
    virtual HRESULT STDMETHODCALLTYPE OnActivated(
        /* [in] */ __RPC__in REFCLSID clsid,
        /* [in] */ __RPC__in REFGUID guidProfile,
        /* [in] */ BOOL fActivated) override;
};
#endif