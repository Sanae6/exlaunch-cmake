#include "rhpgc.hpp"
#include "lib/alloc.hpp"

extern "C" void* RhpNewFast(MethodTable* methodTable) {
    void* data = malloc(methodTable->_uBaseSize);

    *((MethodTable**)data) = methodTable;
    return data;
}

// RhpAssignRef(Object** dst, Object* src)
//
// Write barrier for writes to objects that are known to
// reside on the managed heap.
#ifdef __LP64__
extern "C" void RhpAssignRefArm64(void* dst, void* src) {} // todo care about write barriers?
#else
extern "C" void RhpAssignRefArm(void* dst, void* src) {} // todo care about write barriers?
#endif
