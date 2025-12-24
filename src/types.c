#include <logc/logc.h>

const char* LOG_LogLevelStr(LOG_LogLevel level) {
  switch (level) {
    case LOG_LEVEL_INFO:
      return "Info";
    case LOG_LEVEL_DEBUG:
      return "Debug";
    case LOG_LEVEL_ERROR:
      return "Error";
    case LOG_LEVEL_WARN:
      return "Warn";
    default:
      return "Info";
  }
}

