#ifndef LOGC_H
#define LOGC_H

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_MAX_DRIVERS 8

#include "types.h"

typedef struct LOG_Logger {
  LOG_LogDriver* drivers[LOG_MAX_DRIVERS];
  int driverCount;
} LOG_Logger;

extern LOG_Logger LOG_globalLogger;

void LOG_Init();

void LOG_addDriver(LOG_LogDriver* driver);
void LOG_Log(LOG_LogLevel level, const char* file, int line, const char* fmt, ...);

#define LogInfo(fmt, ...) LOG_Log(LOG_LEVEL_INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LogWarn(fmt, ...) LOG_Log(LOG_LEVEL_WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LogDebug(fmt, ...) LOG_Log(LOG_LEVEL_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LogError(fmt, ...) LOG_Log(LOG_LEVEL_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // !LOGC_H
