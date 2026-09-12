#ifndef _BAI_LU_EDIT_SESSION_HPP_
#define	_BAI_LU_EDIT_SESSION_HPP_
#include "private.hpp"
#include <string>
#include "Log.hpp"
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

    ULONG AddRef() override;
    ULONG Release() override;
private:
    LONG _cRef;
    ITfContext* _pContext;
    ITfComposition* _pComposition;
    std::wstring m_strWord;
};
#endif