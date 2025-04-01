#include "BaiLuFnGetPreferredTouchKeyboardLayout.hpp"
#include "Log.hpp"
CBaiLuFnGetPreferredTouchKeyBoardLayout::CBaiLuFnGetPreferredTouchKeyBoardLayout()
{
    m_refCount = 0;
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
    m_refCount++;
    LogUtil::LogInfo("CBaiLuDisplayAttributeProvider::AddRef %d", m_refCount);
    return m_refCount;
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