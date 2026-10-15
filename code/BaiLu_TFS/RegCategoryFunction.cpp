#include "RegCategoryFunction.hpp"
#include "private.hpp"
#include "GlobalValues.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
static const GUID SupportCategories[] = {
    GUID_TFCAT_TIP_KEYBOARD
};

bool CRegCategoryFunction::InstallRegCategory()
{
    //g_logger.Info("RegisterCategories");
    ITfCategoryMgr* pCategoryMgr = nullptr;
    HRESULT hr = S_OK;

    hr = CoCreateInstance(CLSID_TF_CategoryMgr, NULL, CLSCTX_INPROC_SERVER, IID_ITfCategoryMgr, (void**)&pCategoryMgr);
    if (FAILED(hr))
    {
        return false;
    }

	if (1 == sizeof(SupportCategories) / sizeof(GUID))
    {
        hr = pCategoryMgr->RegisterCategory(
            GlobalValue::GetInputMethod_CLSID(),
            SupportCategories[0],
            GlobalValue::GetInputMethod_CLSID());
    }

    pCategoryMgr->Release();

    return (hr == S_OK);
}


bool CRegCategoryFunction::UninstallRegCategory()
{
    //g_logger.Info("UnregisterCategories");
    ITfCategoryMgr* pCategoryMgr = nullptr;
    HRESULT hr = S_OK;

    hr = CoCreateInstance(CLSID_TF_CategoryMgr, NULL, CLSCTX_INPROC_SERVER, IID_ITfCategoryMgr, (void**)&pCategoryMgr);
    if (FAILED(hr))
    {
        return false;
    }

    for(auto& guid : SupportCategories)
    {
        pCategoryMgr->UnregisterCategory(
            GlobalValue::GetInputMethod_CLSID(), 
            guid, 
            GlobalValue::GetInputMethod_CLSID());
    }

    pCategoryMgr->Release();
	return true;
}