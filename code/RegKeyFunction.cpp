#include "RegKeyFunction.hpp"
#include "GlobalValues.hpp"
#include <windows.h>
#include <iostream>
#include <winnt.h>
#include "Log.hpp"
#define CLSID_STRLEN    (38)  // strlen("{xxxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxx}")

std::wstring CRegKeyFunction::m_RegInfo_Prefix_CLSID=L"CLSID\\";;
std::wstring CRegKeyFunction::m_RegInfo_Key_InProSvr32= L"InProcServer32";
std::wstring CRegKeyFunction::m_RegInfo_Key_ThreadModel=L"ThreadingModel";
std::wstring CRegKeyFunction::m_TEXTSERVICE_DESC=L"BaiLuIME";
std::wstring CRegKeyFunction::m_TEXTSERVICE_MODEL=L"Apartment";
bool CRegKeyFunction::InstallRegKeyValues()
{
    DWORD copiedStringLen = 0;
    HKEY regKeyHandle = nullptr;
    HKEY regSubkeyHandle = nullptr;
    BOOL ret = FALSE;
    const std::size_t KeyLength = 128;
    WCHAR* achIMEKey = new WCHAR[KeyLength];
    memset(achIMEKey, 0, sizeof(WCHAR) * KeyLength);
    WCHAR achFileName[MAX_PATH] = { '\0' };
    if (!GlobalValue::CLSIDToString(GlobalValue::GetInputMethod_CLSID(), achIMEKey + m_RegInfo_Prefix_CLSID.length() - 1))
    {
        LogUtil::LogInfo("GlobalValue::CLSIDToString Failed");
        LogUtil::LogTrace(__FILE__, __LINE__);
        return FALSE;
    }

    memcpy(achIMEKey, m_RegInfo_Prefix_CLSID.data(), m_RegInfo_Prefix_CLSID.length() - sizeof(WCHAR));
    if (RegCreateKeyExW(HKEY_CLASSES_ROOT, achIMEKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &regKeyHandle, &copiedStringLen) == ERROR_SUCCESS)
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        if (RegSetValueExW(regKeyHandle, NULL, 0, REG_SZ, (const BYTE*)(GlobalValue::Get_TEXTSERVICE_DESC()), GlobalValue::Get_TEXTSERVICE_DESC_LENGTH()) != ERROR_SUCCESS)
        {
            LogUtil::LogTrace(__FILE__, __LINE__);
            goto Exit;
        }

        if (RegCreateKeyExW(regKeyHandle, m_RegInfo_Key_InProSvr32.data(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &regSubkeyHandle, &copiedStringLen) == ERROR_SUCCESS)
        {
            LogUtil::LogTrace(__FILE__, __LINE__);
            copiedStringLen = GetModuleFileNameW(GlobalValue::GetInstanceHandle(), achFileName, ARRAYSIZE(achFileName));
            copiedStringLen = (copiedStringLen >= (MAX_PATH - 1)) ? MAX_PATH : (++copiedStringLen);
            if (RegSetValueEx(regSubkeyHandle, NULL, 0, REG_SZ, (const BYTE*)achFileName, (copiedStringLen) * sizeof(WCHAR)) != ERROR_SUCCESS)
            {
                LogUtil::LogTrace(__FILE__, __LINE__);
                goto Exit;
            }
            if (RegSetValueExW(regSubkeyHandle, m_RegInfo_Key_ThreadModel.data(), 0, REG_SZ, (const BYTE*)(m_TEXTSERVICE_MODEL.data()), (m_TEXTSERVICE_MODEL.length()) * sizeof(WCHAR)) != ERROR_SUCCESS)
            {
                LogUtil::LogTrace(__FILE__, __LINE__);
                goto Exit;
            }

            ret = TRUE;
        }
    }

Exit:
    if (regSubkeyHandle)
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        RegCloseKey(regSubkeyHandle);
        regSubkeyHandle = nullptr;
    }
    if (regKeyHandle)
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        RegCloseKey(regKeyHandle);
        regKeyHandle = nullptr;
    }
    return ret;
}


LONG RecurseDeleteKey(_In_ HKEY hParentKey, _In_ WCHAR* lpszKey)
{
    HKEY regKeyHandle = nullptr;
    LONG res = 0;
    FILETIME time;
    WCHAR stringBuffer[256] = { '\0' };
    DWORD size = ARRAYSIZE(stringBuffer);

    if (RegOpenKeyW(hParentKey, lpszKey, &regKeyHandle) != ERROR_SUCCESS)
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        return ERROR_SUCCESS;
    }

    res = ERROR_SUCCESS;
    while (RegEnumKeyExW(regKeyHandle, 0, stringBuffer, &size, NULL, NULL, NULL, &time) == ERROR_SUCCESS)
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        stringBuffer[ARRAYSIZE(stringBuffer) - 1] = '\0';
        res = RecurseDeleteKey(regKeyHandle, stringBuffer);
        if (res != ERROR_SUCCESS)
        {
            LogUtil::LogTrace(__FILE__, __LINE__);
            break;
        }
        size = ARRAYSIZE(stringBuffer);
    }
    RegCloseKey(regKeyHandle);

    return res == ERROR_SUCCESS ? RegDeleteKeyW(hParentKey, lpszKey) : res;
}


bool CRegKeyFunction::UnInstallRegKeyValues()
{
    const std::size_t KeyLength = 128;
    WCHAR* achIMEKey = new WCHAR[KeyLength];
    memset(achIMEKey, 0, sizeof(WCHAR) * KeyLength);
    WCHAR achFileName[MAX_PATH] = { '\0' };
    if (!GlobalValue::CLSIDToString(GlobalValue::GetInputMethod_CLSID(), achIMEKey + m_RegInfo_Prefix_CLSID.length() - 1))
    {
        LogUtil::LogTrace(__FILE__, __LINE__);
        return FALSE;
    }

    memcpy(achIMEKey, m_RegInfo_Prefix_CLSID.data(), m_RegInfo_Prefix_CLSID.length() - sizeof(WCHAR));

    RecurseDeleteKey(HKEY_CLASSES_ROOT, achIMEKey);
    return false;
}