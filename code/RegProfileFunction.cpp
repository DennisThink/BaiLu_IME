#include "RegProfileFunction.hpp"
#include "Log.hpp"
#include "private.hpp"
#include "GlobalValues.hpp"
#include "BaiLuIME_resource.hpp"
bool CRegProfileFunction::InstallProfile()
{

    LogUtil::LogInfo("RegisterProfiles");
    HRESULT hr = S_FALSE;

    ITfInputProcessorProfileMgr* pITfInputProcessorProfileMgr = nullptr;
    hr = CoCreateInstance(CLSID_TF_InputProcessorProfiles, NULL, CLSCTX_INPROC_SERVER,
        IID_ITfInputProcessorProfileMgr, (void**)&pITfInputProcessorProfileMgr);
    if (FAILED(hr))
    {
        return FALSE;
    }

    WCHAR achIconFile[MAX_PATH] = { '\0' };
    DWORD cchA = 0;
    cchA = GetModuleFileNameW(GlobalValue::GetInstanceHandle(), achIconFile, MAX_PATH);
    cchA = cchA >= MAX_PATH ? (MAX_PATH - 1) : cchA;
    achIconFile[cchA] = '\0';

    size_t lenOfDesc = GlobalValue::Get_TEXTSERVICE_DESC_LENGTH();

    //TODO: We need solve this
    const int TEXTSERVICE_ICON_INDEX = 0;
    hr = pITfInputProcessorProfileMgr->RegisterProfile(GlobalValue::GetInputMethod_CLSID(),
        GlobalValue::GetLanguageId(),
        GlobalValue::GetInputMethod_ProfileGuid(),
        GlobalValue::Get_TEXTSERVICE_DESC(),
        static_cast<ULONG>(GlobalValue::Get_TEXTSERVICE_DESC_LENGTH()),
        achIconFile,
        cchA,
        (UINT)IDIS_BAILUIME, NULL, 0, TRUE, 0);

    if (FAILED(hr))
    {
        LogUtil::LogTrace(__FILE__,__LINE__);
        goto Exit;
    }

Exit:
    if (pITfInputProcessorProfileMgr)
    {
        pITfInputProcessorProfileMgr->Release();
    }

    return (hr == S_OK);
}

bool CRegProfileFunction::CRegProfileFunction::UninstallProfile()
{
    LogUtil::LogInfo("UnregisterProfiles");
    HRESULT hr = S_OK;

    ITfInputProcessorProfileMgr* pITfInputProcessorProfileMgr = nullptr;
    hr = CoCreateInstance(CLSID_TF_InputProcessorProfiles, NULL, CLSCTX_INPROC_SERVER,
        IID_ITfInputProcessorProfileMgr, (void**)&pITfInputProcessorProfileMgr);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    hr = pITfInputProcessorProfileMgr->UnregisterProfile(
        GlobalValue::GetInputMethod_CLSID(),
        GlobalValue::GetLanguageId(),
        GlobalValue::GetInputMethod_ProfileGuid(),
        0);
    if (FAILED(hr))
    {
        goto Exit;
    }
    

Exit:
    if (pITfInputProcessorProfileMgr)
    {
        pITfInputProcessorProfileMgr->Release();
    }
	return false;
}