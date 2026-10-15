#include "BaiLuInputCore.hpp"
#include "CommonFunction.hpp"
#include "BaiLuEditSession.hpp"
#include "BaiLu_DeleteBeforeEditSession.hpp"
#include "private.hpp"
#include "SimpleCandidateGenerator.h"
#include "SimpleQuanPinGenerator.h"
#include "RimeCandidateGenerator.h"
#include "CandidateWindow.h"
#include "ListCandidateView.h"
#include "GlobalValues.hpp"
static std::unique_ptr<CandidateWindow> g_candidateWindow;
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
void CBaiLuInputCore::DealOnKeyDown(WPARAM wParam, LPARAM lParam)
{
	//g_logger.Info("CBaiLuInputCore::DealOnKeyDown wParam={} lParam={}", wParam, lParam);
	LogKeyDownAndUp(wParam, lParam, "DealOnKeyDown");
}
void CBaiLuInputCore::DealOnKeyUp(WPARAM wParam, LPARAM lParam)
{
	//g_logger.Info("CBaiLuInputCore::DealOnKeyUp wParam={} lParam={}", wParam, lParam);
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
		//g_logger.Info("CBaiLuInputCore::SetCurTfContext: m_pCurTfContext is not null");
		m_pCurTfContext->Release();
	}
	else
	{
		//g_logger.Info("CBaiLuInputCore::SetCurTfContext: m_pCurTfContext is null");
	}
	if(pContext == nullptr)
	{
		//g_logger.Info("CBaiLuInputCore::SetCurTfContext: pContext is null");
	}
	else
	{
		//g_logger.Info("CBaiLuInputCore::SetCurTfContext: pContext is not null");
		m_pCurTfContext = pContext;
		m_pCurTfContext->AddRef();
	}

	//g_logger.Info("CBaiLuInputCore::SetCurTfContext");
}
void CBaiLuInputCore::SetClientID(TfClientId clientID)
{
	m_clientID = clientID;
	//g_logger.Info("CBaiLuInputCore::SetClientID");
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

void CBaiLuInputCore::DeleteWordByBackSpace()
{
	if (nullptr != this-> m_pCurTfContext)
	{
		CBaiLuDeleteEditSession* pSession = new CBaiLuDeleteEditSession(this->m_pCurTfContext);
		HRESULT sessionResult = E_FAIL;

		// 注意：这里必须使用同步编辑会话,具体原因不清楚
		// 只使用 TF_ES_READWRITE 时，候选词提交可能出现
		// DoEditSession 已执行，但文本没有稳定插入的情况。
		HRESULT hr = m_pCurTfContext->RequestEditSession(
			m_clientID,
			pSession,
			TF_ES_READWRITE | TF_ES_SYNC,
			&sessionResult
		);
		if (pSession)
		{
			pSession->Release();
			pSession = nullptr;
		}
	}

}

void CBaiLuInputCore::InsertWordToWindow(const std::wstring& strWord)
{
	//g_logger.Info("CBaiLuInputCore::InsertWordToWindow: {}", strWord.c_str());
	//g_logger.Info("CBaiLuInputCore::InsertWordToWindow: {} {}", __FILE__, __LINE__);
	if (!this->m_pCurTfContext)
	{
		//g_logger.Info("CBaiLuInputCore::InsertWordToWindow: m_pCurTfContext is null");
		return;
	}
	//g_logger.Info("CBaiLuInputCore::InsertWordToWindow:{} {}", __FILE__, __LINE__);
	BaiLuEditSession* session =
		new BaiLuEditSession(
			m_pCurTfContext,
			strWord
		);
	//g_logger.Info("CBaiLuInputCore::InsertWordToWindow: {} {}", __FILE__, __LINE__);
	if(nullptr == session)
	{
		//g_logger.Info("CBaiLuInputCore::InsertWordToWindow: BaiLuEditSession is null");
		return;
	}
	//g_logger.Info("CBaiLuInputCore::InsertWordToWindow: {} {}", __FILE__, __LINE__);
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
	//g_logger.Info("CBaiLuInputCore::InsertWordToWindow: {} {}", __FILE__, __LINE__);

	if(FAILED(hr))
	{
		//g_logger.Info("CBaiLuInputCore::InsertWordToWindow: RequestEditSession failed with HRESULT: {}", hr);
		return;
	}
	if(FAILED(sessionResult))
	{
		//g_logger.Info("CBaiLuInputCore::InsertWordToWindow: EditSession failed with HRESULT: {}", sessionResult);
		return;
	}
	if(session)
	{
		session->Release();
		session = nullptr;
	}
	//g_logger.Info("CBaiLuInputCore::InsertWordToWindow: {} {}", __FILE__, __LINE__);
}

void CBaiLuInputCore::LogKeyDownAndUp(WPARAM wParam, LPARAM lParam, const std::string method)
{
	//g_logger.Info("CBaiLuInputCore::LogKeyDownAndUp");
	UINT vCode = UINT(wParam);
	std::string strCodeName = VirtualKeyCodeToString(vCode);
	char buff[1024] = { 0 };
	//sprintf(buff, "CBaiLuInputCore Key {} Name:{}  Code:{}  Code2: {}\n", method.c_str(), strCodeName.c_str(), vCode, (UINT)(lParam));
	std::string strLog(buff);
	//g_logger.Info("{}", strLog.c_str());
}

CBaiLuInputCore::CBaiLuInputCore()
{
	g_candidateWindow = nullptr;
	m_pCurTfContext = nullptr;
	m_curSelectedIndex = 0;
	//m_generator = std::make_unique<SimpleCandidateGenerator>();
	m_generator = std::make_unique<CSimpleQuanPinGenerator>();
	//m_generator = std::make_unique<CRimeCandiateGenerator>();
	m_clientID = 0;
	//g_logger.Info("CBaiLuInputCore::CBaiLuInputCore");
	auto pListView= std::make_unique<ListCandidateView>();
	if(nullptr != pListView)
	{
		g_candidateWindow = std::make_unique<CandidateWindow>();
		if (g_candidateWindow)
		{
			g_candidateWindow->Create(NULL, NULL);
			g_candidateWindow->Move(300, 300);
			g_candidateWindow->Hide();
		}
		else
		{
			//g_logger.Info("CBaiLuInputCore::CBaiLuInputCore g_candidateWindow is null");
		}
	}
	else
	{
		//g_logger.Info("CBaiLuInputCore::CBaiLuInputCore pListView is null");
	}
	

}
CBaiLuInputCore::~CBaiLuInputCore()
{
	//g_logger.Info("CBaiLuInputCore::~CBaiLuInputCore");
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
		//g_logger.Info("CBaiLuInputCore::ProcessKeyInfo NoneKey");
	}break;
	case KeyType::CharacterKey:
	{
		//g_logger.Info("CBaiLuInputCore::ProcessKeyInfo CharacterKey: {}", keyInfo._keyValue);
		wchar_t inputChar = static_cast<wchar_t>(keyInfo._keyValue);
		
		// Handle character key input for normal text input

		m_vecWord.push_back(inputChar);
		if (!m_vecWord.empty())
		{
			std::wstring strWord(m_vecWord.begin(), m_vecWord.end());
			m_vecCandidate.clear();
			if (m_generator)
			{
				//m_vecCandidate = m_generator->Generate(strWord, 5);
			}
			if(g_candidateWindow)
			{
				g_candidateWindow->SetUserInput(strWord);
				//g_candidateWindow->SetCandidates(m_vecCandidate);
				g_candidateWindow->Show();
			}
			else
			{
				//g_logger.Info("CBaiLuInputCore::ProcessKeyInfo g_candidateWindow is null");
			}
		}
	}break;
	case KeyType::NumberKey:
	{
		//g_logger.Info("CBaiLuInputCore::ProcessKeyInfo NumberKey: {}", keyInfo._keyValue);
		if (IsChandidateWindowShow())
		{
			// Handle number key selection for candidate window
			if(g_candidateWindow)
			{
				int index = keyInfo._keyValue-1; // Assuming number keys 1-9 correspond to candidate indices 0-8
				if(index >= 0 && index < m_vecCandidate.size())
				{
					m_curSelectedIndex = index;
					g_candidateWindow->SetSelectedIndex(index);
				}
				else
				{
					//g_logger.Info("CBaiLuInputCore::ProcessKeyInfo NumberKey: Invalid candidate index");
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
		//g_logger.Info("CBaiLuInputCore::ProcessKeyInfo ControlKey: {}", keyInfo._keyValue);
		if(keyInfo._keyValue == VK_SPACE)
		{
			if (g_candidateWindow)
			{
				if (m_curSelectedIndex >= 0 && m_curSelectedIndex < m_vecCandidate.size())
				{
					std::wstring selectedWord = m_vecCandidate[m_curSelectedIndex];
					InsertWordToWindow(selectedWord);
					m_vecWord.clear();
					m_vecCandidate.clear();
					g_candidateWindow->Hide();
					m_curSelectedIndex = 0;
				}
				else
				{
					//g_logger.Info("CBaiLuInputCore::ProcessKeyInfo Space: Invalid candidate index");
				}
			}
		}
		else if (keyInfo._keyValue == VK_BACK)
		{
			if (IsChandidateWindowShow())
			{
				if (!m_vecWord.empty())
				{
					auto endIter = m_vecWord.end();
					endIter--;
					std::wstring strWord(m_vecWord.begin(), endIter);
					m_vecCandidate.clear();
					if (m_generator)
					{
						//m_vecCandidate = m_generator->Generate(strWord, 5);
					}
					if (g_candidateWindow)
					{
						g_candidateWindow->SetUserInput(strWord);
						//g_candidateWindow->SetCandidates(m_vecCandidate);
						g_candidateWindow->Show();
					}
					else
					{
						//g_logger.Info("CBaiLuInputCore::ProcessKeyInfo g_candidateWindow is null");
					}
					m_vecWord.clear();
					for (auto item = strWord.begin(); item != strWord.end(); item++)
					{
						m_vecWord.push_back(*item);
					}
				}
			}
			else
			{
				DeleteWordByBackSpace();
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

bool CBaiLuInputCore::DealActiveEx(ITfThreadMgr* pThreadMgr, TfClientId tfClientId, DWORD dwFlags)
{
	//g_logger.Info("CBaiLuInputCore::DealActiveEx");
	return true;
}

bool CBaiLuInputCore::DealDeactivate()
{
	//g_logger.Info("CBaiLuInputCore::DealDeactivate");
	if (nullptr != g_candidateWindow)
	{
		g_candidateWindow->Hide();
	}
	return true;
}
HRESULT CBaiLuInputCore::DealTestKeyDown(WPARAM wParam, LPARAM lParam, BOOL* pfEaten)
{
	KeyInfo info = GetKeyInfo(wParam, lParam);
	switch (info._type)
	{
		case KeyType::ControlKey:
		{
			if (info._keyValue == VK_BACK)
			{
				if (IsChandidateWindowShow())
				{
					*pfEaten = TRUE;
				}
				else
				{
					*pfEaten = FALSE;
				}
			}
			else
			{
				*pfEaten = TRUE;
			}
		}break;
		default:
		{
			*pfEaten = TRUE;
		}break;
	}
	return S_OK;

}

HRESULT CBaiLuInputCore::DealTestKeyUp(WPARAM wParam, LPARAM lParam, BOOL* pfEaten)
{
	KeyInfo info = GetKeyInfo(wParam, lParam);
	switch (info._type)
	{
	case KeyType::ControlKey:
	{
		if (info._keyValue == VK_BACK)
		{
			if (IsChandidateWindowShow())
			{
				*pfEaten = TRUE;
			}
			else
			{
				*pfEaten = FALSE;
			}
		}
		else
		{
			*pfEaten = TRUE;
		}
	}break;
	default:
	{
		*pfEaten = TRUE;
	}break;
	}
	return S_OK;
}