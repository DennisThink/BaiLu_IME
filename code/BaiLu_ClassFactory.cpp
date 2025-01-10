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
    LogUtil::LogInfo("AddRef");
    m_refCount++;
    return m_refCount;
}

STDMETHODIMP_(ULONG) CBaiLuClassFactory::Release(void)
{
    LogUtil::LogInfo("Release");
    m_refCount--;
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

CBaiLuClassFactory::CBaiLuClassFactory(const REFCLSID lValue):m_rclsid(lValue)
{
    //GUID gid;
    //_rclsid = gid;
}

bool CBaiLuClassFactory::IsEqualGID(const REFCLSID lValue)
{
    return IsEqualIID(this->m_rclsid, lValue);
}