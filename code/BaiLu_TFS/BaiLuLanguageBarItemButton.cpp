#include "BaiLuLanguageBarItemButton.hpp"

BaiLuLanguageBarItemButton::BaiLuLanguageBarItemButton(REFGUID guidLangBar, LPCWSTR description, LPCWSTR tooltip, DWORD onIconIndex, DWORD offIconIndex, BOOL isSecureMode)
{
	this->_refCount = 1;
}

BaiLuLanguageBarItemButton::~BaiLuLanguageBarItemButton()
{

}

// IUnknown
STDMETHODIMP BaiLuLanguageBarItemButton::QueryInterface(REFIID riid, _Outptr_ void** ppvObj) 
{
	return 0;
}
STDMETHODIMP_(ULONG) BaiLuLanguageBarItemButton::AddRef(void) 
{
	_refCount++;
	return _refCount;
}
STDMETHODIMP_(ULONG) BaiLuLanguageBarItemButton::Release(void)
{
	_refCount--;
	ULONG nRet = _refCount;
	if(nRet == 0)
	{
		delete this;
	}
	return nRet;
}

// ITfLangBarItem
STDMETHODIMP BaiLuLanguageBarItemButton::GetInfo(_Out_ TF_LANGBARITEMINFO* pInfo)
{
	return 0;
}

STDMETHODIMP BaiLuLanguageBarItemButton::GetStatus(_Out_ DWORD* pdwStatus)
{
	return 0;
}

STDMETHODIMP BaiLuLanguageBarItemButton::Show(BOOL fShow)
{
	return 0;
}

STDMETHODIMP BaiLuLanguageBarItemButton::GetTooltipString(_Out_ BSTR* pbstrToolTip)
{
	return 0;
}

// ITfLangBarItemButton
STDMETHODIMP BaiLuLanguageBarItemButton::OnClick(TfLBIClick click, POINT pt, _In_ const RECT* prcArea)
{
	return 0;
}

STDMETHODIMP BaiLuLanguageBarItemButton::InitMenu(_In_ ITfMenu* pMenu)
{
	return 0;
}

STDMETHODIMP BaiLuLanguageBarItemButton::OnMenuSelect(UINT wID)
{
	return 0;
}

STDMETHODIMP BaiLuLanguageBarItemButton::GetIcon(_Out_ HICON* phIcon)
{
	return 0;
}

STDMETHODIMP BaiLuLanguageBarItemButton::GetText(_Out_ BSTR* pbstrText)
{
	return 0;
}

// ITfSource
STDMETHODIMP BaiLuLanguageBarItemButton::AdviseSink(__RPC__in REFIID riid, __RPC__in_opt IUnknown* punk, __RPC__out DWORD* pdwCookie)
{
	return 0;
}

STDMETHODIMP BaiLuLanguageBarItemButton::UnadviseSink(DWORD dwCookie)
{
	return 0;
}

// Add/Remove languagebar item
HRESULT BaiLuLanguageBarItemButton::_AddItem(_In_ ITfThreadMgr* pThreadMgr)
{
	return 0;
}

HRESULT BaiLuLanguageBarItemButton::_RemoveItem(_In_ ITfThreadMgr* pThreadMgr)
{
	return 0;
}

// Register compartment for button On/Off switch
BOOL BaiLuLanguageBarItemButton::_RegisterCompartment(_In_ ITfThreadMgr* pThreadMgr, TfClientId tfClientId, REFGUID guidCompartment)
{
	return FALSE;
}

BOOL BaiLuLanguageBarItemButton::_UnregisterCompartment(_In_ ITfThreadMgr* pThreadMgr)
{
	return FALSE;
}

void BaiLuLanguageBarItemButton::CleanUp()
{

}

void BaiLuLanguageBarItemButton::SetStatus(DWORD dwStatus, BOOL fSet)
{

}