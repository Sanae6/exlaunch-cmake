#include "types.h"
#ifdef LOGGER_ENABLED
#include "util/logger.hpp"
#endif
#include "util/symbol.hpp"
#include "lib.hpp"
#include "clr/rtrsetup.hpp"

extern "C" uintptr_t ExlaunchGetSymbol(const char* text) {
    return exl::ro::GetSymbol(text);
}

extern "C" void ExlaunchLog(const char* text) {
#ifdef LOGGER_ENABLED
    exl::logger::log("%s\n", text);
#endif
}

extern "C" void ExlaunchAbort(uint32_t value) {
    exl::diag::AbortImpl(exl::diag::AbortCtx{
            static_cast<Result>(value)
    });
}

extern "C" uintptr_t ExlaunchHook(uintptr_t hook, uintptr_t callback, bool trampoline) {
    return exl::util::Hook::HookFuncCommon(hook, callback, true);
}


extern void exl_setup() {
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::util::Hook::Initialize();

    rtr::prepare();
}