// log.h
// Simple logging surface for developer-oriented output.

#ifndef MINIJS_LOG_H
#define MINIJS_LOG_H

// Log level labels used for human-readable output.
#define MJ_LOG_LEVEL_DEBUG "DEBUG"
#define MJ_LOG_LEVEL_INFO "INFO"
#define MJ_LOG_LEVEL_WARN "WARN"
#define MJ_LOG_LEVEL_ERROR "ERROR"

// Base macro that records file and line information for each log call.
#define MJ_LOG(level, fmt, ...) mj_log((level), __FILE__, __LINE__, (fmt), ##__VA_ARGS__)
#define mj_log_debug(fmt, ...) MJ_LOG(MJ_LOG_LEVEL_DEBUG, (fmt), ##__VA_ARGS__)
#define mj_log_info(fmt, ...) MJ_LOG(MJ_LOG_LEVEL_INFO, (fmt), ##__VA_ARGS__)
#define mj_log_warn(fmt, ...) MJ_LOG(MJ_LOG_LEVEL_WARN, (fmt), ##__VA_ARGS__)
#define mj_log_error(fmt, ...) MJ_LOG(MJ_LOG_LEVEL_ERROR, (fmt), ##__VA_ARGS__)

// Low-level log implementation used by the macros above.
void mj_log(const char *level, const char *file, int line, const char *fmt, ...);

#endif
