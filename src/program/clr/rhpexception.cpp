
#include "lib.hpp"

extern "C" void RhpThrowEx(void* ex) {
    EXL_ABORT(MAKERESULT(163, 0xD001));
}