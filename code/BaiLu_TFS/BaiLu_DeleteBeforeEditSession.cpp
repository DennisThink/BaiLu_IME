#include "BaiLu_DeleteBeforeEditSession.hpp"
#include "Log.hpp"

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
			LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %ls %ld", buffer, actualLength);
		}
	}
}
STDMETHODIMP CBaiLuDeleteEditSession::DoEditSession(TfEditCookie ec) 
{
	LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %s  %d", __FILE__, __LINE__);
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
		LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %s  %d", __FILE__, __LINE__);
		if (FAILED(hr) || fetched != 1)
		{
			return S_OK;
		}
		ITfRange* pRange = selection.range;
		
		LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %s  %d", __FILE__, __LINE__);
	

		if (pRange)
		{
			LogRangeText(pRange, ec);
			LONG needShift = -2;
			LONG actualShift = 0;
			HRESULT hShift = pRange->ShiftStart(ec,
				needShift,
				&actualShift,
				NULL);
			LogUtil::LogInfo("BaiLuEditSession::DoEditSession: NeedShift  %ld RealShift %ld", needShift, actualShift);
			LogRangeText(pRange, ec);
			HRESULT hShift2 = pRange->ShiftEnd(ec,
				2,
				&actualShift,
				NULL);
			LogUtil::LogInfo("BaiLuEditSession::DoEditSession: NeedShift  %ld RealShift %ld", needShift, actualShift);
			LogRangeText(pRange, ec);
			if (FAILED(hShift) || actualShift != needShift)
			{
				LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %s  %d", __FILE__, __LINE__);
			}
			else
			{
				HRESULT hSetText = pRange->SetText(ec, 
					TF_ST_CORRECTION,
					L"", 
					0);
				if (FAILED(hSetText))
				{
					LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %s  %d", __FILE__, __LINE__);
				}
			}

		}
		LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %s  %d", __FILE__, __LINE__);
		pRange->Release();
	}
	LogUtil::LogInfo("BaiLuEditSession::DoEditSession: %s  %d", __FILE__, __LINE__);
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