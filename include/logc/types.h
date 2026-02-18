#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  LOG_LEVEL_VERBOSE,
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL,
} LOG_LogLevel;

typedef uint16_t LOG_Source;
#define LOG_SOURCE_INVALID 0

const char* LOG_LogLevelStr(LOG_LogLevel level);

typedef struct LOG_LogMessage {
  LOG_LogLevel level;
  const char* file;
  int line;
  const char* message;
  LOG_Source source;
} LOG_LogMessage;

struct LOG_LogDriver;

typedef char* (*LOG_LogFormatter)(const LOG_LogMessage* msg);

typedef void (*LOG_LogDriverFunc)(const LOG_LogMessage* msg, const struct LOG_LogDriver* driver);

typedef struct LOG_LogDriver {
  const char* name;
  LOG_LogLevel level;
  LOG_LogFormatter formatter;
  LOG_LogDriverFunc write;
  void* user_data;
  bool enabled;
} LOG_LogDriver;

#ifdef __cplusplus
}
#endif
