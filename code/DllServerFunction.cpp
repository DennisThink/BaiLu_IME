#include "DllServerFunction.hpp"
#include "Log.hpp"
#include "RegKeyFunction.hpp"
#include "RegProfileFunction.hpp"
#include "RegCategoryFunction.hpp"
extern "C"
{
    DLL_EXPORT HRESULT DllRegisterServer(void)
    {
        LogUtil::LogInfo("DllRegisterServer");
        CRegKeyFunction::InstallRegKeyValues();
        CRegProfileFunction::InstallProfile();
        CRegCategoryFunction::InstallRegCategory();
        return S_OK;
    }


    DLL_EXPORT HRESULT DllUnregisterServer(void)
    {
        LogUtil::LogInfo("DllUnregisterServer");
        CRegKeyFunction::UnInstallRegKeyValues();
        CRegProfileFunction::UninstallProfile();
        CRegCategoryFunction::UninstallRegCategory();
        return S_OK;
    }

}

