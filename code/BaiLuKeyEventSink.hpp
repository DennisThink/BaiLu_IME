#ifndef _BAI_LU_KEY_EVENT_SINK_HPP_
#define _BAI_LU_KEY_EVENT_SINK_HPP_
#include "private.hpp"
#include <string>
class CBaiLuKeyEventSink :public ITfKeyEventSink
{
public:
	CBaiLuKeyEventSink();
	virtual ~CBaiLuKeyEventSink();
public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)override;

    virtual ULONG STDMETHODCALLTYPE AddRef(void)override;

    virtual ULONG STDMETHODCALLTYPE Release(void)override;
public:
    virtual HRESULT STDMETHODCALLTYPE OnSetFocus(
        /* [in] */ BOOL fForeground) override;

    virtual HRESULT STDMETHODCALLTYPE OnTestKeyDown(
        /* [in] */ ITfContext* pic,
        /* [in] */ WPARAM wParam,
        /* [in] */ LPARAM lParam,
        /* [out] */ BOOL* pfEaten) override;

    virtual HRESULT STDMETHODCALLTYPE OnTestKeyUp(
        /* [in] */ ITfContext* pic,
        /* [in] */ WPARAM wParam,
        /* [in] */ LPARAM lParam,
        /* [out] */ BOOL* pfEaten) override;

    virtual HRESULT STDMETHODCALLTYPE OnKeyDown(
        /* [in] */ ITfContext* pic,
        /* [in] */ WPARAM wParam,
        /* [in] */ LPARAM lParam,
        /* [out] */ BOOL* pfEaten) override;

    virtual HRESULT STDMETHODCALLTYPE OnKeyUp(
        /* [in] */ ITfContext* pic,
        /* [in] */ WPARAM wParam,
        /* [in] */ LPARAM lParam,
        /* [out] */ BOOL* pfEaten) override;

    virtual HRESULT STDMETHODCALLTYPE OnPreservedKey(
        /* [in] */ ITfContext* pic,
        /* [in] */ REFGUID rguid,
        /* [out] */ BOOL* pfEaten) override;

protected:
    void LogKeyDownAndUp(WPARAM wParam, LPARAM lParam, const std::string method);
    std::string VirtualKeyCodeToString(UINT vkCode);
private:
    int m_refCount;

};
#endif