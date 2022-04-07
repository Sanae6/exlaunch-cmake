#include "lib.hpp"
#include "../util/logger.hpp"
#include "object.hpp"

extern "C" void RhpThrowEx(Object* exception) {
    exl::logger::log("Fatal exception occurred\n");

    EXL_ABORT(MAKERESULT(163, 0xD001));
}