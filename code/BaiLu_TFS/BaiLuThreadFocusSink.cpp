#include "BaiLuThreadFocusSink.hpp"
#include "Log.hpp"

CBaiLuThreadFocusSink* CBaiLuThreadFocusSink::m_pStaticInst = nullptr;

HRESULT CBaiLuThreadFocusSink::CreateInstance(CBaiLuThreadFocusSink** ppOut)
{
    if (nullptr == m_pStaticInst)
    {
        m_pStaticInst = new CBaiLuThreadFocusSink();
    }

    if (nullptr != m_pStaticInst && nullptr != ppOut)
    {
        *ppOut = m_pStaticInst;
        return S_OK;
    }
    return -1;
}
CBaiLuThreadFocusSink::CBaiLuThreadFocusSink()
{
    LogUtil::LogInfo("CBaiLuThreadFocusSink::CBaiLuThreadFocusSink");
    m_refCount = 1;
    LogUtil::LogInfo("CBaiLuThreadFocusSink::CBaiLuThreadFocusSink %d", m_refCount);
}

CBaiLuThreadFocusSink::~CBaiLuThreadFocusSink()
{
    LogUtil::LogInfo("CBaiLuThreadFocusSink::~CBaiLuThreadFocusSink %d", m_refCount);
    LogUtil::LogInfo("CBaiLuThreadFocusSink::~CBaiLuThreadFocusSink");
}

HRESULT STDMETHODCALLTYPE CBaiLuThreadFocusSink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    LogUtil::LogInfo("CBaiLuThreadFocusSink::QueryInterface");
    return E_NOINTERFACE;
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
	ULONG nRet = m_refCount;
    if (m_refCount == 0)
    {
        delete this;
    }
    return nRet;

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