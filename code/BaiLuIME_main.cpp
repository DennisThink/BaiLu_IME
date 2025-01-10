
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
    return CLASS_E_CLASSNOTAVAILABLE;
    if (g_pClassFactory[0] == nullptr)
    {
        EnterCriticalSection(&GlobalValue::g_cs);
        // need to check ref again after grabbing mutex
        if (g_pClassFactory[0] == nullptr)
        {
            g_pClassFactory[0] = CBaiLuClassFactory::GetSingleInstance();
        }

        LeaveCriticalSection(&GlobalValue::g_cs);
    }

    if (IsEqualIID(riid, IID_IClassFactory) ||
        IsEqualIID(riid, IID_IUnknown))
    {
        for (int i = 0; i < ARRAYSIZE(g_pClassFactory); i++)
        {
            if (nullptr != g_pClassFactory[i])
                // &&
                //IsEqualGUID(rclsid, g_pClassFactory[i]->_rclsid))
            {
                *ppv = (void*)g_pClassFactory[i];
                //DllAddRef();    // class factory holds DLL ref count
                return NOERROR;
            }
        }
    }

    *ppv = nullptr;

    return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow(void)
{
    LogUtil::LogInfo("DllCanUnloadNow");
    return S_OK;
}