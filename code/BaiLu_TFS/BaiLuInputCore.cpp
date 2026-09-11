#include "BaiLuInputCore.hpp"
#include "CommonFunction.hpp"
#include "BaiLuEditSession.hpp"
#include "private.hpp"
#include "Log.hpp"
#include "../BaiLu_CandidateGenerator/source/SimpleCandidateGenerator.h"
#include "../BaiLu_CandidateWindow/source/CandidateWindow.h"
#include "../BaiLu_CandidateWindow/source/ListCandidateView.h"
#include "GlobalValues.hpp"
static std::unique_ptr<CandidateWindow> g_candidateWindow;
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
	LONG vCode = (wParam);
	if (vCode == VK_SPACE)
	{
		std::string strWord;
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
		std::string strWord;
		for (auto item : m_vecWord)
		{
			strWord += item;
		}
		SimpleCandidateGenerator candidateGenerator;
		std::wstring strUserInput(strWord.begin(),strWord.end());
		auto candidates = candidateGenerator.Generate(strUserInput,5);
		if(g_candidateWindow)
		{
			g_candidateWindow->SetCandidates(candidates);
			g_candidateWindow->Show();
		}
		else
		{
			LogUtil::LogInfo("CBaiLuInputCore::ShowWordBySpace: g_candidateWindow is null");
		}

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

CBaiLuInputCore::CBaiLuInputCore()
{
	g_candidateWindow = nullptr;
	m_pCurTfContext = nullptr;
	m_clientID = 0;
	LogUtil::LogInfo("CBaiLuInputCore::CBaiLuInputCore");
	auto pListView= std::make_unique<ListCandidateView>();
	if(nullptr != pListView)
	{
		g_candidateWindow = std::make_unique<CandidateWindow>(std::move(pListView));
		if (g_candidateWindow)
		{
			g_candidateWindow->Create(GlobalValue::GetInstanceHandle());
			g_candidateWindow->Move(300, 300);
			g_candidateWindow->Show();
		}
		else
		{
			LogUtil::LogInfo("CBaiLuInputCore::CBaiLuInputCore g_candidateWindow is null");
		}
	}
	else
	{
		LogUtil::LogInfo("CBaiLuInputCore::CBaiLuInputCore pListView is null");
	}
	

}
CBaiLuInputCore::~CBaiLuInputCore()
{
	LogUtil::LogInfo("CBaiLuInputCore::~CBaiLuInputCore");
}

KeyInfo CBaiLuInputCore::GetKeyInfo(WPARAM wParam, LPARAM lParam)
{
	if (wParam >= 'A' && wParam <= 'Z')
	{
		return KeyInfo{ KeyType::CharacterKey,
				 static_cast<int>(wParam + ('a' - 'A')) };
	}

	if (wParam >= '0' && wParam <= '9')
	{
		return KeyInfo{ KeyType::NumberKey,
				 static_cast<int>(wParam - '0') };
	}

	if (wParam == VK_RETURN)
	{
		return KeyInfo{ KeyType::ControlKey, VK_RETURN };
	}

	if (wParam == VK_ESCAPE)
	{
		return KeyInfo{ KeyType::ControlKey, VK_ESCAPE };
	}

	if (wParam == VK_BACK)
	{
		return { KeyType::ControlKey, VK_BACK };
	}

	if (wParam == VK_CONTROL ||
		wParam == VK_SHIFT ||
		wParam == VK_MENU)
	{
		return KeyInfo{ KeyType::ModifierKey, static_cast<int>(wParam) };
	}

	return { KeyType::NoneKey, 0 };
}