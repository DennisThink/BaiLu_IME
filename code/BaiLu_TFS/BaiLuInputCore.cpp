#include "BaiLuInputCore.hpp"
#include "CommonFunction.hpp"
#include "BaiLuEditSession.hpp"
#include "BaiLu_DeleteBeforeEditSession.hpp"
#include "private.hpp"
#include "SimpleCandidateGenerator.h"
#include "SimpleQuanPinGenerator.h"
#include "RimeCandidateGenerator.h"
#include "LocalTcpGenerator.h"
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

void CBaiLuInputCore::InsertWordToWindow(const std::string& strWord)
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

void CBaiLuInputCore::OnThreadTimer()
{
	g_logger.Info("OnThreadTimer");
	m_strOldUserInput = m_strNewUserInput;
	m_strNewUserInput.clear();
	for (const auto& item : m_vecWord)
	{
		m_strNewUserInput += item;
	}
	if (m_strOldUserInput != m_strNewUserInput)
	{
		m_vecCandidate.clear();
		if (m_generator)
		{
			
			auto result = m_generator->Generate(m_strNewUserInput, 5);
			for (const auto& item : result.m_candidates)
			{
				m_vecCandidate.push_back(item.m_strChinese);
			}
		}
		UpdateCandidateByPageIndex();
	}
}

CBaiLuInputCore::CBaiLuInputCore()
{
	g_candidateWindow = nullptr;
	m_pCurTfContext = nullptr;
	m_curSelectedIndex = 0;
	//m_generator = std::make_unique<SimpleCandidateGenerator>();
	m_generator = std::make_unique<CLocalTcpGenerator>();
	//m_generator = std::make_unique<CRimeCandiateGenerator>();
	m_clientID = 0;
	m_nPageCount = 5;
	m_nPageIndex = 0;
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
	
	m_timer.start(std::chrono::milliseconds(500), [this]()->void {
		this->OnThreadTimer();
	});

}
CBaiLuInputCore::~CBaiLuInputCore()
{
	//g_logger.Info("CBaiLuInputCore::~CBaiLuInputCore");
	m_timer.stop();
}
void CBaiLuInputCore::OnCandidatePrevPage()
{
	while (m_nPageIndex > 0)
	{
		m_nPageIndex--;
	}
	UpdateCandidateByPageIndex();
}

void CBaiLuInputCore::OnCandidateNextPage()
{
	while ((m_nPageIndex + 1) * m_nPageCount < m_vecCandidate.size())
	{
		m_nPageIndex++;
	}
	UpdateCandidateByPageIndex();
}

void CBaiLuInputCore::UpdateCandidateByPageIndex()
{
	if (g_candidateWindow)
	{
		std::vector<std::string> result;
		std::size_t nStart = m_nPageIndex * m_nPageCount;
		std::size_t nCount = m_vecCandidate.size();
		for (int i = 0; i < m_nPageCount; i++)
		{
			if ((nStart + i) < nCount)
			{
				result.push_back(m_vecCandidate[nStart + i]);
				g_logger.Info("Candidates: {}", m_vecCandidate[nStart + i]);
			}
			else
			{
				break;
			}
		}
		std::string strUserInput(m_vecWord.begin(), m_vecWord.end());
		g_candidateWindow->SetUserInput(strUserInput);
		g_candidateWindow->SetCandidates(result);
		g_candidateWindow->Show();
	}
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
		char inputChar = static_cast<char>(keyInfo._keyValue);
		
		// Handle character key input for normal text input
		m_vecWord.push_back(inputChar);
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
			std::string selectedWord = std::to_string(keyInfo._keyValue);
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
					std::string selectedWord = m_vecCandidate[m_curSelectedIndex];
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
					std::size_t nCount = m_vecWord.size();
					std::vector<char> newVector;
					for (std::size_t i = 0; i < nCount - 1; i++)
					{
						newVector.push_back(m_vecWord[i]);
					}
					m_vecWord = newVector;
				}
				else
				{
					if (g_candidateWindow)
					{
						g_candidateWindow->Hide();
					}
				}
			}
			else
			{
				DeleteWordByBackSpace();
			}
		}
		else if(keyInfo._keyValue == VK_PRIOR)
		{
			OnCandidatePrevPage();
		}
		else if (keyInfo._keyValue == VK_NEXT)
		{
			OnCandidateNextPage();
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