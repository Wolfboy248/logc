#include <logc/file.h>

#include <stdio.h>
#include <time.h>
#include <logc/types.h>

char* LOG_fileFormatter(const LOG_LogMessage* msg) {
  static char buf[1024];

  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  char buffer[100];

  strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", t);

  snprintf(buf, sizeof(buf), "[%s] [%s] %s:%d > %s", buffer, LOG_LogLevelStr(msg->level), msg->file, msg->line, msg->message);
  return buf;
}

void LOG_fileWrite(const LOG_LogMessage* msg, const LOG_LogDriver* driver) {
  const char* filename = (const char*)driver->user_data;
  FILE* f = fopen(filename, "a");
  if (!f) return;
  char* formatted = driver->formatter(msg);
  fprintf(f, "%s\n", formatted);
  fclose(f);
}

LOG_LogDriver LOG_fileDriver = {
  .name = "file",
#ifdef NDEBUG
  .level = LOG_LEVEL_DEBUG,
#else 
  .level = LOG_LEVEL_WARN,
#endif
  .formatter = LOG_fileFormatter,
  .write = LOG_fileWrite,
  .enabled = false,
};

