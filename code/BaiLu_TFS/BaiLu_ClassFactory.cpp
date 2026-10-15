#include "BaiLu_ClassFactory.hpp"
#include "GlobalValues.hpp"
#include "Logger.h"
#include "BaiLuInputMethodInterface.hpp"
CBaiLuClassFactory* CBaiLuClassFactory::m_pInstance = nullptr;
static auto& g_logger = BaiLu::Logger::Instance();
CBaiLuClassFactory* CBaiLuClassFactory::GetSingleInstance()
{
    //g_logger.Info("GetSingleInstance");
    if (nullptr == m_pInstance)
    {
        m_pInstance = new CBaiLuClassFactory(GlobalValue::GetInputMethod_CLSID());
        return m_pInstance;
    }
    else
    {
        return m_pInstance;
    }
}
// IUnknown methods
STDMETHODIMP CBaiLuClassFactory::QueryInterface(REFIID riid, _Outptr_ void** ppvObj)
{
    //g_logger.Info("QueryInterface");
    if (IsEqualIID(riid, IID_IClassFactory) || IsEqualIID(riid, IID_IUnknown))
    {
        *ppvObj = this;
        return NOERROR;
    }
    *ppvObj = nullptr;

    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) CBaiLuClassFactory::AddRef(void)
{
    m_refCount++;
    //g_logger.Info("CBaiLuClassFactory AddRef {}", m_refCount);
    return m_refCount;
}

STDMETHODIMP_(ULONG) CBaiLuClassFactory::Release(void)
{
    //g_logger.Info("Release");
    m_refCount--;
    //g_logger.Info("CBaiLuClassFactory Release {}", m_refCount);
	ULONG nRet = m_refCount;
	if (nRet == 0)
    {
        delete this;
    }
    return nRet;
}

// IClassFactory methods
STDMETHODIMP CBaiLuClassFactory::CreateInstance(_In_opt_ IUnknown* pUnkOuter, _In_ REFIID riid, _COM_Outptr_ void** ppvObj)
{
    //g_logger.Info("CreateInstance");
    ClassCreateInstance(pUnkOuter, riid, ppvObj);
    return 0;
}
STDMETHODIMP CBaiLuClassFactory::LockServer(BOOL fLock)
{
    //g_logger.Info("LockServer");
    return 0;
}

CBaiLuClassFactory::CBaiLuClassFactory(REFCLSID lValue):m_rclsid(lValue)
{
    //g_logger.Info("CBaiLuClassFactory::CBaiLuClassFactory");
    this->m_refCount = 0;
}

bool CBaiLuClassFactory::IsEqualGID(REFCLSID lValue)
{
    //g_logger.Info("CBaiLuClassFactory::IsEqualGID");
    bool bResult = IsEqualIID(this->m_rclsid, lValue);
    if (!bResult)
    {
        /*//g_logger.Info("lValue Data1:{}  this Data1:{}", lValue.Data1, this->m_rclsid.Data1);
        //g_logger.Info("lValue Data2:{}  this Data2:{}", lValue.Data2, this->m_rclsid.Data2);
        //g_logger.Info("lValue Data3:{}  this Data3:{}", lValue.Data3, this->m_rclsid.Data3);
        //g_logger.Info("lValue Data4:{}  this Data4:{}", lValue.Data4, this->m_rclsid.Data4);*/
    }
    return bResult;
}

bool CBaiLuClassFactory::DestroySingleInstance()
{
    //g_logger.Info("CBaiLuClassFactory::DestroySingleInstance");
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
    return true;
}