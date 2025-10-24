#ifndef _BAI_LU_THREAD_FOCUS_SINK_H_
#define _BAI_LU_THREAD_FOCUS_SINK_H_
#include "private.hpp"
class CBaiLuThreadFocusSink :public ITfThreadFocusSink
{
public:
    static HRESULT CreateInstance(CBaiLuThreadFocusSink** ppOut);
protected:
    CBaiLuThreadFocusSink();
    virtual ~CBaiLuThreadFocusSink();
public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)override;

    virtual ULONG STDMETHODCALLTYPE AddRef(void)override;

    virtual ULONG STDMETHODCALLTYPE Release(void)override;
public:
    virtual HRESULT STDMETHODCALLTYPE OnSetThreadFocus(void) override;

    virtual HRESULT STDMETHODCALLTYPE OnKillThreadFocus(void) override;
private:
    int m_refCount;
};
#endif