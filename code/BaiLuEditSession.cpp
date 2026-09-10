#include "BaiLuEditSession.hpp"

// IUnknown 的三个函数
HRESULT BaiLuEditSession::QueryInterface(
    REFIID riid,
    void** ppvObj)
{
    return S_OK;
}

ULONG BaiLuEditSession::AddRef()
{
    return 1;
}
ULONG BaiLuEditSession::Release()
{
    return 1;
}