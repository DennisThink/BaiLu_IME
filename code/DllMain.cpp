#include "Log.hpp"
#include "GlobalValues.hpp"
#include <windows.h>
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID pvReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        LogUtil::OpenLogFile();
        LogUtil::LogInfo("DLL_PROCESS_ATTACH");
        GlobalValue::SetInstanceHandle(hInstance);
        break;

    case DLL_PROCESS_DETACH:
        LogUtil::LogInfo("DLL_PROCESS_DETACH");
        LogUtil::CloseLogFile();
        break;

    case DLL_THREAD_ATTACH:
        LogUtil::LogInfo("DLL_THREAD_ATTACH");
        break;

    case DLL_THREAD_DETACH:
        LogUtil::LogInfo("DLL_THREAD_DETACH");
        break;
    }

    return TRUE;
}
