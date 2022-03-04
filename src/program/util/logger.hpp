#pragma once

#include <cstdarg>

namespace exl::logger {
    void log(const char* fmt, ...);
    void log(const char* fmt, va_list args);
}