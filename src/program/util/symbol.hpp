#define GET_SYMBOL(name) exl::ro::GetSymbol(#name)

namespace exl::ro {
    uintptr_t GetSymbol(const char* name);
}