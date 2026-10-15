#include "BaiLuInputProcessorProfileAgent.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
CBaiLuInputProcessorProfileAgent::CBaiLuInputProcessorProfileAgent()
{
    //g_logger.Info(("CBaiLuInputProcessorProfileAgent::CBaiLuInputProcessorProfileAgent"));
    _pInputProcessorProfile = nullptr;
}

CBaiLuInputProcessorProfileAgent::~CBaiLuInputProcessorProfileAgent()
{
    //g_logger.Info(("CBaiLuInputProcessorProfileAgent::~CBaiLuInputProcessorProfileAgent"));
    if (_pInputProcessorProfile) {
        _pInputProcessorProfile->Release();
        _pInputProcessorProfile = nullptr;
    }
}

HRESULT CBaiLuInputProcessorProfileAgent::CreateInstance()
{
    //g_logger.Info("CBaiLuInputProcessorProfileAgent::CreateInstance");
    HRESULT	hr = CoCreateInstance(CLSID_TF_InputProcessorProfiles, nullptr, CLSCTX_INPROC_SERVER,
        IID_ITfInputProcessorProfiles, (void**)&_pInputProcessorProfile);

    return hr;
}

HRESULT CBaiLuInputProcessorProfileAgent::GetCurrentLanguage(_Out_ LANGID* plangid)
{
    //g_logger.Info(("CBaiLuInputProcessorProfileAgent::GetCurrentLanguage"));
    if (_pInputProcessorProfile)
    {
        return _pInputProcessorProfile->GetCurrentLanguage(plangid);
    }
    else
    {
        return E_FAIL;
    }
}

HRESULT CBaiLuInputProcessorProfileAgent::GetDefaultLanguageProfile(LANGID langid, REFGUID catid, _Out_ CLSID* pclsid, _Out_ GUID* pguidProfile)
{
    //g_logger.Info(("CBaiLuInputProcessorProfileAgent::GetDefaultLanguageProfile"));
    if (_pInputProcessorProfile)
    {
        return _pInputProcessorProfile->GetDefaultLanguageProfile(langid, catid, pclsid, pguidProfile);
    }
    else
    {
        return E_FAIL;
    }
}
