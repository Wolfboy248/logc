#include <logc/logc.h>
#include <stdio.h>
#include <stdarg.h>

#include <logc/console.h>
#include <logc/file.h>

LOG_Logger LOG_globalLogger= {0};

void LOG_Init() {
  LOG_addDriver(&LOG_consoleDriver);

  LOG_fileDriver.user_data = "debug.log";
  LOG_addDriver(&LOG_fileDriver);
}

void LOG_addDriver(LOG_LogDriver* driver) {
  if (LOG_globalLogger.driverCount < LOG_MAX_DRIVERS) {
    LOG_globalLogger.drivers[LOG_globalLogger.driverCount++] = driver;
  }
}

void LOG_Log(LOG_LogLevel level, const char* file, int line, const char* fmt, ...) {
  char buffer[1024];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  LOG_LogMessage msg = { level, file, line, buffer };

  for (int i = 0; i < LOG_globalLogger.driverCount; i++) {
    LOG_LogDriver* driver = LOG_globalLogger.drivers[i];
    if (driver->enabled && level <= driver->level) {
      driver->write(&msg, driver);
    }
  }
}

