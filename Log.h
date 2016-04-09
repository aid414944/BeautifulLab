#ifndef LOG_H
#define LOG_H


#ifdef __ANDROID__

#include <android/log.h>
#define LOG "naruto.so"
#define logDebug(...) __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__)
#define logInfo(...) __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__)
#define logWarn(...) __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__)
#define logError(...) __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__)
#define logFatal(...) __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__)

#else

#include <stdio.h>
#include <stdarg.h>

#define logDebug(...) log("Debug: ",__VA_ARGS__)
#define logInfo(...) log("Info: ",__VA_ARGS__)
#define logWarn(...) log("Warn: ",__VA_ARGS__)
#define logError(...) log("Error: ",__VA_ARGS__)
#define logFatal(...) log("Fatal: ",__VA_ARGS__)
void log(const char * type, const char * fmt, ...);


#endif

#endif // LOG_H
