#include "BaiLuKeyEventSink.hpp"
#include "Log.hpp"
CBaiLuKeyEventSink::CBaiLuKeyEventSink()
{
	m_refCount = 0;
}

CBaiLuKeyEventSink::~CBaiLuKeyEventSink()
{

}
HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnSetFocus(
	/* [in] */ BOOL fForeground) 
{
	return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnTestKeyDown(
	/* [in] */ ITfContext* pic,
	/* [in] */ WPARAM wParam,
	/* [in] */ LPARAM lParam,
	/* [out] */ BOOL* pfEaten)
{
	LogKeyDownAndUp(wParam, lParam, "OnTestKeyDown");
	return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnTestKeyUp(
	/* [in] */ ITfContext* pic,
	/* [in] */ WPARAM wParam,
	/* [in] */ LPARAM lParam,
	/* [out] */ BOOL* pfEaten)
{
	LogKeyDownAndUp(wParam, lParam, "OnTestKeyUp");
	return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnKeyDown(
	/* [in] */ ITfContext* pic,
	/* [in] */ WPARAM wParam,
	/* [in] */ LPARAM lParam,
	/* [out] */ BOOL* pfEaten)
{
	LogKeyDownAndUp(wParam, lParam, "OnKeyDown");
	return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnKeyUp(
	/* [in] */ ITfContext* pic,
	/* [in] */ WPARAM wParam,
	/* [in] */ LPARAM lParam,
	/* [out] */ BOOL* pfEaten)
{
	LogKeyDownAndUp(wParam, lParam, "OnKeyUp");
	return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::OnPreservedKey(
	/* [in] */ ITfContext* pic,
	/* [in] */ REFGUID rguid,
	/* [out] */ BOOL* pfEaten)
{
	return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuKeyEventSink::QueryInterface(
	/* [in] */ REFIID riid,
	/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
	LogUtil::LogInfo("%s", "QueryInterface");
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
	return m_refCount;
}
std::string CBaiLuKeyEventSink::VirtualKeyCodeToString(UINT vkCode) {
	// ���ڴ洢�����Ļ�����
	char keyName[256] = { 0 };

	// ���������ת��Ϊɨ����
	UINT scanCode = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);

	// ����lParam����GetKeyNameText����
	// ��16λ��ɨ���룬��16λ�еĵ�25λ��bit24������ָʾ��չ��
	LONG lParam = (scanCode << 16);

	// ��ȡ����
	if (GetKeyNameTextA(lParam, keyName, sizeof(keyName)) > 0) {
		return std::string(keyName);
	}

	return "Unknown Key";
}
void CBaiLuKeyEventSink::LogKeyDownAndUp(WPARAM wParam, LPARAM lParam, const std::string method)
{
	UINT vCode = UINT(wParam);
	std::string strCodeName = VirtualKeyCodeToString(vCode);
	char buff[1024] = { 0 };
	sprintf(buff, "CBaiLuKeyEventSink Key %s  Name:%s  Code:%d  Code2: %d\n", method.c_str(), strCodeName.c_str(), vCode, (UINT)(lParam));
	std::string strLog(buff);
	LogUtil::LogInfo("%s", strLog.c_str());
}