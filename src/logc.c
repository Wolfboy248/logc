#include <logc/logc.h>
#include <stdio.h>
#include <stdarg.h>

#include <logc/console.h>
#include <logc/file.h>
#include <stdlib.h>
#include <string.h>

LOG_Logger LOG_globalLogger = {0};
LOG_Source LOG_defaultSource = {0};

static const char* g_sources[256];
static uint16_t g_source_count = 1;

void LOG_Init() {
  LOG_defaultSource = LOG_registerSource("Default");

  LOG_addDriver(&LOG_consoleDriver);

  LOG_fileDriver.user_data = "debug.log";
  LOG_addDriver(&LOG_fileDriver);
}

void LOG_addDriver(LOG_LogDriver* driver) {
  if (LOG_globalLogger.driverCount < LOG_MAX_DRIVERS) {
    LOG_globalLogger.drivers[LOG_globalLogger.driverCount++] = driver;
  }
}

LOG_Source LOG_registerSource(const char *name) {
  if (g_source_count >= 256) return LOG_SOURCE_INVALID;
  g_sources[g_source_count] = name;
  return g_source_count++;
}

const char* LOG_getSourceName(LOG_Source source) {
  if (source >= 256) return LOG_SOURCE_INVALID;
  return g_sources[source];
}

LOG_Source LOG_getSourceByName(const char* name) {
  if (!name) return LOG_SOURCE_INVALID;

  for (LOG_Source i = 1; i < g_source_count; i++) {
    if (strcmp(g_sources[i], name) == 0) {
      return i;
    }
  }

  return LOG_SOURCE_INVALID;
}

void LOG_Log(LOG_Source source, LOG_LogLevel level, const char* file, int line, const char* fmt, ...) {
  char buffer[1024];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  LOG_LogMessage msg = { level, file, line, buffer, source };

  for (int i = 0; i < LOG_globalLogger.driverCount; i++) {
    LOG_LogDriver* driver = LOG_globalLogger.drivers[i];
    if (driver->enabled && level >= driver->level) {
      driver->write(&msg, driver);
    }
  }

  if (level == LOG_LEVEL_FATAL) {
    abort();
  }
}

