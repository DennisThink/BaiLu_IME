#include "BaiLuEditSession.hpp"
#include "Log.hpp"
// IUnknown 的三个函数
HRESULT BaiLuEditSession::QueryInterface(
    REFIID riid,
    void** ppvObj)
{
    return S_OK;
}

ULONG BaiLuEditSession::AddRef()
{
    this->_cRef++;
	LogUtil::LogInfo("BaiLuEditSession::AddRef: _cRef=%d", this->_cRef);
    return this->_cRef;
}
ULONG BaiLuEditSession::Release()
{
	this->_cRef--;
	int count = this->_cRef;
    LogUtil::LogInfo("BaiLuEditSession::AddRef: _cRef=%d", this->_cRef);
    if(count ==0)
    {
        delete this;
	}
    return count;
}

STDMETHODIMP BaiLuEditSession::DoEditSession(TfEditCookie ec)
{
    if(_pContext == nullptr)
    {
        LogUtil::LogInfo("BaiLuEditSession::DoEditSession: _pContext is null");
        return E_FAIL;
	}
    LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %s  %d", __FILE__,__LINE__);
    // 核心操作：结束组合，提交文本
    // ec 是 TSF 传递的编辑 Cookie，用于在当前会话中标识编辑上下文
    TF_SELECTION selection{};
    ULONG fetched = 0;

    HRESULT hr = _pContext->GetSelection(
        ec,
        0,
        1,
        &selection,
        &fetched
    );
	LogUtil::LogInfo("BaiLuEditSession::DoEditSession: GetSelection returned hr=0x%08X, fetched=%lu", hr, fetched);
    LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %s  %d", __FILE__, __LINE__);
    if (FAILED(hr))
    {
        LogUtil::LogInfo("BaiLuEditSession::DoEditSession: GetSelection failed");
    }

    LogUtil::LogInfo("BaiLuEditSession::DoEditSession: Inserting text: %ls", m_strWord.c_str());
    HRESULT hr2 = selection.range->SetText(
        ec,
        TF_ST_CORRECTION,
        m_strWord.data(),
        static_cast<LONG>(m_strWord.length())
    );
    LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %s  %d", __FILE__, __LINE__);
    if (FAILED(hr2))
    {
        LogUtil::LogInfo("BaiLuEditSession::DoEditSession: SetText failed");
    }
    selection.range->Release();
    LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %s  %d", __FILE__, __LINE__);
    return S_OK;
}