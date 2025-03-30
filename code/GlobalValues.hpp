#ifndef _WIN_INPUT_DEMO_GLOBAL_H_
#define _WIN_INPUT_DEMO_GLOBAL_H_
#include <windows.h>
#include <iostream>
namespace GlobalValue
{
	bool SetInstanceHandle(HINSTANCE hInstance);
	bool SetClassFactoryInitValue();
	bool UnSetClassFactoryInitValue();
	bool IsClassFactoryInit();
	HINSTANCE GetInstanceHandle();
	CLSID GetInputMethod_CLSID();
	CLSID GetInputMethod_ProfileGuid();
	GUID GetSampleIMEGuidDisplayAttributeConverted();
	GUID GetSampleIMEGuidDisplayAttributeInput();
	LANGID GetLanguageId();
	const wchar_t* GetInputMethodLayoutString();
	const wchar_t* GetInputMethodLayoutFileName();
	const wchar_t* GetInputMethodLayoutText();
	const wchar_t* GetInputMethodTipPath();
	const wchar_t* Get_TEXTSERVICE_DESC();
	const unsigned int Get_TEXTSERVICE_DESC_LENGTH();
	BOOL CLSIDToString(REFGUID refGUID, _Out_writes_(39) WCHAR* pCLSIDString);
	static CRITICAL_SECTION g_cs;
};

class CIMECommonValues
{
public:
	static CIMECommonValues* GetInstance();
	bool SetInstanceHandle(HINSTANCE hInstance);
	HINSTANCE GetInstanceHandle();
	CLSID GetInputMethod_CLSID();
	const wchar_t* GetInputMethodLayoutString();
	const wchar_t* GetInputMethodLayoutFileName();
	const wchar_t* GetInputMethodLayoutText();
	const wchar_t* GetInputMethodTipPath();
	const wchar_t* Get_TEXTSERVICE_DESC();
	const unsigned int Get_TEXTSERVICE_DESC_LENGTH();
	BOOL CLSIDToString(REFGUID refGUID, _Out_writes_(39) WCHAR* pCLSIDString);
private:
	CIMECommonValues* m_ptr;
	CIMECommonValues();

};
#endif