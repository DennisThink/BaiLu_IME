#include "BaiLuFnGetPreferredTouchKeyboardLayout.hpp"
#include "Log.hpp"

HRESULT CBaiLuFnGetPreferredTouchKeyBoardLayout::CreateInstance(CBaiLuFnGetPreferredTouchKeyBoardLayout** ppOut)
{
    CBaiLuFnGetPreferredTouchKeyBoardLayout* pInst = new CBaiLuFnGetPreferredTouchKeyBoardLayout();
    if (nullptr != pInst && nullptr != ppOut)
    {
        *ppOut = pInst;
        return S_OK;
    }
    return -1;
}

CBaiLuFnGetPreferredTouchKeyBoardLayout::CBaiLuFnGetPreferredTouchKeyBoardLayout()
{
    LogUtil::LogInfo("CBaiLuFnGetPreferredTouchKeyBoardLayout::CBaiLuFnGetPreferredTouchKeyBoardLayout");
    m_refCount = 0;
}

CBaiLuFnGetPreferredTouchKeyBoardLayout::~CBaiLuFnGetPreferredTouchKeyBoardLayout()
{
    LogUtil::LogInfo("CBaiLuFnGetPreferredTouchKeyBoardLayout::~CBaiLuFnGetPreferredTouchKeyBoardLayout");
}

HRESULT STDMETHODCALLTYPE CBaiLuFnGetPreferredTouchKeyBoardLayout::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    LogUtil::LogInfo("CBaiLuFnGetPreferredTouchKeyBoardLayout::QueryInterface");
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
    m_refCount--;
    LogUtil::LogInfo("CBaiLuFnGetPreferredTouchKeyBoardLayout::Release %d",m_refCount);
    return m_refCount;
}

HRESULT STDMETHODCALLTYPE CBaiLuFnGetPreferredTouchKeyBoardLayout::GetLayout(
    /* [out] */ __RPC__out TKBLayoutType* pTKBLayoutType,
    __RPC__in WORD* pwPreferredLayoutId)
{
    LogUtil::LogInfo("CBaiLuFnGetPreferredTouchKeyBoardLayout::GetLayout");
    return 0;
}

STDMETHODIMP CBaiLuFnGetPreferredTouchKeyBoardLayout::GetDisplayName(_Out_ BSTR* pbstrDisplayName)
{
    LogUtil::LogInfo("CBaiLuFnGetPreferredTouchKeyBoardLayout::GetDisplayName");
    return 0;
}