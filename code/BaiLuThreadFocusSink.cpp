#include "BaiLuThreadFocusSink.hpp"
#include "Log.hpp"
CBaiLuThreadFocusSink::CBaiLuThreadFocusSink()
{
    LogUtil::LogInfo("CBaiLuThreadFocusSink::CBaiLuThreadFocusSink");
    m_refCount = 0;
}

CBaiLuThreadFocusSink::~CBaiLuThreadFocusSink()
{
    LogUtil::LogInfo("CBaiLuThreadFocusSink::~CBaiLuThreadFocusSink");
}

HRESULT STDMETHODCALLTYPE CBaiLuThreadFocusSink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    LogUtil::LogInfo("CBaiLuThreadFocusSink::QueryInterface");
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
    LogUtil::LogInfo("CBaiLuThreadFocusSink::OnSetThreadFocus");
    return 0;
}

HRESULT STDMETHODCALLTYPE CBaiLuThreadFocusSink::OnKillThreadFocus(void)
{
    LogUtil::LogInfo("CBaiLuThreadFocusSink::OnKillThreadFocus");
    return 0;
}