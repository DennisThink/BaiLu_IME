#include "BaiLuFunctionProvider.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();

HRESULT CBaiLuFunctionProvider::CreateInstance(CBaiLuFunctionProvider** ppOut)
{
    CBaiLuFunctionProvider* pInst = new CBaiLuFunctionProvider();
    if (nullptr != pInst && ppOut != nullptr)
    {
        *ppOut = pInst;
        return S_OK;
    }
    return -1;
}


CBaiLuFunctionProvider::CBaiLuFunctionProvider()
{
    //g_logger.Info("CBaiLuFunctionProvider::CBaiLuFunctionProvider");
    m_refCount = 1;
}
CBaiLuFunctionProvider::~CBaiLuFunctionProvider()
{
    //g_logger.Info("CBaiLuFunctionProvider::~CBaiLuFunctionProvider");
}

HRESULT STDMETHODCALLTYPE CBaiLuFunctionProvider::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    //g_logger.Info("CBaiLuFunctionProvider::QueryInterface");
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuFunctionProvider::AddRef(void)
{
    m_refCount++;
    //g_logger.Info("CBaiLuFunctionProvider::AddRef {} ", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuFunctionProvider::Release(void)
{
    m_refCount--;
    //g_logger.Info("CBaiLuFunctionProvider::Release {} ", m_refCount);
	ULONG nRet = m_refCount;
    if(m_refCount == 0)
    {
        delete this;
	}
    return nRet;
}

HRESULT STDMETHODCALLTYPE  CBaiLuFunctionProvider::GetType(
    /* [out] */ __RPC__out GUID* pguid)
{
    //g_logger.Info("CBaiLuFunctionProvider::GetType");
    return 0;
}

HRESULT STDMETHODCALLTYPE  CBaiLuFunctionProvider::GetDescription(
    /* [out] */ __RPC__deref_out_opt BSTR* pbstrDesc)
{
    //g_logger.Info("CBaiLuFunctionProvider::GetDescription");
    return 0;
}

HRESULT STDMETHODCALLTYPE  CBaiLuFunctionProvider::GetFunction(
    /* [in] */ __RPC__in REFGUID rguid,
    /* [in] */ __RPC__in REFIID riid,
    /* [iid_is][out] */ __RPC__deref_out_opt IUnknown** ppunk)
{
    //g_logger.Info("CBaiLuFunctionProvider::GetFunction");
    return 0;
}