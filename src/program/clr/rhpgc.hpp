#pragma once

#include "types.h"

// https://github.com/dotnet/runtime/blob/2330b4bef645bf8bcd3011f35968e55192c697f5/src/coreclr/nativeaot/Runtime/inc/MethodTable.h#L151
enum Flags {
    EETypeKindMask = 0x0003,
    RelatedTypeViaIATFlag = 0x0004,
    IsDynamicTypeFlag = 0x0008,
    HasFinalizerFlag = 0x0010,
    HasPointersFlag = 0x0020,
    GenericVarianceFlag = 0x0080,
    OptionalFieldsFlag = 0x0100,
    // Unused         = 0x0200,
    IsGenericFlag = 0x0400,
    ElementTypeMask = 0xf800,
    ElementTypeShift = 11,
};

struct MethodTable {
    ushort _usComponentSize;
    ushort _usFlags;
    uint _uBaseSize;
    union {
        // Kinds.CanonicalEEType
        MethodTable* _pBaseType;
        MethodTable** _ppBaseTypeViaIAT;

        // Kinds.ClonedEEType
        MethodTable* _pCanonicalType;
        MethodTable** _ppCanonicalTypeViaIAT;

        // Kinds.ArrayEEType
        MethodTable* _pRelatedParameterType;
        MethodTable** _ppRelatedParameterTypeViaIAT;
    } _relatedType;
    ushort _usNumVtableSlots;
    ushort _usNumInterfaces;
    uint _uHashCode;
    void* vtable[];
};

enum class CorElementType {
    End = 0x00,
    Void = 0x01,
    Boolean = 0x02,
    Char = 0x03,
    I1 = 0x04,
    U1 = 0x05,
    I2 = 0x06,
    U2 = 0x07,
    I4 = 0x08,
    U4 = 0x09,
    I8 = 0x0A,
    U8 = 0x0B,
    R4 = 0x0C,
    R8 = 0x0D,
    String = 0x0E,
    Ptr = 0x0F,
    Byref = 0x10,
    Valuetype = 0x11,
    Class = 0x12,
    Var = 0x13,
    Array = 0x14,
    Genericinst = 0x15,
    Typedbyref = 0x16,
    I = 0x18,
    U = 0x19,
    Fnptr = 0x1B,
    Object = 0x1C,
    Szarray = 0x1D,
    Mvar = 0x1E,
    CmodReqd = 0x1F,
    CmodOpt = 0x20,
    Internal = 0x21,
    Max = 0x22,
    Modifier = 0x40,
    Sentinel = 0x41,
    Pinned = 0x45,
};
