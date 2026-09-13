#ifndef _BAI_LU_INPUT_CORE_HPP_
#define _BAI_LU_INPUT_CORE_HPP_
#include <wtypes.h>
#include <string>
#include <vector>
#include "private.hpp"
/*
* 这个类是整个输入法的核心类，负责处理键盘输入，管理候选词窗口，以及与文本框进行交互。
* 总的来说就是把所有其他的接口串起来，形成一个完整的输入法。
*/
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
	void InsertWordToWindow(const std::wstring& strWord);
	void _UpdateComposition(ITfContext* pContext, const std::string& strText);
	ITfContext* _GetFocusContext();
	KeyInfo GetKeyInfo(WPARAM wParam, LPARAM lParam);
	void ProcessKeyInfo(const KeyInfo& keyInfo);
	bool IsChandidateWindowShow()const;
private:
	std::vector<wchar_t> m_vecWord;
	std::vector<std::wstring> m_vecCandidate;
	CBaiLuInputCore();
	~CBaiLuInputCore();
	ITfContext* m_pCurTfContext;
	TfClientId m_clientID;
};
#endif