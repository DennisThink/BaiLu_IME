#ifndef _BAI_LU_LANGUAGE_BAR_ITEM_BUTTON_HPP_
#define _BAI_LU_LANGUAGE_BAR_ITEM_BUTTON_HPP_
#include "private.hpp"

class CCompartment;
class CCompartmentEventSink;
/*
*TODO:不知道这个类做什么用的，先实现了再说
*/
class BaiLuLanguageBarItemButton : public ITfLangBarItemButton,
    public ITfSource
{
public:
    BaiLuLanguageBarItemButton(REFGUID guidLangBar, LPCWSTR description, LPCWSTR tooltip, DWORD onIconIndex, DWORD offIconIndex, BOOL isSecureMode);
    ~BaiLuLanguageBarItemButton();

    // IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, _Outptr_ void** ppvObj) override;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
    virtual ULONG STDMETHODCALLTYPE Release(void) override;

    // ITfLangBarItem
    STDMETHODIMP GetInfo(_Out_ TF_LANGBARITEMINFO* pInfo) override;
    STDMETHODIMP GetStatus(_Out_ DWORD* pdwStatus) override;
    STDMETHODIMP Show(BOOL fShow) override;
    STDMETHODIMP GetTooltipString(_Out_ BSTR* pbstrToolTip) override;

    // ITfLangBarItemButton
    STDMETHODIMP OnClick(TfLBIClick click, POINT pt, _In_ const RECT* prcArea) override;
    STDMETHODIMP InitMenu(_In_ ITfMenu* pMenu) override;
    STDMETHODIMP OnMenuSelect(UINT wID) override;
    STDMETHODIMP GetIcon(_Out_ HICON* phIcon) override;
    STDMETHODIMP GetText(_Out_ BSTR* pbstrText) override;

    // ITfSource
    STDMETHODIMP AdviseSink(__RPC__in REFIID riid, __RPC__in_opt IUnknown* punk, __RPC__out DWORD* pdwCookie) override;
    STDMETHODIMP UnadviseSink(DWORD dwCookie) override;

    // Add/Remove languagebar item
    HRESULT _AddItem(_In_ ITfThreadMgr* pThreadMgr);
    HRESULT _RemoveItem(_In_ ITfThreadMgr* pThreadMgr);

    // Register compartment for button On/Off switch
    BOOL _RegisterCompartment(_In_ ITfThreadMgr* pThreadMgr, TfClientId tfClientId, REFGUID guidCompartment);
    BOOL _UnregisterCompartment(_In_ ITfThreadMgr* pThreadMgr);

    void CleanUp();

    void SetStatus(DWORD dwStatus, BOOL fSet);

private:
    ITfLangBarItemSink* _pLangBarItemSink;

    TF_LANGBARITEMINFO _tfLangBarItemInfo;
    LPCWSTR _pTooltipText;
    DWORD _onIconIndex;
    DWORD _offIconIndex;

    BOOL _isAddedToLanguageBar;
    BOOL _isSecureMode;
    DWORD _status;

    CCompartment* _pCompartment;
    CCompartmentEventSink* _pCompartmentEventSink;
    static HRESULT _CompartmentCallback(_In_ void* pv, REFGUID guidCompartment);

    // The cookie for the sink to CLangBarItemButton.
    static const DWORD _cookie = 0;

    LONG _refCount;
};
#endif