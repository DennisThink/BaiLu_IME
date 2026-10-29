
#include "private.hpp"
#include "BaiLu_ClassFactory.hpp"
#include "GlobalValues.hpp"
#include <Psapi.h>
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
static CBaiLuClassFactory* g_pClassFactory[1] = { nullptr };

static std::string GetProcessName(DWORD pid)
{
    std::string result = "UNKNOWN";
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (hProcess != NULL) {
        TCHAR buffer[MAX_PATH];
        GetModuleBaseName(hProcess,NULL,buffer, MAX_PATH);
        result = std::string(buffer);
        g_logger.Info("GetModuleBaseNameA {}", buffer);
        GetModuleFileNameEx(hProcess, NULL, buffer, MAX_PATH);
        g_logger.Info("GetModuleFileNameEx {}", buffer);
        GetProcessImageFileName(hProcess,buffer, MAX_PATH);
        g_logger.Info("GetProcessImageFileNameA {}", buffer);
       
        CloseHandle(hProcess);
    }
    return result;
}

_Check_return_
STDAPI  DllGetClassObject(
    _In_ REFCLSID rclsid,
    _In_ REFIID riid,
    _Outptr_ void** ppv)
{
    DWORD pid = GetCurrentProcessId();
   
    if (GlobalValue::IsWhiteListProcess(pid))
    {
        InitializeCriticalSection(&GlobalValue::g_cs);
        GlobalValue::SetClassFactoryInitValue();
        g_logger.Info("DllGetClassObject");
        g_logger.Debug("{} {}",__FILE__, __LINE__);
        if (g_pClassFactory[0] == nullptr)
        {
            g_logger.Debug("{} {}",__FILE__, __LINE__);
            EnterCriticalSection(&GlobalValue::g_cs);
            // need to check ref again after grabbing mutex
            if (g_pClassFactory[0] == nullptr)
            {
                g_logger.Debug("{} {}",__FILE__, __LINE__);
                g_pClassFactory[0] = CBaiLuClassFactory::GetSingleInstance();
                g_pClassFactory[0]->AddRef();
                g_logger.Info("DllGetClassObject {} {}", __FILE__, __LINE__);
            }
            else
            {
                g_logger.Error("{} {}",__FILE__, __LINE__);
            }
            LeaveCriticalSection(&GlobalValue::g_cs);
        }
        else
        {
            g_logger.Error("{} {}",__FILE__, __LINE__);
        }

        if (IsEqualIID(riid, IID_IClassFactory) ||
            IsEqualIID(riid, IID_IUnknown))
        {
            g_logger.Debug("{} {}",__FILE__, __LINE__);
            //for (int i = 0; i < ARRAYSIZE(g_pClassFactory); i++)
            {
                g_logger.Debug("{} {}", __FILE__, __LINE__);
                if (nullptr != g_pClassFactory[0] && g_pClassFactory[0]->IsEqualGID(rclsid))
                {
                    g_logger.Debug("{} {}", __FILE__, __LINE__);
                    g_logger.Info("DllGetClassObject {} {}", __FILE__, __LINE__);
                    *ppv = (void*)g_pClassFactory[0];
                    g_pClassFactory[0]->AddRef();
                    //DllAddRef();    // class factory holds DLL ref count
                    return S_OK;
                }
                else
                {
                    g_logger.Error("{} {}", __FILE__, __LINE__);
                }
            }
        }
        else
        {
            g_logger.Error("{} {}", __FILE__, __LINE__);
        }
        g_logger.Debug("{} {}", __FILE__, __LINE__);
        *ppv = nullptr;
        g_logger.Debug("{} {}", __FILE__, __LINE__);
        return CLASS_E_CLASSNOTAVAILABLE;
    }
    else
    {
        *ppv = nullptr;
        g_logger.Error("{} {}", __FILE__, __LINE__);
        return CLASS_E_CLASSNOTAVAILABLE;
    }
}

STDAPI DllCanUnloadNow(void)
{
    DWORD pid = GetCurrentProcessId();
    if (GlobalValue::IsWhiteListProcess(pid))
    {
        g_logger.Info("DllCanUnloadNow");
        EnterCriticalSection(&GlobalValue::g_cs);
        g_pClassFactory[0]->Release();
        CBaiLuClassFactory::DestroySingleInstance();
        g_pClassFactory[0] = nullptr;
        LeaveCriticalSection(&GlobalValue::g_cs);
    }
    return S_OK;
}