#include "BaiLuThreadFocusSink.hpp"
#include "Log.hpp"
CBaiLuThreadFocusSink::CBaiLuThreadFocusSink()
{
    m_refCount = 0;
}

CBaiLuThreadFocusSink::~CBaiLuThreadFocusSink()
{

}

HRESULT STDMETHODCALLTYPE CBaiLuThreadFocusSink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    return 0;
}

ULONG STDMETHODCALLTYPE CBaiLuThreadFocusSink::AddRef(void)
{
    
    m_refCount++;
    LogUtil::LogInfo("CBaiLuThreadFocusSink::AddRef %d", m_refCount);
    return m_refCount;

}

ULONG STDMETHODCALLTYPE CBaiLuThreadFocusSink::Release(void)
{
    
    m_refCount--;
    LogUtil::LogInfo("CBaiLuThreadFocusSink::Release %d", m_refCount);
    return m_refCount;

}

HRESULT STDMETHODCALLTYPE CBaiLuThreadFocusSink::OnSetThreadFocus(void)
{
    return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuThreadFocusSink::OnKillThreadFocus(void)
{
    return 0;
}