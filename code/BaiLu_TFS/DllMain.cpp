#include "Logger.h"
#include "GlobalValues.hpp"
#include <windows.h>
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID pvReserved)
{
	auto& logger = BaiLu::Logger::Instance();
    DWORD pID = GetCurrentProcessId();
    std::string processName = GlobalValue::GetProcessName(pID);
	std::string strName(processName.begin(), processName.end());
    logger.Info("DllMain {}", pID);
    if (GlobalValue::IsWhiteListProcess(pID))
    {
        switch (dwReason)
        {
        case DLL_PROCESS_ATTACH: {
           
            logger.Info("DLL_PROCESS_ATTACH");
            if (!InitializeCriticalSectionAndSpinCount(&GlobalValue::g_cs, 0))
            {
                logger.Info("InitializeCriticalSectionAndSpinCount Failed");
                return FALSE;
            }
            else
            {
                logger.Info("InitializeCriticalSectionAndSpinCount Succeed");
                GlobalValue::UnSetClassFactoryInitValue();
                GlobalValue::SetClassFactoryInitValue();
                GlobalValue::SetInstanceHandle(hInstance);
            }

        }break;

        case DLL_PROCESS_DETACH: {
            logger.Info("DLL_PROCESS_DETACH");
            //LogUtil::CloseLogFile();
            GlobalValue::UnSetClassFactoryInitValue();
            DeleteCriticalSection(&GlobalValue::g_cs);
        }break;

        case DLL_THREAD_ATTACH: {
            logger.Info("DLL_THREAD_ATTACH");
        }break;

        case DLL_THREAD_DETACH: {
            logger.Info("DLL_THREAD_DETACH");
        }break;
        default: {
            logger.Info("Should not Go Here");
        }break;
        }
        logger.Info("DllMain TRUE {}", strName.c_str());
        return TRUE;
    }
    else
    {
        logger.Info("DllMain FALSE {}", strName.c_str());
        return FALSE;
    }
}
