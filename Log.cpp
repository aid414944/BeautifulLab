#include "Log.h"

#ifdef __ANDROID__



#else

void log(const char *type, const char *fmt, ...) {
    puts(type);
    va_list  arg_ptr;
    va_start(arg_ptr, fmt);
    printf(fmt, arg_ptr);
    va_end(arg_ptr);
}

#endif
