#ifndef _BAI_LU_EDIT_SESSION_HPP_
#define	_BAI_LU_EDIT_SESSION_HPP_
#include "private.hpp"
#include <string>
#include "Log.hpp"
class BaiLuEditSession :public ITfEditSession
{
public:
    BaiLuEditSession(ITfContext* pContext,const std::string& strWord)
        : _cRef(1), _pContext(pContext), m_strWord(strWord) {
    }

public:
    STDMETHODIMP DoEditSession(TfEditCookie ec)
    {
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
        if (hr != S_OK)
        {
			LogUtil::LogInfo("BaiLuEditSession::DoEditSession: GetSelection failed");
        }

		LogUtil::LogInfo("BaiLuEditSession::DoEditSession: Inserting text: %s", m_strWord.c_str());
        std::wstring wtext(m_strWord.begin(), m_strWord.end());
		LogUtil::LogInfo("BaiLuEditSession::DoEditSession: Converted text to wide string: %ls", wtext.c_str());

        HRESULT hr2 = selection.range->SetText(
            ec,
            TF_ST_CORRECTION,
            wtext.c_str(),
            static_cast<LONG>(wtext.length())
        );
        if (hr2 != S_OK)
        {
			LogUtil::LogInfo("BaiLuEditSession::DoEditSession: SetText failed");
        }
        selection.range->Release();
        return S_OK;
    }
    // IUnknown 的三个函数
    HRESULT QueryInterface(
        REFIID riid,
        void** ppvObj) override;

    ULONG AddRef() override;
    ULONG Release() override;
private:
    LONG _cRef;
    ITfContext* _pContext;
    ITfComposition* _pComposition;
    std::string m_strWord;
};
#endif