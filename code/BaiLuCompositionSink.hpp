#ifndef _BAI_LU_COMPOSITION_SINK_H_
#define _BAI_LU_COMPOSITION_SINK_H_
#include "private.hpp"
class CBaiLuCompositionSink :public ITfCompositionSink
{
public:
	CBaiLuCompositionSink();
	virtual ~CBaiLuCompositionSink();
public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)override;

    virtual ULONG STDMETHODCALLTYPE AddRef(void)override;

    virtual ULONG STDMETHODCALLTYPE Release(void)override;
public:
    virtual HRESULT STDMETHODCALLTYPE OnCompositionTerminated(
        /* [in] */ TfEditCookie ecWrite,
        /* [in] */ __RPC__in_opt ITfComposition* pComposition) override;
private:
    int m_refCount;
};
#endif