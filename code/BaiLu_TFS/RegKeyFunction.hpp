#ifndef _WIN_INPUT_REG_KEY_FUNCTION_H_
#define _WIN_INPUT_REG_KEY_FUNCTION_H_
#include <string>
class CRegKeyFunction
{
public:
	static bool InstallRegKeyValues();
	static bool UnInstallRegKeyValues();
private:
	static std::wstring m_RegInfo_Prefix_CLSID;
	static std::wstring m_RegInfo_Key_InProSvr32;
	static std::wstring m_RegInfo_Key_ThreadModel;
	static std::wstring m_TEXTSERVICE_DESC;
	static std::wstring m_TEXTSERVICE_MODEL;//        L"Apartment"
};

#endif