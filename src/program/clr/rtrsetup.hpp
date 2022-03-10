#pragma once

#include "types.h"

namespace rtr {
    enum class HeaderFlags {
        PLATFORM_NEUTRAL_SOURCE = 0x00000001,   // Set if the original IL assembly was platform-neutral
        SKIP_TYPE_VALIDATION = 0x00000002,   // Set of methods with native code was determined using profile data
        PARTIAL = 0x00000004,
        NONSHARED_PINVOKE_STUBS = 0x00000008,   // PInvoke stubs compiled into image are non-shareable (no secret parameter)
        EMBEDDED_MSIL = 0x00000010,   // MSIL is embedded in the composite R2R executable
        COMPONENT = 0x00000020,   // This is the header describing a component assembly of composite R2R
    };

    // https://github.com/dotnet/runtime/blob/main/src/coreclr/tools/Common/Internal/Runtime/ModuleHeaders.cs#L46
    enum class SectionType {
        //
        // CoreCLR ReadyToRun sections
        //
        CompilerIdentifier = 100,
        ImportSections = 101,
        RuntimeFunctions = 102,
        MethodDefEntryPoints = 103,
        ExceptionInfo = 104,
        DebugInfo = 105,
        DelayLoadMethodCallThunks = 106,
        // 107 is deprecated - it was used by an older format of AvailableTypes
        AvailableTypes = 108,
        InstanceMethodEntryPoints = 109,
        InliningInfo = 110, // Added in v2.1, deprecated in 4.1
        ProfileDataInfo = 111, // Added in v2.2
        ManifestMetadata = 112, // Added in v2.3
        AttributePresence = 113, // Added in V3.1
        InliningInfo2 = 114, // Added in 4.1
        ComponentAssemblies = 115, // Added in 4.1
        OwnerCompositeExecutable = 116, // Added in 4.1
        PgoInstrumentationData = 117, // Added in 5.2
        ManifestAssemblyMvids = 118, // Added in 5.3

        //
        // CoreRT ReadyToRun sections
        //
        StringTable = 200, // Unused
        GCStaticRegion = 201,
        ThreadStaticRegion = 202,
        InterfaceDispatchTable = 203,
        TypeManagerIndirection = 204,
        EagerCctor = 205,
        FrozenObjectRegion = 206,
        GCStaticDesc = 207,
        ThreadStaticOffsetRegion = 208,
        ThreadStaticGCDescRegion = 209,
        ThreadStaticIndex = 210,
        LoopHijackFlag = 211,
        ImportAddressTables = 212,
        ModuleInitializerList = 213,

        // Sections 300 - 399 are reserved for RhFindBlob backwards compatibility
        ReadonlyBlobRegionStart = 300,
        ReadonlyBlobRegionEnd = 399,
    };

    struct Section {
        SectionType type;
        u32 flags;
        void* start;
        void* end;
    };

    struct Header {
        char magic[4];
        u16 majorVersion;
        u16 minorVersion;
        HeaderFlags flags;
        u16 numSections;
        u8 entrySize;
        u8 entryType;
        Section sections[];
    };

    namespace sections {
        enum GcStaticRegionConstants {
            Uninitialized = 1,
            PreInit = 2,
            Mask = Uninitialized | PreInit
        };
    }

    void prepare();
}