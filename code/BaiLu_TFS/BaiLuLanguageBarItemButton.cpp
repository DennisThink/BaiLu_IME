#include "BaiLuLanguageBarItemButton.hpp"
#include "Log.hpp"
#include <string>
BaiLuLanguageBarItemButton::BaiLuLanguageBarItemButton(REFGUID guidLangBar, LPCWSTR description, LPCWSTR tooltip, DWORD onIconIndex, DWORD offIconIndex, BOOL isSecureMode)
{
	this->_refCount = 1;
	//
	this->m_tfLangBarItemInfo.clsidService = guidLangBar;
	this->m_tfLangBarItemInfo.dwStyle = TF_LBI_STYLE_BTN_TOGGLE;
	this->m_tfLangBarItemInfo.guidItem = GUID_LBI_INPUTMODE;
	std::string strDescription = "BaiLuIME";
	memcpy(this->m_tfLangBarItemInfo.szDescription, strDescription.data(), strDescription.length());
	this->m_tfLangBarItemInfo.ulSort = 0;

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
	pInfo = &(this->m_tfLangBarItemInfo);
	return 0;
}

STDMETHODIMP BaiLuLanguageBarItemButton::GetStatus(_Out_ DWORD* pdwStatus)
{
	*pdwStatus = 0; // ³õÊ¼ÇåÁã
	*pdwStatus |= TF_LBI_STATUS_BTN_TOGGLED;
	return S_OK;
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
	LogUtil::LogInfo(TEXT("CLangBarItemButton::AdviseSink"));
	// We allow only ITfLangBarItemSink interface.
	if (!IsEqualIID(IID_ITfLangBarItemSink, riid))
	{
		return CONNECT_E_CANNOTCONNECT;
	}

	// We support only one sink once.
	if (m_pLangBarItemSink != nullptr)
	{
		return CONNECT_E_ADVISELIMIT;
	}

	// Query the ITfLangBarItemSink interface and store it into _pLangBarItemSink.
	if (punk == nullptr)
	{
		return E_INVALIDARG;
	}
	if (punk->QueryInterface(IID_ITfLangBarItemSink, (void**)&m_pLangBarItemSink) != S_OK)
	{
		m_pLangBarItemSink = nullptr;
		return E_NOINTERFACE;
	}

	// return our cookie.
	*pdwCookie = _cookie;
	return S_OK;
}

STDMETHODIMP BaiLuLanguageBarItemButton::UnadviseSink(DWORD dwCookie)
{
	LogUtil::LogInfo(TEXT("BaiLuLanguageBarItemButton::UnadviseSink"));
	// Check the given cookie.
	if (dwCookie != _cookie)
	{
		return CONNECT_E_NOCONNECTION;
	}

	// If there is nno connected sink, we just fail.
	if (m_pLangBarItemSink == nullptr)
	{
		return CONNECT_E_NOCONNECTION;
	}

	m_pLangBarItemSink->Release();
	m_pLangBarItemSink = nullptr;

	return S_OK;
	return 0;
}

// Add/Remove languagebar item
HRESULT BaiLuLanguageBarItemButton::_AddItem(_In_ ITfThreadMgr* pThreadMgr)
{
	LogUtil::LogInfo(TEXT("BaiLuLanguageBarItemButton::_AddItem"));
	HRESULT hr = S_OK;
	ITfLangBarItemMgr* pLangBarItemMgr = nullptr;

	if (_isAddedToLanguageBar)
	{
		return S_OK;
	}

	hr = pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void**)&pLangBarItemMgr);
	if (SUCCEEDED(hr))
	{
		hr = pLangBarItemMgr->AddItem(this);
		if (SUCCEEDED(hr))
		{
			_isAddedToLanguageBar = TRUE;
		}
		pLangBarItemMgr->Release();
	}

	return hr;
}

HRESULT BaiLuLanguageBarItemButton::_RemoveItem(_In_ ITfThreadMgr* pThreadMgr)
{
	LogUtil::LogInfo(TEXT("CLangBarItemButton::_RemoveItem"));
	HRESULT hr = S_OK;
	ITfLangBarItemMgr* pLangBarItemMgr = nullptr;

	if (!_isAddedToLanguageBar)
	{
		return S_OK;
	}

	hr = pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void**)&pLangBarItemMgr);
	if (SUCCEEDED(hr))
	{
		hr = pLangBarItemMgr->RemoveItem(this);
		if (SUCCEEDED(hr))
		{
			_isAddedToLanguageBar = FALSE;
		}
		pLangBarItemMgr->Release();
	}

	return hr;
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