#include "BaiLuTextEditSink.hpp"
#include "Log.hpp"
CBaiLuTextEditSink::CBaiLuTextEditSink()
{
    m_refCount = 0;
}

CBaiLuTextEditSink::~CBaiLuTextEditSink()
{

}

HRESULT STDMETHODCALLTYPE CBaiLuTextEditSink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuTextEditSink::AddRef(void)
{
    m_refCount++;
    LogUtil::LogInfo("CBaiLuTextEditSink::AddRef %d", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuTextEditSink::Release(void)
{
    m_refCount--;
    LogUtil::LogInfo("CBaiLuTextEditSink::Release %d", m_refCount);
    return m_refCount;
}

HRESULT STDMETHODCALLTYPE CBaiLuTextEditSink::OnEndEdit(
    /* [in] */ __RPC__in_opt ITfContext* pic,
    /* [in] */ TfEditCookie ecReadOnly,
    /* [in] */ __RPC__in_opt ITfEditRecord* pEditRecord)
{
    return 0;
}