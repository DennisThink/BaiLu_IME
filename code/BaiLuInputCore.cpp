#include "BaiLuInputCore.hpp"
#include "CommonFunction.hpp"
#include "BaiLuEditSession.hpp"
#include "private.hpp"
#include "Log.hpp"
void CBaiLuInputCore::DealOnKeyDown(WPARAM wParam, LPARAM lParam)
{
	LogUtil::LogInfo("CBaiLuInputCore::DealOnKeyDown wParam=%d lParam=%ld", wParam, lParam);
	LogKeyDownAndUp(wParam, lParam, "DealOnKeyDown");
}
void CBaiLuInputCore::DealOnKeyUp(WPARAM wParam, LPARAM lParam)
{
	LogUtil::LogInfo("CBaiLuInputCore::DealOnKeyUp wParam=%d lParam=%ld", wParam, lParam);
	LogKeyDownAndUp(wParam, lParam, "DealOnKeyUp");
	ShowWordBySpace(wParam, lParam);
}
void CBaiLuInputCore::SetCurTfContext(ITfContext* pContext)
{
	m_pCurTfContext = pContext;
	LogUtil::LogInfo("CBaiLuInputCore::SetCurTfContext");
}
void CBaiLuInputCore::SetClientID(TfClientId clientID)
{
	m_clientID = clientID;
	LogUtil::LogInfo("CBaiLuInputCore::SetClientID");
}
void CBaiLuInputCore::ShowWordBySpace(WPARAM wParam, LPARAM lParam)
{

	std::string strWord;
	LONG vCode = (wParam);
	if (vCode == VK_SPACE)
	{
		for (const auto& word : m_vecWord)
		{
			strWord += word;
		}
		LogUtil::LogInfo("CBaiLuInputCore::ShowWordBySpace: %s", strWord.c_str());
		m_vecWord.clear();
		InsertWordToWindow(strWord);
	}
	else
	{
		UINT vCode = UINT(wParam);
		std::string strCodeName = VirtualKeyCodeToString(vCode);
		m_vecWord.push_back(strCodeName);
	}
}

ITfContext* CBaiLuInputCore::_GetFocusContext()
{
	ITfContext* pContext = m_pCurTfContext;
	return pContext;
}

void CBaiLuInputCore::_UpdateComposition(ITfContext* pContext, const std::string& strText)
{

}
void CBaiLuInputCore::InsertWordToWindow(const std::string& strWord)
{
	LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: %s", strWord.c_str());
	
	if (!this->m_pCurTfContext)
	{
		LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: m_pCurTfContext is null");
		return;
	}
	BaiLuEditSession* session =
		new BaiLuEditSession(
			m_pCurTfContext,
			strWord
		);

	HRESULT sessionResult = E_FAIL;

	HRESULT hr = m_pCurTfContext->RequestEditSession(
		m_clientID,
		session,
		TF_ES_READWRITE,
		&sessionResult
	);

	if(hr != S_OK)
	{
		LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: RequestEditSession failed");
	}
	if(sessionResult != S_OK)
	{
		LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: EditSession failed");
	}
	session->Release();
}

void CBaiLuInputCore::LogKeyDownAndUp(WPARAM wParam, LPARAM lParam, const std::string method)
{
	LogUtil::LogInfo("CBaiLuInputCore::LogKeyDownAndUp");
	UINT vCode = UINT(wParam);
	std::string strCodeName = VirtualKeyCodeToString(vCode);
	char buff[1024] = { 0 };
	sprintf(buff, "CBaiLuInputCore Key %s  Name:%s  Code:%d  Code2: %d\n", method.c_str(), strCodeName.c_str(), vCode, (UINT)(lParam));
	std::string strLog(buff);
	LogUtil::LogInfo("%s", strLog.c_str());
}