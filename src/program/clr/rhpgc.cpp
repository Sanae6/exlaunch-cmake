#include "curarch.hpp"
#include "rhpgc.hpp"
#include "lib.hpp"

extern "C" {

Object* RhpGcAlloc(MethodTable* methodTable, u32 _flags, uintptr_t elementCount) {
    size_t finalSize = methodTable->_uBaseSize;

    if (methodTable->_usComponentSize > 0) {
        // usually you would do some sort of size checks to prevent certain sizes of allocations,
        // however, your mother.
        finalSize += elementCount * methodTable->_usComponentSize;
        finalSize = ALIGN_UP(finalSize, sizeof(uintptr_t));
    } else {
        EXL_ASSERT(elementCount == 0);
    }

    auto* object = reinterpret_cast<Object*>(std::malloc(finalSize));

    EXL_ASSERT(object != nullptr);

    object->setMethodTable(methodTable);

    return object;
}

Object* RhpNewFast(MethodTable* methodTable) {
    return RhpGcAlloc(methodTable, 0, 0);
}

void* RhpNewArray(MethodTable* methodTable, int length) {
    if (length > 0x7FFFFFFF) {
        svcBreak(0x83, reinterpret_cast<u64>(methodTable), methodTable->_uBaseSize);
    }
    return RhpGcAlloc(methodTable, 0, length);
}

// RhpAssignRef(Object** dst, Object* src) (i don't know how to implement this)
//
// Write barrier for writes to objects that are known to
// reside on the managed heap.
// TODO: learn about write barriers and their use
#ifdef ARM64
void RhpAssignRefArm64(void* dst, void* src) {}
#else
void RhpAssignRefArm(void* dst, void* src) {}
#endif
}