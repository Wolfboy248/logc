#include <logc/console.h>

#include <stdio.h>

#define TERMINAL_WARN       "\x1b[33m"
#define TERMINAL_ERROR      "\x1b[31m"
#define TERMINAL_DEBUG      "\x1b[35m"
#define TERMINAL_DIM        "\x1b[4m"
#define TERMINAL_RESET   "\x1b[0m"

char* LOG_consoleFormatter(const LOG_LogMessage* msg) {
  static char buf[1024];
  char* col = "";

  switch (msg->level) {
    case LOG_LEVEL_ERROR:
    case LOG_LEVEL_FATAL:
      col = TERMINAL_ERROR;
      break;
    case LOG_LEVEL_WARN:
      col = TERMINAL_WARN;
      break;
    case LOG_LEVEL_DEBUG:
      col = TERMINAL_DEBUG;
      break;
    case LOG_LEVEL_INFO:
    default:
      break;
  }

  snprintf(buf, sizeof(buf), "%s[%s]" TERMINAL_RESET " " TERMINAL_DIM "%s:%d" TERMINAL_RESET  " > %s", col, LOG_LogLevelStr(msg->level), msg->file, msg->line, msg->message);
  return buf;
}

void LOG_consoleWrite(const LOG_LogMessage* msg, const LOG_LogDriver* driver) {
  char* formatted = driver->formatter(msg);
  fprintf(stdout, "%s\n", formatted);
}

LOG_LogDriver LOG_consoleDriver = {
  .name = "console",
#ifdef NDEBUG
  .level = LOG_LEVEL_WARN,
#else 
  .level = LOG_LEVEL_DEBUG,
#endif
  .formatter = LOG_consoleFormatter,
  .write = LOG_consoleWrite,
  .user_data = NULL,
  .enabled = true,
};
