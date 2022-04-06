#pragma once

#include "types.h"

struct MethodTable;

class Object {
    MethodTable* methodTable;
public:
    void setMethodTable(MethodTable* newMethodTable) { methodTable = newMethodTable; }

    MethodTable* getMethodTable() { return methodTable; }
    void* getRawData() {
        return reinterpret_cast<void*>(((uintptr_t) this) + sizeof(uintptr_t));
    }
};

class Array : public Object {
    s32 size;
    char data[0];

public:
    void setSize(int newSize) { size = newSize; }

    [[nodiscard]] s32 getSize() const { return size; }
};


class String : public Object {
    u32 length;
    u16 firstChar;

public:
    void setLength(u32 newLength) { length = newLength; }

    u32 getLength() const { return length; }
    u16 getFirstChar() const { return firstChar; }
};