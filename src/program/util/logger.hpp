#pragma once

#include <cstdarg>

#ifdef LOGGER_ENABLED
namespace exl::logger {
    void log(const char* fmt, ...);
    void log(const char* fmt, va_list args);
}
#endif