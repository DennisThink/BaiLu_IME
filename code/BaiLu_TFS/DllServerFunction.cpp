#include "DllServerFunction.hpp"
#include "RegKeyFunction.hpp"
#include "RegProfileFunction.hpp"
#include "RegCategoryFunction.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
extern "C"
{
    DLL_EXPORT HRESULT DllRegisterServer(void)
    {
        //g_logger.Info("DllRegisterServer");
        CRegKeyFunction::InstallRegKeyValues();
        CRegProfileFunction::InstallProfile();
        CRegCategoryFunction::InstallRegCategory();
        return S_OK;
    }


    DLL_EXPORT HRESULT DllUnregisterServer(void)
    {
        //g_logger.Info("DllUnregisterServer");
        CRegKeyFunction::UnInstallRegKeyValues();
        CRegProfileFunction::UninstallProfile();
        CRegCategoryFunction::UninstallRegCategory();
        return S_OK;
    }

}

