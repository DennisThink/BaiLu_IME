#include "BaiLuDisplayAttributeProvider.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();

HRESULT CBaiLuDisplayAttributeProvider::CreateInstance(CBaiLuDisplayAttributeProvider** ppOut)
{
    CBaiLuDisplayAttributeProvider* pInst = new CBaiLuDisplayAttributeProvider();
    if (nullptr != pInst && nullptr != ppOut)
    {
        *ppOut = pInst;
        return S_OK;
    }
    return -1;
}

CBaiLuDisplayAttributeProvider::CBaiLuDisplayAttributeProvider()
{
    //g_logger.Info("CBaiLuDisplayAttributeProvider::CBaiLuDisplayAttributeProvider");
    m_refCount = 1;
}
CBaiLuDisplayAttributeProvider::~CBaiLuDisplayAttributeProvider()
{
    //g_logger.Info("CBaiLuDisplayAttributeProvider::~CBaiLuDisplayAttributeProvider");
}
HRESULT STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    //g_logger.Info("CBaiLuDisplayAttributeProvider::QueryInterface");
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::AddRef(void)
{
    m_refCount++;
    //g_logger.Info("CBaiLuDisplayAttributeProvider::AddRef {}", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::Release(void)
{
    m_refCount--;
    //g_logger.Info("CBaiLuDisplayAttributeProvider::Release {}", m_refCount);
	ULONG ulRet = m_refCount;
    if (m_refCount == 0)
    {
        delete this;
    }
    return ulRet;
}
HRESULT STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::EnumDisplayAttributeInfo(
    /* [out] */ __RPC__deref_out_opt IEnumTfDisplayAttributeInfo** ppEnum)
{
    //g_logger.Info("CBaiLuDisplayAttributeProvider::EnumDisplayAttributeInfo");
    return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuDisplayAttributeProvider::GetDisplayAttributeInfo(
    /* [in] */ __RPC__in REFGUID guid,
    /* [out] */ __RPC__deref_out_opt ITfDisplayAttributeInfo** ppInfo)
{
    //g_logger.Info("CBaiLuDisplayAttributeProvider::GetDisplayAttributeInfo");
    return 0;
}