#include "DllServerFunction.hpp"
#include "Log.hpp"
#include "RegKeyFunction.hpp"
#include "RegProfileFunction.hpp"
extern "C"
{
    DLL_EXPORT HRESULT DllRegisterServer(void)
    {
        LogUtil::LogInfo("DllRegisterServer");
        CRegKeyFunction::InstallRegKeyValues();
        CRegProfileFunction::InstallProfile();
        return S_OK;
    }


    DLL_EXPORT HRESULT DllUnregisterServer(void)
    {
        LogUtil::LogInfo("DllUnregisterServer");
        CRegKeyFunction::UnInstallRegKeyValues();
        CRegProfileFunction::UninstallProfile();
        return S_OK;
    }

}

