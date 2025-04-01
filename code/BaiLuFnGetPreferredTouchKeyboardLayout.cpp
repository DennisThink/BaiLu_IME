#include "BaiLuFnGetPreferredTouchKeyboardLayout.hpp"
CBaiLuFnGetPreferredTouchKeyBoardLayout::CBaiLuFnGetPreferredTouchKeyBoardLayout()
{

}

CBaiLuFnGetPreferredTouchKeyBoardLayout::~CBaiLuFnGetPreferredTouchKeyBoardLayout()
{

}

HRESULT STDMETHODCALLTYPE CBaiLuFnGetPreferredTouchKeyBoardLayout::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuFnGetPreferredTouchKeyBoardLayout::AddRef(void)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuFnGetPreferredTouchKeyBoardLayout::Release(void)
{
    return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuFnGetPreferredTouchKeyBoardLayout::GetLayout(
    /* [out] */ __RPC__out TKBLayoutType* pTKBLayoutType,
    __RPC__in WORD* pwPreferredLayoutId)
{
    return 0;
}

STDMETHODIMP CBaiLuFnGetPreferredTouchKeyBoardLayout::GetDisplayName(_Out_ BSTR* pbstrDisplayName)
{
    return 0;
}