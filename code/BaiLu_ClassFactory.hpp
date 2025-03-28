#ifndef _BAILU_CLASS_FACTORY_H_
#define _BAILU_CLASS_FACTORY_H_
#include "private.hpp"
class CBaiLuClassFactory :public IClassFactory
{
public:
    // IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, _Outptr_ void** ppvObj) override;
    STDMETHODIMP_(ULONG) AddRef(void) override;
    STDMETHODIMP_(ULONG) Release(void) override;

    // IClassFactory methods
    STDMETHODIMP CreateInstance(_In_opt_ IUnknown* pUnkOuter, _In_ REFIID riid, _COM_Outptr_ void** ppvObj) override;
    STDMETHODIMP LockServer(BOOL fLock) override;
    bool IsEqualGID(REFCLSID lValue);
    static CBaiLuClassFactory* GetSingleInstance();
    static bool DestroySingleInstance();
private:
    // Constructor
    CBaiLuClassFactory(REFCLSID lValue);
private:
public:

private:
    CBaiLuClassFactory& operator=(const CBaiLuClassFactory& rhn) = delete;
    GUID m_rclsid;
    //CRITICAL_SECTION m_cs;
    ATOM m_refCount;
    static CBaiLuClassFactory* m_pInstance;
};
#endif