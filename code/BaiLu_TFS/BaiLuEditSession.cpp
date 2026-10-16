#include "BaiLuEditSession.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
// IUnknown 的三个函数
HRESULT BaiLuEditSession::QueryInterface(
    REFIID riid,
    void** ppvObj)
{
    return S_OK;
}

static std::wstring Utf8ToWide(const std::string& utf8) {
    if (utf8.empty()) return L"";

    int len = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), (int)utf8.size(), nullptr, 0);
    std::wstring wstr(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8.data(), (int)utf8.size(), wstr.data(), len);
    return wstr;
}
ULONG BaiLuEditSession::AddRef()
{
    this->_cRef++;
	//g_logger.Info("BaiLuEditSession::AddRef: _cRef={}", this->_cRef);
    return this->_cRef;
}
ULONG BaiLuEditSession::Release()
{
	this->_cRef--;
	ULONG count = this->_cRef;
    //g_logger.Info("BaiLuEditSession::AddRef: _cRef={}", this->_cRef);
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
        //g_logger.Info("BaiLuEditSession::DoEditSession: _pContext is null");
        return E_FAIL;
	}
    //g_logger.Info("BaiLuEditSession::DoEditSession: {} {}", __FILE__,__LINE__);
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
	//g_logger.Info("BaiLuEditSession::DoEditSession: GetSelection returned hr={}, fetched={}", hr, fetched);
    //g_logger.Info("BaiLuEditSession::DoEditSession: {} {}", __FILE__, __LINE__);
    if (FAILED(hr))
    {
        //g_logger.Info("BaiLuEditSession::DoEditSession: GetSelection failed");
    }

    //g_logger.Info("BaiLuEditSession::DoEditSession: Inserting text: {}", m_strWord.c_str());
	std::wstring wideWord = Utf8ToWide(m_strWord);
    HRESULT hr2 = selection.range->SetText(
        ec,
        TF_ST_CORRECTION,
        wideWord.data(),
        static_cast<LONG>(wideWord.length())
    );
    //g_logger.Info("BaiLuEditSession::DoEditSession: {} {}", __FILE__, __LINE__);
    if (FAILED(hr2))
    {
        //g_logger.Info("BaiLuEditSession::DoEditSession: SetText failed");
    }
    selection.range->Release();
    //g_logger.Info("BaiLuEditSession::DoEditSession: {} {}", __FILE__, __LINE__);
    return S_OK;
}