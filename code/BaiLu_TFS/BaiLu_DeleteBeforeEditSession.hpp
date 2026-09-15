#ifndef _BAI_LU_DELETE_EDIT_SESSION_H_
#define _BAI_LU_DELETE_EDIT_SESSION_H_
#include "private.hpp"
/*
** Not Used Now
*/
class CBaiLuDeleteEditSession :public ITfEditSession
{
public:
    CBaiLuDeleteEditSession(ITfContext* pContext) :_cRef(1), _pContext(pContext) {

    }
    virtual ~CBaiLuDeleteEditSession(){

    }
public:
    STDMETHODIMP DoEditSession(TfEditCookie ec) override;
    // IUnknown 的三个函数
    HRESULT QueryInterface(
        REFIID riid,
        void** ppvObj) override;

    virtual ULONG AddRef() override;
    virtual ULONG Release() override;
private:
    LONG _cRef;
    ITfContext* _pContext;
    ITfComposition* _pComposition;
};
#endif