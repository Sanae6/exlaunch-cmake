#include "types.h"
#include "util/logger.hpp"
#include "util/symbol.hpp"
#include "lib/diag/abort.hpp"
#include "lib/util/nx_hook.hpp"

extern "C" uintptr_t ExlaunchGetSymbol(const char* text) {
    return exl::ro::GetSymbol(text);
}

extern "C" void ExlaunchLog(const char* text) {
    exl::logger::log("%s\n", text);
}

extern "C" void ExlaunchAbort(uint32_t value) {
    exl::diag::AbortImpl(exl::diag::AbortCtx{
            static_cast<Result>(value)
    });
}

extern "C" void* ExlaunchHook(uintptr_t hook, uintptr_t callback) {
    return (void*)(exl::util::Hook::HookFunc<void (*)()>(hook, callback, true));
}
