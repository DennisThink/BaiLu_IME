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
	{
		KeyInfo keyInfo = GetKeyInfo(wParam, lParam);
		ProcessKeyInfo(keyInfo);
	}
}
void CBaiLuInputCore::SetCurTfContext(ITfContext* pContext)
{
	if(m_pCurTfContext != nullptr)
	{
		LogUtil::LogInfo("CBaiLuInputCore::SetCurTfContext: m_pCurTfContext is not null");
		m_pCurTfContext->Release();
	}
	else
	{
		LogUtil::LogInfo("CBaiLuInputCore::SetCurTfContext: m_pCurTfContext is null");
	}
	if(pContext == nullptr)
	{
		LogUtil::LogInfo("CBaiLuInputCore::SetCurTfContext: pContext is null");
	}
	else
	{
		LogUtil::LogInfo("CBaiLuInputCore::SetCurTfContext: pContext is not null");
		m_pCurTfContext = pContext;
		m_pCurTfContext->AddRef();
	}

	LogUtil::LogInfo("CBaiLuInputCore::SetCurTfContext");
}
void CBaiLuInputCore::SetClientID(TfClientId clientID)
{
	m_clientID = clientID;
	LogUtil::LogInfo("CBaiLuInputCore::SetClientID");
}
void CBaiLuInputCore::ShowWordBySpace(WPARAM wParam, LPARAM lParam)
{

}

ITfContext* CBaiLuInputCore::_GetFocusContext()
{
	ITfContext* pContext = m_pCurTfContext;
	return pContext;
}

void CBaiLuInputCore::_UpdateComposition(ITfContext* pContext, const std::string& strText)
{

}
void CBaiLuInputCore::InsertWordToWindow(const std::wstring& strWord)
{
	LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: %ls", strWord.c_str());
	LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: %s %d", __FILE__, __LINE__);
	if (!this->m_pCurTfContext)
	{
		LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: m_pCurTfContext is null");
		return;
	}
	LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: %s %d", __FILE__, __LINE__);
	BaiLuEditSession* session =
		new BaiLuEditSession(
			m_pCurTfContext,
			strWord
		);
	LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: %s %d", __FILE__, __LINE__);
	if(nullptr == session)
	{
		LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: BaiLuEditSession is null");
		return;
	}
	LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: %s %d", __FILE__, __LINE__);
	HRESULT sessionResult = E_FAIL;

	// 注意：这里必须使用同步编辑会话,具体原因不清楚
	// 只使用 TF_ES_READWRITE 时，候选词提交可能出现
	// DoEditSession 已执行，但文本没有稳定插入的情况。
	HRESULT hr = m_pCurTfContext->RequestEditSession(
		m_clientID,
		session,
		TF_ES_READWRITE|TF_ES_SYNC,
		&sessionResult
	);
	LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: %s %d", __FILE__, __LINE__);

	if(FAILED(hr))
	{
		LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: RequestEditSession failed with HRESULT: 0x%08X", hr);
		return;
	}
	if(FAILED(sessionResult))
	{
		LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: EditSession failed with HRESULT: 0x%08X", sessionResult);
		return;
	}
	if(session)
	{
		session->Release();
		session = nullptr;
	}
	LogUtil::LogInfo("CBaiLuInputCore::InsertWordToWindow: %s %d", __FILE__, __LINE__);
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

bool CBaiLuInputCore::IsChandidateWindowShow()const
{
	if (g_candidateWindow)
	{
		return IsWindowVisible(g_candidateWindow->GetHandle());
	}
	return false;
}
void CBaiLuInputCore::ProcessKeyInfo(const KeyInfo& keyInfo)
{
	switch (keyInfo._type)
	{
	case KeyType::NoneKey:
	{
		LogUtil::LogInfo("CBaiLuInputCore::ProcessKeyInfo NoneKey");
	}break;
	case KeyType::CharacterKey:
	{
		LogUtil::LogInfo("CBaiLuInputCore::ProcessKeyInfo CharacterKey: %c", keyInfo._keyValue);
		wchar_t inputChar = static_cast<wchar_t>(keyInfo._keyValue);
		
		// Handle character key input for normal text input
		if (inputChar == L' ')
		{
			
		}
		else
		{
			m_vecWord.push_back(inputChar);
			if (!m_vecWord.empty())
			{
				std::wstring strWord(m_vecWord.begin(), m_vecWord.end());
				m_vecCandidate.clear();
				m_vecCandidate = SimpleCandidateGenerator().Generate(strWord, 5);
				if(g_candidateWindow)
				{
					g_candidateWindow->SetCandidates(m_vecCandidate);
					g_candidateWindow->Show();
				}
				else
				{
					LogUtil::LogInfo("CBaiLuInputCore::ProcessKeyInfo g_candidateWindow is null");
				}
			}
		}
	}break;
	case KeyType::NumberKey:
	{
		LogUtil::LogInfo("CBaiLuInputCore::ProcessKeyInfo NumberKey: %d", keyInfo._keyValue);
		if (IsChandidateWindowShow())
		{
			// Handle number key selection for candidate window
			if(g_candidateWindow)
			{
				int index = keyInfo._keyValue; // Assuming number keys 1-9 correspond to candidate indices 0-8
				if(index >= 0 && index < m_vecCandidate.size())
				{
					g_candidateWindow->SetSelectedIndex(index);
				}
				else
				{
					LogUtil::LogInfo("CBaiLuInputCore::ProcessKeyInfo NumberKey: Invalid candidate index");
				}
			}
		}
		else
		{
			// Handle number key input for normal text input
			std::wstring selectedWord = std::to_wstring(keyInfo._keyValue);
			InsertWordToWindow(selectedWord);
		}
	}break;
	case KeyType::ControlKey:
	{
		LogUtil::LogInfo("CBaiLuInputCore::ProcessKeyInfo ControlKey: %d", keyInfo._keyValue);
		if(keyInfo._keyValue == VK_SPACE)
		{
			if (g_candidateWindow)
			{
				int index = g_candidateWindow->GetSelectedIndex();
				if (index >= 0 && index < m_vecCandidate.size())
				{
					std::wstring selectedWord = m_vecCandidate[index];
					InsertWordToWindow(selectedWord);
					m_vecWord.clear();
					m_vecCandidate.clear();
					g_candidateWindow->Hide();
				}
				else
				{
					LogUtil::LogInfo("CBaiLuInputCore::ProcessKeyInfo Space: Invalid candidate index");
				}
			}
		}
	}break;
	default:
		break;
	}
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
	if(wParam == VK_SPACE)
	{
		return KeyInfo{ KeyType::ControlKey, VK_SPACE };
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