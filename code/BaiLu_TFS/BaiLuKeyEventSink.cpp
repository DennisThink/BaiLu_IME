#include "BaiLuKeyEventSink.hpp"
#include "CommonFunction.hpp"
#include "BaiLuInputCore.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
HRESULT CBaiLuKeyEventSink::CreateInstance(CBaiLuKeyEventSink** pOut)
{
	CBaiLuKeyEventSink* pInst = new CBaiLuKeyEventSink();
	if (nullptr != pInst&& pOut != nullptr)
	{
		*pOut = pInst;
		return S_OK;
	}
	return -1;
}
CBaiLuKeyEventSink::CBaiLuKeyEventSink()
{
	m_refCount = 1;
	//g_logger.Info("CBaiLuKeyEventSink::CBaiLuKeyEventSink {}", m_refCount);
}

CBaiLuKeyEventSink::~CBaiLuKeyEventSink()
{
	//g_logger.Info("CBaiLuKeyEventSink::~CBaiLuKeyEventSink {}", m_refCount);
}
HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnSetFocus(
	/* [in] */ BOOL fForeground) 
{
	//g_logger.Info("CBaiLuKeyEventSink::~CBaiLuKeyEventSink {}", m_refCount);
	return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnTestKeyDown(
	/* [in] */ ITfContext* pic,
	/* [in] */ WPARAM wParam,
	/* [in] */ LPARAM lParam,
	/* [out] */ BOOL* pfEaten)
{
	//g_logger.Info("CBaiLuKeyEventSink::OnTestKeyDown {}", m_refCount);
	LogKeyDownAndUp(wParam, lParam, "OnTestKeyDown");
	CBaiLuInputCore* pInputCore = CBaiLuInputCore::GetInstance();
	if (pInputCore != nullptr)
	{
		pInputCore->DealTestKeyDown(wParam, lParam,pfEaten);
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnTestKeyUp(
	/* [in] */ ITfContext* pic,
	/* [in] */ WPARAM wParam,
	/* [in] */ LPARAM lParam,
	/* [out] */ BOOL* pfEaten)
{
	//g_logger.Info("CBaiLuKeyEventSink::OnTestKeyUp {}", m_refCount);
	LogKeyDownAndUp(wParam, lParam, "OnTestKeyUp");
	CBaiLuInputCore* pInputCore = CBaiLuInputCore::GetInstance();
	if (pInputCore != nullptr)
	{
		pInputCore->DealTestKeyDown(wParam, lParam, pfEaten);
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnKeyDown(
	/* [in] */ ITfContext* pic,
	/* [in] */ WPARAM wParam,
	/* [in] */ LPARAM lParam,
	/* [out] */ BOOL* pfEaten)
{
	//g_logger.Info("CBaiLuKeyEventSink::OnKeyDown {}", m_refCount);
	LogKeyDownAndUp(wParam, lParam, "OnKeyDown");
	*pfEaten = TRUE;

	CBaiLuInputCore* pInputCore = CBaiLuInputCore::GetInstance();
	if(pInputCore != nullptr)
	{
		pInputCore->DealOnKeyDown(wParam, lParam);
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnKeyUp(
	/* [in] */ ITfContext* pic,
	/* [in] */ WPARAM wParam,
	/* [in] */ LPARAM lParam,
	/* [out] */ BOOL* pfEaten)
{
	//g_logger.Info("CBaiLuKeyEventSink::OnKeyUp {}", m_refCount);
	LogKeyDownAndUp(wParam, lParam, "OnKeyUp");
	*pfEaten = TRUE;
	CBaiLuInputCore* pInputCore = CBaiLuInputCore::GetInstance();
	if (pInputCore != nullptr)
	{
		pInputCore->DealOnKeyUp(wParam, lParam);
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnPreservedKey(
	/* [in] */ ITfContext* pic,
	/* [in] */ REFGUID rguid,
	/* [out] */ BOOL* pfEaten)
{
	//g_logger.Info("CBaiLuKeyEventSink::OnPreservedKey {}", m_refCount);
	return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::QueryInterface(
	/* [in] */ REFIID riid,
	/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
	//g_logger.Info("CBaiLuKeyEventSink::QueryInterface {}", m_refCount);
	return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuKeyEventSink::AddRef(void) 
{
	m_refCount++;
	//g_logger.Info("CBaiLuKeyEventSink::AddRef {}", m_refCount);
	return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuKeyEventSink::Release(void) 
{
	m_refCount--;
	//g_logger.Info("CBaiLuKeyEventSink::Release {}", m_refCount);
	ULONG nRet = m_refCount;
	if(nRet == 0)
	{
		delete this;
	}
	return nRet;
}

void CBaiLuKeyEventSink::CheckRefCount() const
{
	//g_logger.Info("CBaiLuKeyEventSink::CheckRefCount {}", m_refCount);
}

void CBaiLuKeyEventSink::LogKeyDownAndUp(WPARAM wParam, LPARAM lParam, const std::string method)
{
	//g_logger.Info("CBaiLuKeyEventSink::LogKeyDownAndUp");
	UINT vCode = UINT(wParam);
	std::string strCodeName = VirtualKeyCodeToString(vCode);
	char buff[1024] = { 0 };
	sprintf(buff, "CBaiLuKeyEventSink Key %s  Name:%s  Code:%d  Code2: %d\n", method.c_str(), strCodeName.c_str(), vCode, (UINT)(lParam));
	std::string strLog(buff);
	//g_logger.Info("%s", strLog.c_str());
}