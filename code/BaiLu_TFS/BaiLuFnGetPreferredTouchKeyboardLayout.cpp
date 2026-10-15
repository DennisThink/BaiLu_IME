#include "BaiLuFnGetPreferredTouchKeyboardLayout.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
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
    //g_logger.Info("CBaiLuFnGetPreferredTouchKeyBoardLayout::CBaiLuFnGetPreferredTouchKeyBoardLayout");
    m_refCount = 1;
}

CBaiLuFnGetPreferredTouchKeyBoardLayout::~CBaiLuFnGetPreferredTouchKeyBoardLayout()
{
    //g_logger.Info("CBaiLuFnGetPreferredTouchKeyBoardLayout::~CBaiLuFnGetPreferredTouchKeyBoardLayout");
}

HRESULT STDMETHODCALLTYPE CBaiLuFnGetPreferredTouchKeyBoardLayout::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    //g_logger.Info("CBaiLuFnGetPreferredTouchKeyBoardLayout::QueryInterface");
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuFnGetPreferredTouchKeyBoardLayout::AddRef(void)
{
    m_refCount++;
    //g_logger.Info("CBaiLuDisplayAttributeProvider::AddRef {}", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuFnGetPreferredTouchKeyBoardLayout::Release(void)
{
    m_refCount--;
    //g_logger.Info("CBaiLuFnGetPreferredTouchKeyBoardLayout::Release {}",m_refCount);
	ULONG nRet = m_refCount;
    if (m_refCount == 0)
    {
        delete this;
    }
    return nRet;
}

HRESULT STDMETHODCALLTYPE CBaiLuFnGetPreferredTouchKeyBoardLayout::GetLayout(
    /* [out] */ __RPC__out TKBLayoutType* pTKBLayoutType,
    __RPC__in WORD* pwPreferredLayoutId)
{
    //g_logger.Info("CBaiLuFnGetPreferredTouchKeyBoardLayout::GetLayout");
    return 0;
}

STDMETHODIMP CBaiLuFnGetPreferredTouchKeyBoardLayout::GetDisplayName(_Out_ BSTR* pbstrDisplayName)
{
    //g_logger.Info("CBaiLuFnGetPreferredTouchKeyBoardLayout::GetDisplayName");
    return 0;
}