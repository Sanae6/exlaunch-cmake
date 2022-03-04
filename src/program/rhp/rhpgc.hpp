#pragma once

#include "types.h"

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
};