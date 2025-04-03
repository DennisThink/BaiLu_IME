#include "Log.hpp"
#include "GlobalValues.hpp"
#include <windows.h>
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID pvReserved)
{
    DWORD pID = GetCurrentProcessId();
    std::string processName = GlobalValue::GetProcessName(pID);
    LogUtil::LogInfo("DllMain %s", processName.c_str());
    if (processName == "regsvr32.exe" || processName == "NOTEPAD.EXE")
    {
        switch (dwReason)
        {
        case DLL_PROCESS_ATTACH: {
            LogUtil::OpenLogFile();
            LogUtil::LogInfo("DLL_PROCESS_ATTACH");
            GlobalValue::UnSetClassFactoryInitValue();
            InitializeCriticalSection(&GlobalValue::g_cs);
            GlobalValue::SetClassFactoryInitValue();
            GlobalValue::SetInstanceHandle(hInstance);

        }break;

        case DLL_PROCESS_DETACH: {
            LogUtil::LogInfo("DLL_PROCESS_DETACH");
            LogUtil::CloseLogFile();
            GlobalValue::UnSetClassFactoryInitValue();
            //DeleteCriticalSection(&GlobalValue::g_cs);
        }break;

        case DLL_THREAD_ATTACH: {
            LogUtil::LogInfo("DLL_THREAD_ATTACH");
        }break;

        case DLL_THREAD_DETACH: {
            LogUtil::LogInfo("DLL_THREAD_DETACH");
        }break;
        default: {
            LogUtil::LogInfo("Should not Go Here");
        }break;
        }
        LogUtil::LogInfo("DllMain TRUE %s", processName.c_str());
        return TRUE;
    }
    else
    {
        LogUtil::LogInfo("DllMain FALSE %s", processName.c_str());
        return FALSE;
    }
}
