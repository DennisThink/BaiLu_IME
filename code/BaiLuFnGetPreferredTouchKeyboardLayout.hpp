#ifndef _BAI_LU_FN_GET_PREFERRED_TOUCH_KEY_BOARD_LAYOUT_H_
#define _BAI_LU_FN_GET_PREFERRED_TOUCH_KEY_BOARD_LAYOUT_H_
#include "private.hpp"
class CBaiLuFnGetPreferredTouchKeyBoardLayout :public ITfFnGetPreferredTouchKeyboardLayout
{
public:
    static HRESULT CreateInstance(CBaiLuFnGetPreferredTouchKeyBoardLayout** ppOut); 
protected:
    CBaiLuFnGetPreferredTouchKeyBoardLayout();
    virtual ~CBaiLuFnGetPreferredTouchKeyBoardLayout();
public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)override;

    virtual ULONG STDMETHODCALLTYPE AddRef(void)override;

    virtual ULONG STDMETHODCALLTYPE Release(void)override;
public:
    virtual HRESULT STDMETHODCALLTYPE GetLayout(
        /* [out] */ __RPC__out TKBLayoutType* pTKBLayoutType,
        __RPC__in WORD* pwPreferredLayoutId) override;
    virtual STDMETHODIMP GetDisplayName(_Out_ BSTR* pbstrDisplayName) override;
private:
    int m_refCount;
};
#endif