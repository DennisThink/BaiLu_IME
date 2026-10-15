#include "BaiLuInputMethodInterface.hpp"
#include "BaiLuInputMethodClass.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
HRESULT ClassCreateInstance(_In_opt_ IUnknown* pUnkOuter, _In_ REFIID riid, _COM_Outptr_ void** ppvObj)
{
    //g_logger.Info("CSampleIME::CreateInstance Enter");
   

    if (ppvObj == nullptr)
    {
        g_logger.Error("{} {}", __FILE__, __LINE__);
        return E_INVALIDARG;
    }

    *ppvObj = nullptr;

    if (nullptr != pUnkOuter)
    {
        g_logger.Error("{} {}", __FILE__, __LINE__);
        return CLASS_E_NOAGGREGATION;
    }

    CBaiLuInputMethodClass* pClass = CBaiLuInputMethodClass::GetSingleInstance();
    HRESULT hr = S_OK;
    if (pClass == nullptr)
    {
        g_logger.Error("{} {}", __FILE__, __LINE__);
        return E_OUTOFMEMORY;
    }

    hr = pClass->QueryInterface(riid, ppvObj);

    pClass->Release();

    //g_logger.Info("CSampleIME::CreateInstance Leave");
    return hr;
}