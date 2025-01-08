#include "RegCategoryFunction.hpp"
#include "Log.hpp"
#include "private.hpp"
#include "GlobalValues.hpp"
static const GUID SupportCategories[] = {
    GUID_TFCAT_TIP_KEYBOARD,
    GUID_TFCAT_DISPLAYATTRIBUTEPROVIDER,
    GUID_TFCAT_TIPCAP_UIELEMENTENABLED,
    GUID_TFCAT_TIPCAP_SECUREMODE,
    GUID_TFCAT_TIPCAP_COMLESS,
    GUID_TFCAT_TIPCAP_INPUTMODECOMPARTMENT,
    GUID_TFCAT_TIPCAP_IMMERSIVESUPPORT,
    GUID_TFCAT_TIPCAP_SYSTRAYSUPPORT,
};
bool CRegCategoryFunction::InstallRegCategory()
{
    LogUtil::LogInfo(("RegisterCategories"));
    ITfCategoryMgr* pCategoryMgr = nullptr;
    HRESULT hr = S_OK;

    hr = CoCreateInstance(CLSID_TF_CategoryMgr, NULL, CLSCTX_INPROC_SERVER, IID_ITfCategoryMgr, (void**)&pCategoryMgr);
    if (FAILED(hr))
    {
        return FALSE;
    }

    for each(GUID guid in SupportCategories)
    {
        hr = pCategoryMgr->RegisterCategory(
            GlobalValue::GetInputMethod_CLSID(),
            guid, 
            GlobalValue::GetInputMethod_CLSID());
    }

    pCategoryMgr->Release();

    return (hr == S_OK);
}


bool CRegCategoryFunction::UninstallRegCategory()
{
    LogUtil::LogInfo("UnregisterCategories");
    ITfCategoryMgr* pCategoryMgr = S_OK;
    HRESULT hr = S_OK;

    hr = CoCreateInstance(CLSID_TF_CategoryMgr, NULL, CLSCTX_INPROC_SERVER, IID_ITfCategoryMgr, (void**)&pCategoryMgr);
    if (FAILED(hr))
    {
        return false;
    }

    for each(GUID guid in SupportCategories)
    {
        pCategoryMgr->UnregisterCategory(
            GlobalValue::GetInputMethod_CLSID(), 
            guid, 
            GlobalValue::GetInputMethod_CLSID());
    }

    pCategoryMgr->Release();
	return false;
}