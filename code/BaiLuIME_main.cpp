
#include "private.hpp"
#include "Log.hpp"
#include "BaiLu_ClassFactory.hpp"
#include "GlobalValues.hpp"
static CBaiLuClassFactory* g_pClassFactory[1] = { nullptr };
_Check_return_
STDAPI  DllGetClassObject(
    _In_ REFCLSID rclsid,
    _In_ REFIID riid,
    _Outptr_ void** ppv)
{
    LogUtil::LogInfo("DllGetClassObject");
    LogUtil::LogTrace(__FILE__, __LINE__);
    if (g_pClassFactory[0] == nullptr)
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        //EnterCriticalSection(&GlobalValue::g_cs);
        // need to check ref again after grabbing mutex
        if (g_pClassFactory[0] == nullptr)
        {
            LogUtil::LogTrace(__FILE__, __LINE__);
            g_pClassFactory[0] = CBaiLuClassFactory::GetSingleInstance();
            g_pClassFactory[0]->AddRef();
            LogUtil::LogInfo("DllGetClassObject %s %d", __FILE__, __LINE__);
        }
        else
        {
            LogUtil::LogTrace(__FILE__, __LINE__);
        }
        //LeaveCriticalSection(&GlobalValue::g_cs);
    }
    else
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
    }

    if (IsEqualIID(riid, IID_IClassFactory) ||
        IsEqualIID(riid, IID_IUnknown))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        //for (int i = 0; i < ARRAYSIZE(g_pClassFactory); i++)
        {
            LogUtil::LogTrace(__FILE__, __LINE__);
            if (nullptr != g_pClassFactory[0] && g_pClassFactory[0]->IsEqualGID(rclsid))
            {
                LogUtil::LogTrace(__FILE__, __LINE__);
                LogUtil::LogInfo("DllGetClassObject %s %d", __FILE__, __LINE__);
                *ppv = (void*)g_pClassFactory[0];
                g_pClassFactory[0]->AddRef();
                //DllAddRef();    // class factory holds DLL ref count
                return S_OK;
            }
            else
            {
                LogUtil::LogTrace(__FILE__, __LINE__);
            }
        }
    }
    else
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
    }
    LogUtil::LogTrace(__FILE__, __LINE__);
    *ppv = nullptr;
    LogUtil::LogTrace(__FILE__, __LINE__);
    return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow(void)
{
    LogUtil::LogInfo("DllCanUnloadNow");
    EnterCriticalSection(&GlobalValue::g_cs);
    g_pClassFactory[0]->Release();
    CBaiLuClassFactory::DestroySingleInstance();
    g_pClassFactory[0] = nullptr;
    LeaveCriticalSection(&GlobalValue::g_cs);
    return S_OK;
}