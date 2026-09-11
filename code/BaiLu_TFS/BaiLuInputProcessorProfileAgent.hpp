#ifndef _BAI_LU_INPUT_PROCESSOR_PROFILE_AGENT_H_
#define _BAI_LU_INPUT_PROCESSOR_PROFILE_AGENT_H_
#include "private.hpp"
class CBaiLuInputProcessorProfileAgent
{
public:
    CBaiLuInputProcessorProfileAgent();
    ~CBaiLuInputProcessorProfileAgent();

    HRESULT CreateInstance();
    HRESULT GetCurrentLanguage(_Out_ LANGID* plangid);
    HRESULT GetDefaultLanguageProfile(LANGID langid, REFGUID catid, _Out_ CLSID* pclsid, _Out_ GUID* pguidProfile);

private:
    ITfInputProcessorProfiles* _pInputProcessorProfile;
};
#endif