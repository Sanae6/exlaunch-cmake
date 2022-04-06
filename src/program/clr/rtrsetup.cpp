#include "rtrsetup.hpp"
#include "rhpgc.hpp"
#include "lib.hpp"
#include "program/util/logger.hpp"
#include <utility>

//extern "C" rtr::Header __ReadyToRunHeader;

void rtr::prepare() {
//    Header* header = &__ReadyToRunHeader;
//    if (__ReadyToRunHeader == nullptr) {
//        exl::logger::log("No ReadyToRun support available");
//        return;
//    }
//
//    for (u16 i = 0; i < header->numSections; ++i) {
//        Section section = header->sections[i];
//
//        switch (section.type) {
//            case SectionType::GCStaticRegion: {
//                for (void*** block = static_cast<void***>(section.start); block < section.end; block++) {
//                    void** baseBlockPtr = *block;
//                    auto blockAddr = reinterpret_cast<uintptr_t>(*baseBlockPtr);
//
//                    Object* heap = RhpGcAlloc(
//                            reinterpret_cast<MethodTable*>(blockAddr & ~static_cast<uintptr_t>(std::to_underlying(sections::GcStaticRegionConstants::Mask))),
//                            0,
//                            0);
//                    EXL_ASSERT(heap != nullptr);
//
//                    if (blockAddr & std::to_underlying(sections::GcStaticRegionConstants::PreInit)) {
//                        void* preInitData = *(baseBlockPtr + 1);
//                        memcpy(heap->getRawData(), preInitData, heap->getMethodTable()->_uBaseSize);
//                    }
//
//                    *baseBlockPtr = heap;
//                }
//                break;
//            }
//            default:
//                break;
//        }
//    }
}
