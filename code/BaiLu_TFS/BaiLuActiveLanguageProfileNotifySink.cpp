#include "BaiLuActiveLanguageProfileNotifySink.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
HRESULT CBaiLuActiveLanguageProfileNotifySink::CreateInstance(CBaiLuActiveLanguageProfileNotifySink** ppOut)
{
    CBaiLuActiveLanguageProfileNotifySink* pInst = new CBaiLuActiveLanguageProfileNotifySink();
    if (nullptr != pInst && nullptr != ppOut)
    {
        *ppOut = pInst;
        return S_OK;
    }
    return -1;
}

CBaiLuActiveLanguageProfileNotifySink::CBaiLuActiveLanguageProfileNotifySink()
{
    m_refCount = 1;
	auto& logger = BaiLu::Logger::Instance();
    logger.Info("CBaiLuActiveLanguageProfileNotifySink::CBaiLuActiveLanguageProfileNotifySink {}", m_refCount);
}

CBaiLuActiveLanguageProfileNotifySink::~CBaiLuActiveLanguageProfileNotifySink()
{
    auto& logger = BaiLu::Logger::Instance();
    logger.Info("CBaiLuActiveLanguageProfileNotifySink::~CBaiLuActiveLanguageProfileNotifySink {}", m_refCount);
}

HRESULT STDMETHODCALLTYPE CBaiLuActiveLanguageProfileNotifySink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    auto& logger = BaiLu::Logger::Instance();
    logger.Info("CBaiLuActiveLanguageProfileNotifySink::QueryInterface {}", m_refCount);
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuActiveLanguageProfileNotifySink::AddRef(void)
{
    m_refCount++;
    auto& logger = BaiLu::Logger::Instance();
    logger.Info("CBaiLuActiveLanguageProfileNotifySink::AddRef {}", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuActiveLanguageProfileNotifySink::Release(void)
{
    m_refCount--;
    auto& logger = BaiLu::Logger::Instance();
    logger.Info("CBaiLuActiveLanguageProfileNotifySink::Release {}", m_refCount);
    ULONG nRet = m_refCount;
    if(m_refCount == 0)
    {
        delete this;
	}
    return nRet;
}


HRESULT STDMETHODCALLTYPE CBaiLuActiveLanguageProfileNotifySink::OnActivated(
    /* [in] */ __RPC__in REFCLSID clsid,
    /* [in] */ __RPC__in REFGUID guidProfile,
    /* [in] */ BOOL fActivated)
{
    auto& logger = BaiLu::Logger::Instance();
    logger.Info("CBaiLuActiveLanguageProfileNotifySink::OnActivated");
    return 0;
}