#ifndef _BAI_LU_INPUT_CORE_HPP_
#define _BAI_LU_INPUT_CORE_HPP_
#include <wtypes.h>
#include <string>
#include <vector>
#include "private.hpp"
enum class KeyType
{
	NoneKey,
	CharacterKey,
	NumberKey,
	ControlKey,
	ModifierKey
};
struct KeyInfo
{
	KeyType _type;
	int _keyValue;
};



class CBaiLuInputCore
{
public:
	static CBaiLuInputCore* GetInstance()
	{
		static CBaiLuInputCore instance;
		return &instance;
	}

public:
	void DealOnKeyDown(WPARAM wParam, LPARAM lParam);
	void DealOnKeyUp(WPARAM wParam, LPARAM lParam);
	void SetCurTfContext(ITfContext* pContext);
	void SetClientID(TfClientId clientID);
private:
	void LogKeyDownAndUp(WPARAM wParam, LPARAM lParam, const std::string method);
	void ShowWordBySpace(WPARAM wParam, LPARAM lParam);
	void InsertWordToWindow(const std::string& strWord);
	void _UpdateComposition(ITfContext* pContext, const std::string& strText);
	ITfContext* _GetFocusContext();
	KeyInfo GetKeyInfo(WPARAM wParam, LPARAM lParam);
private:
	std::vector<std::string> m_vecWord;
	CBaiLuInputCore();
	~CBaiLuInputCore();
	ITfContext* m_pCurTfContext;
	TfClientId m_clientID;
};
#endif