#ifndef _BAI_LU_EDIT_SESSION_HPP_
#define	_BAI_LU_EDIT_SESSION_HPP_
#include "private.hpp"
#include <string>
#include "Log.hpp"
/*
* 我们需要这个类来实现最后的文本写入到输入框
*/
class BaiLuEditSession :public ITfEditSession
{
public:
    BaiLuEditSession(ITfContext* pContext,const std::wstring& strWord)
        : _cRef(1), _pContext(pContext), m_strWord(strWord) {
        if (_pContext) {
			_pContext->AddRef();
        }
    }
    virtual ~BaiLuEditSession() {
        if (_pContext) {
            _pContext->Release();
            _pContext = nullptr;
        }
	}
public:
	STDMETHODIMP DoEditSession(TfEditCookie ec) override;
    // IUnknown 的三个函数
    HRESULT QueryInterface(
        REFIID riid,
        void** ppvObj) override;

    virtual ULONG STDMETHODCALLTYPE AddRef() override;
    virtual ULONG STDMETHODCALLTYPE Release() override;
private:
    LONG _cRef;
    ITfContext* _pContext;
    ITfComposition* _pComposition;
    std::wstring m_strWord;
};
#endif