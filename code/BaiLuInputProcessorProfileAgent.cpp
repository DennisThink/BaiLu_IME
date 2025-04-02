#include "BaiLuInputProcessorProfileAgent.hpp"
#include "Log.hpp"
CBaiLuInputProcessorProfileAgent::CBaiLuInputProcessorProfileAgent()
{
    LogUtil::LogInfo(TEXT("CBaiLuInputProcessorProfileAgent::CBaiLuInputProcessorProfileAgent"));
    _pInputProcessorProfile = nullptr;
}

CBaiLuInputProcessorProfileAgent::~CBaiLuInputProcessorProfileAgent()
{
    LogUtil::LogInfo(TEXT("CBaiLuInputProcessorProfileAgent::~CBaiLuInputProcessorProfileAgent"));
    if (_pInputProcessorProfile) {
        _pInputProcessorProfile->Release();
        _pInputProcessorProfile = nullptr;
    }
}

HRESULT CBaiLuInputProcessorProfileAgent::CreateInstance()
{
    LogUtil::LogInfo(TEXT("CBaiLuInputProcessorProfileAgent::CreateInstance"));
    HRESULT	hr = CoCreateInstance(CLSID_TF_InputProcessorProfiles, nullptr, CLSCTX_INPROC_SERVER,
        IID_ITfInputProcessorProfiles, (void**)&_pInputProcessorProfile);

    return hr;
}

HRESULT CBaiLuInputProcessorProfileAgent::GetCurrentLanguage(_Out_ LANGID* plangid)
{
    LogUtil::LogInfo(TEXT("CBaiLuInputProcessorProfileAgent::GetCurrentLanguage"));
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
    LogUtil::LogInfo(TEXT("CBaiLuInputProcessorProfileAgent::GetDefaultLanguageProfile"));
    if (_pInputProcessorProfile)
    {
        return _pInputProcessorProfile->GetDefaultLanguageProfile(langid, catid, pclsid, pguidProfile);
    }
    else
    {
        return E_FAIL;
    }
}
