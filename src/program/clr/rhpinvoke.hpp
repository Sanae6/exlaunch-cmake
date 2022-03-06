#pragma once

#include <cstddef>
#include <cstdint>

#include "curarch.hpp"

#ifdef ARM64
enum PInvokeTransitionFrameFlags : uint64_t {
    // NOTE: Keep in sync with ndp\FxCore\CoreRT\src\Native\Runtime\arm64\AsmMacros.h

    // NOTE: The order in which registers get pushed in the PInvokeTransitionFrame's m_PreservedRegs list has
    //       to match the order of these flags (that's also the order in which they are read in StackFrameIterator.cpp

    // standard preserved registers
    PTFF_SAVE_X19 = 0x0000000000000001,
    PTFF_SAVE_X20 = 0x0000000000000002,
    PTFF_SAVE_X21 = 0x0000000000000004,
    PTFF_SAVE_X22 = 0x0000000000000008,
    PTFF_SAVE_X23 = 0x0000000000000010,
    PTFF_SAVE_X24 = 0x0000000000000020,
    PTFF_SAVE_X25 = 0x0000000000000040,
    PTFF_SAVE_X26 = 0x0000000000000080,
    PTFF_SAVE_X27 = 0x0000000000000100,
    PTFF_SAVE_X28 = 0x0000000000000200,

    PTFF_SAVE_SP = 0x0000000000000400,   // Used for 'coop pinvokes' in runtime helper routines.  Methods with
    // PInvokes are required to have a frame pointers, but methods which
    // call runtime helpers are not.  Therefore, methods that call runtime
    // helpers may need SP to seed the stackwalk.

    // Scratch registers
    PTFF_SAVE_X0 = 0x0000000000000800,
    PTFF_SAVE_X1 = 0x0000000000001000,
    PTFF_SAVE_X2 = 0x0000000000002000,
    PTFF_SAVE_X3 = 0x0000000000004000,
    PTFF_SAVE_X4 = 0x0000000000008000,
    PTFF_SAVE_X5 = 0x0000000000010000,
    PTFF_SAVE_X6 = 0x0000000000020000,
    PTFF_SAVE_X7 = 0x0000000000040000,
    PTFF_SAVE_X8 = 0x0000000000080000,
    PTFF_SAVE_X9 = 0x0000000000100000,
    PTFF_SAVE_X10 = 0x0000000000200000,
    PTFF_SAVE_X11 = 0x0000000000400000,
    PTFF_SAVE_X12 = 0x0000000000800000,
    PTFF_SAVE_X13 = 0x0000000001000000,
    PTFF_SAVE_X14 = 0x0000000002000000,
    PTFF_SAVE_X15 = 0x0000000004000000,
    PTFF_SAVE_X16 = 0x0000000008000000,
    PTFF_SAVE_X17 = 0x0000000010000000,
    PTFF_SAVE_X18 = 0x0000000020000000,

    PTFF_SAVE_FP = 0x0000000040000000,   // should never be used, we require FP frames for methods with
    // pinvoke and it is saved into the frame pointer field instead

    PTFF_SAVE_LR = 0x0000000080000000,   // this is useful for the case of loop hijacking where we need both
    // a return address pointing into the hijacked method and that method's
    // lr register, which may hold a gc pointer

    // used by hijack handler to report return value of hijacked method
    PTFF_X0_IS_GCREF = 0x0000000100000000,
    PTFF_X0_IS_BYREF = 0x0000000200000000,
    PTFF_X1_IS_GCREF = 0x0000000400000000,
    PTFF_X1_IS_BYREF = 0x0000000800000000,

    PTFF_THREAD_ABORT = 0x0000001000000000,   // indicates that ThreadAbortException should be thrown when returning from the transition
};
#else
enum PInvokeTransitionFrameFlags {
    // NOTE: The order in which registers get pushed in the PInvokeTransitionFrame's m_PreservedRegs list has
    //       to match the order of these flags (that's also the order in which they are read in StackFrameIterator.cpp

    // standard preserved registers
    PTFF_SAVE_RBX = 0x00000001,
    PTFF_SAVE_RSI = 0x00000002,
    PTFF_SAVE_RDI = 0x00000004,
    PTFF_SAVE_RBP = 0x00000008,   // should never be used, we require RBP frames for methods with
    // pinvoke and it is saved into the frame pointer field instead
    PTFF_SAVE_R12 = 0x00000010,
    PTFF_SAVE_R13 = 0x00000020,
    PTFF_SAVE_R14 = 0x00000040,
    PTFF_SAVE_R15 = 0x00000080,

    PTFF_SAVE_RSP = 0x00008000,   // Used for 'coop pinvokes' in runtime helper routines.  Methods with
    // PInvokes are required to have a frame pointers, but methods which
    // call runtime helpers are not.  Therefore, methods that call runtime
    // helpers may need RSP to seed the stackwalk.
    //
    // NOTE: despite the fact that this flag's bit is out of order, it is
    // still expected to be saved here after the preserved registers and
    // before the scratch registers
    PTFF_SAVE_RAX = 0x00000100,
    PTFF_SAVE_RCX = 0x00000200,
    PTFF_SAVE_RDX = 0x00000400,
    PTFF_SAVE_R8 = 0x00000800,
    PTFF_SAVE_R9 = 0x00001000,
    PTFF_SAVE_R10 = 0x00002000,
    PTFF_SAVE_R11 = 0x00004000,

    PTFF_RAX_IS_GCREF = 0x00010000,   // used by hijack handler to report return value of hijacked method
    PTFF_RAX_IS_BYREF = 0x00020000,   // used by hijack handler to report return value of hijacked method

    PTFF_THREAD_ABORT = 0x00040000,   // indicates that ThreadAbortException should be thrown when returning from the transition
};
#endif

struct PInvokeTransitionFrame {
#ifdef ARM
    void* chainPtr;
#endif
#ifdef ARM64
    void* framePtr;
    void* rip;
#else
    void* rip;
    void* framePtr;
#endif
    void* threadPtr;
    size_t flags;
    size_t preservedRegs[];
};

struct ReversePInvokeFrame {
    void*   savedPInvokeTransitionFrame;
    void* savedThreadPtr;
};