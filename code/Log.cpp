#include "Log.hpp"
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <windows.h>
namespace LogUtil
{
    static std::ofstream g_logFile;

    void OpenLogFile()
    {
        std::cout<<"Open Log File"<<std::endl;
        g_logFile.open("./Demo3_log.txt",std::ios_base::out|std::ios_base::app);
    }
    void LogInfo(const char * formatStr, ...)
    {
        va_list arglist;
        char* pBuff = new char[1024];
        {
            memset(pBuff, 0, 1024);
            va_start(arglist, formatStr);
            vsprintf(pBuff, formatStr, arglist);
            va_end(arglist);
            SYSTEMTIME time;
            GetLocalTime(&time);
            char buffer[2048] = { 0 };
            sprintf(buffer, ("[%04d-%02d-%02d %02d:%02d:%02d] %s\r\n"),
                time.wYear, time.wMonth, time.wDay,
                time.wHour, time.wMinute, time.wSecond,
                pBuff);
            g_logFile.write(buffer, strlen(buffer));
        }

        delete[] pBuff;
    }

    void LogTrace(const char* pFileName, const int line)
    {
        char buff[128] = { 0 };
        memset(buff, 0, 128);
        sprintf(buff, "%s %d\n", pFileName, line);
        g_logFile.write(buff, std::strlen(buff));
    }
    void CloseLogFile()
    {
        std::cout<<"Close Log File"<<std::endl;
        g_logFile.close();
    }
}
  