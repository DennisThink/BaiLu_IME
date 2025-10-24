#include "Log.hpp"
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <windows.h>
#include <processthreadsapi.h>
namespace LogUtil
{
    static std::ofstream g_logFile;

    void OpenLogFile()
    {
        if (g_logFile.is_open())
        {

        }
        else
        {
            std::cout << "Open Log File" << std::endl;
            //g_logFile.open("./Demo3_log.txt", std::ios_base::out | std::ios_base::app);
        }

    }
    void LogInfo(const char * formatStr, ...)
    {
        va_list arglist;
        char* pBuff = new char[1024];
        {
            memset(pBuff, 0, 1024);
            va_start(arglist, formatStr);
            vsprintf_s(pBuff,1024, formatStr, arglist);
            va_end(arglist);
            SYSTEMTIME time;
            GetLocalTime(&time);
            char buffer[2048] = { 0 };
            DWORD processId = GetCurrentProcessId();
            DWORD threadId = GetCurrentThreadId();
            sprintf_s(buffer,2048, ("PID: %ld TID:%ld [%04d-%02d-%02d %02d:%02d:%02d] %s\r\n"),
                processId,threadId,
                time.wYear, time.wMonth, time.wDay,
                time.wHour, time.wMinute, time.wSecond,
                pBuff);
            OutputDebugString(buffer);
        }

        delete[] pBuff;
    }

    void LogTrace(const char* pFileName, const int line)
    {
        char buff[128] = { 0 };
        memset(buff, 0, 128);
        DWORD processId = GetCurrentProcessId();
        DWORD threadId = GetCurrentThreadId();
        sprintf_s(buff,128, "PID:%ld TID:%ld %s %d\n", processId, threadId, pFileName, line);
        OutputDebugString(buff);
    }

    void LogError(const char* pFileName, const int line)
    {
        char buff[128] = { 0 };
        memset(buff, 0, 128);
        DWORD processId = GetCurrentProcessId();
        DWORD threadId = GetCurrentThreadId();
        sprintf_s(buff, 128, "[ERROR] PID:%ld TID:%ld %s %d\n", processId, threadId, pFileName, line);
        OutputDebugString(buff);
    }

    void CloseLogFile()
    {
        std::cout<<"Close Log File"<<std::endl;
        //g_logFile.close();
    }
}
  