#include "BaiLuInputMethodInterface.hpp"
#include "BaiLuInputMethodClass.hpp"
#include "Log.hpp"
HRESULT ClassCreateInstance(_In_opt_ IUnknown* pUnkOuter, _In_ REFIID riid, _COM_Outptr_ void** ppvObj)
{
    LogUtil::LogInfo("CSampleIME::CreateInstance Enter");
   

    if (ppvObj == nullptr)
    {
        LogUtil::LogError(__FILE__, __LINE__);
        return E_INVALIDARG;
    }

    *ppvObj = nullptr;

    if (nullptr != pUnkOuter)
    {
        LogUtil::LogError(__FILE__, __LINE__);
        return CLASS_E_NOAGGREGATION;
    }

    CBaiLuInputMethodClass* pClass = CBaiLuInputMethodClass::GetSingleInstance();
    HRESULT hr = S_OK;
    if (pClass == nullptr)
    {
        LogUtil::LogError(__FILE__, __LINE__);
        return E_OUTOFMEMORY;
    }

    hr = pClass->QueryInterface(riid, ppvObj);

    pClass->Release();

    LogUtil::LogInfo("CSampleIME::CreateInstance Leave");
    return hr;
}