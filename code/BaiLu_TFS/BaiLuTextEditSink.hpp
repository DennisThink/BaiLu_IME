#ifndef _BAI_LU_TEXT_EDIT_SINK_H_
#define _BAI_LU_TEXT_EDIT_SINK_H_
#include "private.hpp"
class CBaiLuTextEditSink :public ITfTextEditSink
{
public:
    static HRESULT CreateInstance(CBaiLuTextEditSink** pOut);
protected:
    CBaiLuTextEditSink();
    virtual ~CBaiLuTextEditSink();
public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)override;

    virtual ULONG STDMETHODCALLTYPE AddRef(void)override;

    virtual ULONG STDMETHODCALLTYPE Release(void)override;
public:
    virtual HRESULT STDMETHODCALLTYPE OnEndEdit(
        /* [in] */ __RPC__in_opt ITfContext* pic,
        /* [in] */ TfEditCookie ecReadOnly,
        /* [in] */ __RPC__in_opt ITfEditRecord* pEditRecord) override;
private:
    int m_refCount;
};
#endif