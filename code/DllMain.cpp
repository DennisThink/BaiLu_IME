#include "Log.hpp"
#include "GlobalValues.hpp"
#include <windows.h>
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID pvReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH: {
        LogUtil::OpenLogFile();
        LogUtil::LogInfo("DLL_PROCESS_ATTACH");
        InitializeCriticalSection(&GlobalValue::g_cs);
        GlobalValue::SetInstanceHandle(hInstance);
    }break;

    case DLL_PROCESS_DETACH: {
        LogUtil::LogInfo("DLL_PROCESS_DETACH");
        LogUtil::CloseLogFile();
        DeleteCriticalSection(&GlobalValue::g_cs);
    }break;

    case DLL_THREAD_ATTACH: {
        LogUtil::LogInfo("DLL_THREAD_ATTACH");
    }break;

    case DLL_THREAD_DETACH: {
        LogUtil::LogInfo("DLL_THREAD_DETACH");
    }break;
    default:{
        LogUtil::LogInfo("Should not Go Here");
    }break;
    }

    return TRUE;
}
