#include "rhpinvoke.hpp"
#include "lib/diag/assert.hpp"

extern "C" void RhpPInvoke(PInvokeTransitionFrame* frame) {}
extern "C" void RhpPInvokeReturn(PInvokeTransitionFrame* frame) {}
extern "C" void RhpReversePInvoke(ReversePInvokeFrame* frame) {}
extern "C" void RhpReversePInvokeReturn(ReversePInvokeFrame* frame) {}
extern "C" void RhpFailFast() {
    EXL_ABORT(0x11111111);
}