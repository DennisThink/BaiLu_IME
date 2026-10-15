#include "BaiLu_DeleteBeforeEditSession.hpp"
#include "Logger.h"
static auto& g_logger = BaiLu::Logger::Instance();
static void LogRangeText(ITfRange* pRange, TfEditCookie ec)
{
	{
		if (pRange)
		{
			WCHAR buffer[256] = {};
			ULONG actualLength = 0;

			HRESULT hText = pRange->GetText(
				ec,
				0,
				buffer,
				256,
				&actualLength
			);
			//g_logger.Info("BaiLuEditSession::DoEditSession:{}  {}", buffer, actualLength);
		}
	}
}
STDMETHODIMP CBaiLuDeleteEditSession::DoEditSession(TfEditCookie ec) 
{
	//g_logger.Info("BaiLuEditSession::DoEditSession: {} {}", __FILE__, __LINE__);
	if (_pContext)
	{
		TF_SELECTION selection{};
		ULONG fetched = 0;
		HRESULT hr = _pContext->GetSelection(
			ec,
			TF_DEFAULT_SELECTION,
			1,
			&selection,
			&fetched
		);
		//g_logger.Info("BaiLuEditSession::DoEditSession: {} {}", __FILE__, __LINE__);
		if (FAILED(hr) || fetched != 1)
		{
			return S_OK;
		}
		ITfRange* pRange = selection.range;
		
		//g_logger.Info("BaiLuEditSession::DoEditSession: {} {}", __FILE__, __LINE__);
	

		if (pRange)
		{
			LogRangeText(pRange, ec);
			LONG needShift = -2;
			LONG actualShift = 0;
			HRESULT hShift = pRange->ShiftStart(ec,
				needShift,
				&actualShift,
				NULL);
			//g_logger.Info("BaiLuEditSession::DoEditSession: NeedShift  %ld RealShift %ld", needShift, actualShift);
			LogRangeText(pRange, ec);
			HRESULT hShift2 = pRange->ShiftEnd(ec,
				2,
				&actualShift,
				NULL);
			//g_logger.Info("BaiLuEditSession::DoEditSession: NeedShift  %ld RealShift %ld", needShift, actualShift);
			LogRangeText(pRange, ec);
			if (FAILED(hShift) || actualShift != needShift)
			{
				//g_logger.Info("BaiLuEditSession::DoEditSession: {} {}", __FILE__, __LINE__);
			}
			else
			{
				HRESULT hSetText = pRange->SetText(ec, 
					TF_ST_CORRECTION,
					L"", 
					0);
				if (FAILED(hSetText))
				{
					//g_logger.Info("BaiLuEditSession::DoEditSession: {} {}", __FILE__, __LINE__);
				}
			}

		}
		//g_logger.Info("BaiLuEditSession::DoEditSession: {} {}", __FILE__, __LINE__);
		pRange->Release();
	}
	//g_logger.Info("BaiLuEditSession::DoEditSession: {} {}", __FILE__, __LINE__);
	return S_OK;
}
// IUnknown 的三个函数
HRESULT  CBaiLuDeleteEditSession::QueryInterface(
    REFIID riid,
    void** ppvObj)  {
    return S_OK;
}

ULONG  CBaiLuDeleteEditSession::AddRef() {
    _cRef++;
    return _cRef;
}

ULONG  CBaiLuDeleteEditSession::Release() {
    _cRef--;
    ULONG nRet = _cRef;
    if (nRet == 0) 
    {
        delete this;
    }
    return nRet;
}