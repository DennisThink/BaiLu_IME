#ifndef _WIN_INPUT_DEMO_LOG_H_
#define _WIN_INPUT_DEMO_LOG_H_
#include <string>
namespace LogUtil
{
    void OpenLogFile();
    void LogInfo(const char * formatStr, ...);
    void LogTrace(const char* pFileName, const int line);
    void LogError(const char* pFileName, const int line);
    void CloseLogFile();
};
#endif