//
// Created by lhk12 on 2023-03-22.
//

#ifndef OPENGLDEMO_LOG_H
#define OPENGLDEMO_LOG_H

#include <android/log.h>
#include <sys/time.h>


#define  LOGE(tag, ...)  __android_log_print(ANDROID_LOG_ERROR,tag,__VA_ARGS__)
#define  LOGV(tag, ...)  __android_log_print(ANDROID_LOG_VERBOSE,tag,__VA_ARGS__)
#define  LOGD(tag, ...)  __android_log_print(ANDROID_LOG_DEBUG,tag,__VA_ARGS__)
#define  LOGI(tag, ...)  __android_log_print(ANDROID_LOG_INFO,tag,__VA_ARGS__)

#define FUN_BEGIN_TIME(FUN) {\
    LOGCATE("%s:%s func start", __FILE__, FUN); \
    long long t0 = GetSysCurrentTime();

#define FUN_END_TIME(FUN) \
    long long t1 = GetSysCurrentTime(); \
    LOGCATE("%s:%s func cost time %ldms", __FILE__, FUN, (long)(t1-t0));}

#define BEGIN_TIME(FUN) {\
    LOGCATE("%s func start", FUN); \
    long long t0 = GetSysCurrentTime();

#define END_TIME(FUN) \
    long long t1 = GetSysCurrentTime(); \
    LOGCATE("%s func cost time %ldms", FUN, (long)(t1-t0));}

static long long GetSysCurrentTime() {
    struct timeval time;
    gettimeofday(&time, NULL);
    long long curTime = ((long long) (time.tv_sec)) * 1000 + time.tv_usec / 1000;
    return curTime;
}

#define GO_CHECK_GL_ERROR(...)   LOGCATE("CHECK_GL_ERROR %s glGetError = %d, line = %d, ",  __FUNCTION__, glGetError(), __LINE__)

#define DEBUG_LOGCATE(...) LOGCATE("DEBUG_LOGCATE %s line = %d",  __FUNCTION__, __LINE__)
#endif //OPENGLDEMO_LOG_H
