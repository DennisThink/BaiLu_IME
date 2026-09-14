#include "BaiLuKeyEventSink.hpp"
#include "Log.hpp"
#include "CommonFunction.hpp"
#include "BaiLuInputCore.hpp"
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
	LogUtil::LogInfo("CBaiLuKeyEventSink::CBaiLuKeyEventSink %d", m_refCount);
}

CBaiLuKeyEventSink::~CBaiLuKeyEventSink()
{
	LogUtil::LogInfo("CBaiLuKeyEventSink::~CBaiLuKeyEventSink %d", m_refCount);
}
HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnSetFocus(
	/* [in] */ BOOL fForeground) 
{
	LogUtil::LogInfo("CBaiLuKeyEventSink::~CBaiLuKeyEventSink %d", m_refCount);
	return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnTestKeyDown(
	/* [in] */ ITfContext* pic,
	/* [in] */ WPARAM wParam,
	/* [in] */ LPARAM lParam,
	/* [out] */ BOOL* pfEaten)
{
	LogUtil::LogInfo("CBaiLuKeyEventSink::OnTestKeyDown %d", m_refCount);
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
	LogUtil::LogInfo("CBaiLuKeyEventSink::OnTestKeyUp %d", m_refCount);
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
	LogUtil::LogInfo("CBaiLuKeyEventSink::OnKeyDown %d", m_refCount);
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
	LogUtil::LogInfo("CBaiLuKeyEventSink::OnKeyUp %d", m_refCount);
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
	LogUtil::LogInfo("CBaiLuKeyEventSink::OnPreservedKey %d", m_refCount);
	return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::QueryInterface(
	/* [in] */ REFIID riid,
	/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
	LogUtil::LogInfo("CBaiLuKeyEventSink::QueryInterface %d", m_refCount);
	return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuKeyEventSink::AddRef(void) 
{
	m_refCount++;
	LogUtil::LogInfo("CBaiLuKeyEventSink::AddRef %d", m_refCount);
	return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuKeyEventSink::Release(void) 
{
	m_refCount--;
	LogUtil::LogInfo("CBaiLuKeyEventSink::Release %d", m_refCount);
	ULONG nRet = m_refCount;
	if(nRet == 0)
	{
		delete this;
	}
	return nRet;
}

void CBaiLuKeyEventSink::CheckRefCount() const
{
	LogUtil::LogInfo("CBaiLuKeyEventSink::CheckRefCount %d", m_refCount);
}

void CBaiLuKeyEventSink::LogKeyDownAndUp(WPARAM wParam, LPARAM lParam, const std::string method)
{
	LogUtil::LogInfo("CBaiLuKeyEventSink::LogKeyDownAndUp");
	UINT vCode = UINT(wParam);
	std::string strCodeName = VirtualKeyCodeToString(vCode);
	char buff[1024] = { 0 };
	sprintf(buff, "CBaiLuKeyEventSink Key %s  Name:%s  Code:%d  Code2: %d\n", method.c_str(), strCodeName.c_str(), vCode, (UINT)(lParam));
	std::string strLog(buff);
	LogUtil::LogInfo("%s", strLog.c_str());
}