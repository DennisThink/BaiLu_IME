#include "BaiLuThreadMgrEventSink.hpp"
#include "Logger.h"
#include "BaiLuInputCore.hpp"
static auto& g_logger = BaiLu::Logger::Instance();
HRESULT CBaiLuThreadMgrEventSink::CreateInstance(CBaiLuThreadMgrEventSink** pInst)
{
    CBaiLuThreadMgrEventSink* pOut = new CBaiLuThreadMgrEventSink();
    if (nullptr != pOut && pInst != nullptr)
    {
        *pInst = pOut;
        return S_OK;
    }
    return -1;
}
CBaiLuThreadMgrEventSink::CBaiLuThreadMgrEventSink()
{
    //g_logger.Info("CBaiLuThreadMgrEventSink::CBaiLuThreadMgrEventSink");
    m_refCount = 1;
    m_pPrevTfDocumentMgr = nullptr;
    m_pCurTfDocumentMgr = nullptr;
    m_pCurTfContext = nullptr;
}

CBaiLuThreadMgrEventSink::~CBaiLuThreadMgrEventSink()
{
    //g_logger.Info("CBaiLuThreadMgrEventSink::~CBaiLuThreadMgrEventSink");
}

//IUnKnown
HRESULT STDMETHODCALLTYPE CBaiLuThreadMgrEventSink::QueryInterface(
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    //g_logger.Info("CBaiLuThreadMgrEventSink::QueryInterface");
    if (IsEqualIID(riid, IID_ITfThreadMgrEventSink))
    {
        //g_logger.Debug("{} {}",__FILE__, __LINE__);
        this->AddRef();
        *ppvObject = this;
        return S_OK;
    }
    else
    {
        return S_OK;
    }

}

ULONG STDMETHODCALLTYPE CBaiLuThreadMgrEventSink::AddRef(void)
{
    m_refCount++;
    //g_logger.Info("CBaiLuThreadMgrEventSink::AddRef {}", m_refCount);
    return m_refCount;
}

ULONG STDMETHODCALLTYPE CBaiLuThreadMgrEventSink::Release(void)
{
    m_refCount--;
    //g_logger.Info("CBaiLuThreadMgrEventSink::Release {}", m_refCount);
	ULONG nRet = m_refCount;
    if(nRet == 0)
    {
        delete this;
	}
    return nRet;
}
void CBaiLuThreadMgrEventSink::CheckRefCount() const
{
    //g_logger.Info("CBaiLuThreadMgrEventSink::CheckRefCount {}", m_refCount);
}
// ITfThreadMgrEventSink
STDMETHODIMP CBaiLuThreadMgrEventSink::OnInitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr)
{
    return E_NOTIMPL;
    if (nullptr != pDocMgr)
    {
        //g_logger.Info("CBaiLuInputMethodClass::OnInitDocumentMgr Succeed");
        //this->m_pCurTfDocumentMgr = pDocMgr;
        //this->m_pCurTfDocumentMgr->AddRef();
        return S_OK;
    }
    else
    {
        //g_logger.Info("CBaiLuInputMethodClass::OnInitDocumentMgr Param Error");
        return -1;
    }
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnUninitDocumentMgr(_In_ ITfDocumentMgr* pDocMgr)
{
    return E_NOTIMPL;
    //g_logger.Info("CBaiLuInputMethodClass::OnUninitDocumentMgr");
    /*if (nullptr != this->m_pCurTfDocumentMgr)
    {
        this->m_pCurTfDocumentMgr->Release();
    }*/
    return 0;
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnSetFocus(_In_ ITfDocumentMgr* pDocMgrFocus, _In_ ITfDocumentMgr* pDocMgrPrevFocus)
{
    //g_logger.Info("CBaiLuInputMethodClass::OnSetFocus");
    //this->m_pPrevTfDocumentMgr = pDocMgrPrevFocus;
    //this->m_pCurTfDocumentMgr = pDocMgrFocus;
    if (pDocMgrFocus)
    {
        ITfContext* context = nullptr;

        HRESULT hr = pDocMgrFocus->GetTop(&context);

        if (SUCCEEDED(hr) && context)
        {
            CBaiLuInputCore* pCore = CBaiLuInputCore::GetInstance();
            if (pCore)
            {
                pCore->SetCurTfContext(context);
            }
            else
            {
                //g_logger.Info("CBaiLuInputCore::GetInstance GetInstance failed");
            }
            context->Release();
        }
        else
        {
			//g_logger.Info("CBaiLuInputMethodClass::OnSetFocus GetTop failed");
        }
    }
    else
    {
		//g_logger.Info("CBaiLuInputMethodClass::OnSetFocus pDocMgrFocus is null");
    }

    return S_OK;
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnPushContext(_In_ ITfContext* pContext)
{
    //g_logger.Info("CBaiLuInputMethodClass::OnPushContext");
    //m_pCurTfContext = pContext;
    return E_NOTIMPL;
}

STDMETHODIMP CBaiLuThreadMgrEventSink::OnPopContext(_In_ ITfContext* pContext)
{
    //g_logger.Info("CBaiLuInputMethodClass::OnPopContext");
    //m_pCurTfContext = pContext;
    return E_NOTIMPL;
}