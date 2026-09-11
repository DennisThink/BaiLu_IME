#include "BaiLu_ClassFactory.hpp"
#include "GlobalValues.hpp"
#include "Log.hpp"
#include "BaiLuInputMethodInterface.hpp"
CBaiLuClassFactory* CBaiLuClassFactory::m_pInstance = nullptr;
CBaiLuClassFactory* CBaiLuClassFactory::GetSingleInstance()
{
    LogUtil::LogInfo("GetSingleInstance");
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
    LogUtil::LogInfo("QueryInterface");
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
    LogUtil::LogInfo("CBaiLuClassFactory AddRef %d", m_refCount);
    return m_refCount;
}

STDMETHODIMP_(ULONG) CBaiLuClassFactory::Release(void)
{
    LogUtil::LogInfo("Release");
    m_refCount--;
    LogUtil::LogInfo("CBaiLuClassFactory Release %d", m_refCount);
    return m_refCount;
}

// IClassFactory methods
STDMETHODIMP CBaiLuClassFactory::CreateInstance(_In_opt_ IUnknown* pUnkOuter, _In_ REFIID riid, _COM_Outptr_ void** ppvObj)
{
    LogUtil::LogInfo("CreateInstance");
    ClassCreateInstance(pUnkOuter, riid, ppvObj);
    return 0;
}
STDMETHODIMP CBaiLuClassFactory::LockServer(BOOL fLock)
{
    LogUtil::LogInfo("LockServer");
    return 0;
}

CBaiLuClassFactory::CBaiLuClassFactory(REFCLSID lValue):m_rclsid(lValue)
{
    LogUtil::LogInfo("CBaiLuClassFactory::CBaiLuClassFactory");
    this->m_refCount = 0;
}

bool CBaiLuClassFactory::IsEqualGID(REFCLSID lValue)
{
    LogUtil::LogInfo("CBaiLuClassFactory::IsEqualGID");
    bool bResult = IsEqualIID(this->m_rclsid, lValue);
    if (!bResult)
    {
        LogUtil::LogInfo("lValue Data1:%x  this Data1:%x", lValue.Data1, this->m_rclsid.Data1);
        LogUtil::LogInfo("lValue Data2:%x  this Data2:%x", lValue.Data2, this->m_rclsid.Data2);
        LogUtil::LogInfo("lValue Data3:%x  this Data3:%x", lValue.Data3, this->m_rclsid.Data3);
        LogUtil::LogInfo("lValue Data4:%x  this Data4:%x", lValue.Data4, this->m_rclsid.Data4);
    }
    return bResult;
}

bool CBaiLuClassFactory::DestroySingleInstance()
{
    LogUtil::LogInfo("CBaiLuClassFactory::DestroySingleInstance");
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
    return true;
}