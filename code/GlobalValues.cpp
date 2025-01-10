#include "GlobalValues.hpp"
namespace GlobalValue
{
    static HINSTANCE g_dllInstanceHandle=0;
    //0b2b6f3b-edd4-dd16-d726-2befa061c0ee
    static CLSID InputMethod_CLSID = {
    0x0b2b6f3b,
    0xedd4,
    0xdd16,
    { 0xd7, 0x26, 0x2b, 0xef, 0xa0, 0x61, 0xc0, 0xee }
    };


    //{BA6312FA-263B-4406-BF02-BEDBFE5FC2F8}
    static CLSID InputProfile_GUID = {
        0xBA6312FA,
        0x263B,
        0x4406,
        {0xBF,0x02,0xBE,0xDB,0xFE,0x5F,0xC2,0xF8}
    };

    const static wchar_t g_dllName[] = L"BaiLuIME.dll";
    static const WCHAR TEXTSERVICE_DESC[] = L"°×Â¶ÊäÈë·¨";
#define CLSID_STRLEN    (38)  // strlen("{xxxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxx}")
	
    CLSID GetInputMethod_CLSID()
    {
        return InputMethod_CLSID;
    }

    CLSID GetInputMethod_ProfileGuid()
    {
        return InputProfile_GUID;
    }

    LANGID GetLanguageId()
    {
        LANGID result = MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED);
        //LANGID result = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
        return result;
    }
    bool SetInstanceHandle(HINSTANCE hInstance)
    {
        g_dllInstanceHandle = hInstance;
        return true;
    }

    HINSTANCE GetInstanceHandle()
    {
        return g_dllInstanceHandle;
    }


    const wchar_t* GetInputMethodLayoutFileName()
	{	
		return g_dllName;
	}

	const wchar_t* GetInputMethodLayoutText()
	{
		const static wchar_t g_layoutText[] = L"BaiLuIME.dll";;
		return g_layoutText;
	}

    const wchar_t * Get_TEXTSERVICE_DESC()
    {
        
        return TEXTSERVICE_DESC;
    }

    const unsigned int Get_TEXTSERVICE_DESC_LENGTH()
    {
        std::size_t count = sizeof(TEXTSERVICE_DESC);
        return count;
    }


    const BYTE GuidSymbols[] = {
        3, 2, 1, 0, '-', 5, 4, '-', 7, 6, '-', 8, 9, '-', 10, 11, 12, 13, 14, 15
    };

    const WCHAR HexDigits[] = L"0123456789ABCDEF";

    BOOL CLSIDToString(REFGUID refGUID, _Out_writes_(39) WCHAR* pCLSIDString)
    {
        WCHAR* pTemp = pCLSIDString;
        const BYTE* pBytes = (const BYTE*)&refGUID;

        DWORD j = 0;
        pTemp[j++] = L'{';
        for (int i = 0; i < sizeof(GuidSymbols) && j < (CLSID_STRLEN - 2); i++)
        {
            if (GuidSymbols[i] == '-')
            {
                pTemp[j++] = L'-';
            }
            else
            {
                pTemp[j++] = HexDigits[(pBytes[GuidSymbols[i]] & 0xF0) >> 4];
                pTemp[j++] = HexDigits[(pBytes[GuidSymbols[i]] & 0x0F)];
            }
        }

        pTemp[j++] = L'}';
        return TRUE;
    }
}


CIMECommonValues::CIMECommonValues()
{
    m_ptr = nullptr;
}

CIMECommonValues* CIMECommonValues::GetInstance() 
{
    static CIMECommonValues constValue;
    return &constValue;
}
bool CIMECommonValues::SetInstanceHandle(HINSTANCE hInstance)
{
    return false;
}
HINSTANCE CIMECommonValues::GetInstanceHandle()
{
    return 0;
}
CLSID CIMECommonValues::GetInputMethod_CLSID()
{
    CLSID gid;
    return gid;
}
const wchar_t* CIMECommonValues::GetInputMethodLayoutString()
{
    return nullptr;
}
const wchar_t* CIMECommonValues::GetInputMethodLayoutFileName()
{
    return nullptr;
}
const wchar_t* CIMECommonValues::GetInputMethodLayoutText()
{
    return nullptr;
}
const wchar_t* CIMECommonValues::GetInputMethodTipPath()
{
    return nullptr;
}
const wchar_t* CIMECommonValues::Get_TEXTSERVICE_DESC()
{
    return nullptr;
}
const unsigned int CIMECommonValues::Get_TEXTSERVICE_DESC_LENGTH()
{
    return 0;
}
BOOL CIMECommonValues::CLSIDToString(REFGUID refGUID, _Out_writes_(39) WCHAR* pCLSIDString)
{
    return FALSE;
}