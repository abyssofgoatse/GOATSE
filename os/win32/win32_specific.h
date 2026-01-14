 

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <intrin.h>
#include <stdlib.h>
#include <windows.h>
#include "data/resource.h"

#define EndianSwap16(x) _byteswap_ushort(x)
#define EndianSwap32(x) _byteswap_ulong(x)
#define EndianSwap64(x) _byteswap_uint64(x)

#define EmbeddedResourceType int
#define EmbeddedResource(filename) CONCAT(RESOURCE_, filename)

#define GetEmbeddedResource(filename) GetDynamicEmbeddedResource(EmbeddedResource(filename))
rdcstr GetDynamicEmbeddedResource(int resource);

namespace OSUtility
{
inline void ForceCrash()
{
  *((int *)NULL) = 0;
}
inline bool DebuggerPresent()
{
  return ::IsDebuggerPresent() == TRUE;
}
struct DLLFileVersion
{
  uint16_t major, minor, build, revision;

  bool operator==(const DLLFileVersion &o) const
  {
    return major == o.major && minor == o.minor && build == o.build && revision == o.revision;
  }
};
DLLFileVersion GetDLLVersion(const rdcstr &path);
DLLFileVersion GetDLLVersion(HMODULE mod);
};

namespace Threading
{
typedef CriticalSectionTemplate<CRITICAL_SECTION> CriticalSection;
typedef RWLockTemplate<SRWLOCK> RWLock;
};

namespace Bits
{
inline uint32_t CountLeadingZeroes(uint32_t value)
{
  DWORD index;
  BOOLEAN result = _BitScanReverse(&index, value);
  return (result == TRUE) ? (index ^ 31) : 32;
}

#if ENABLED(RDOC_X64)
inline uint64_t CountLeadingZeroes(uint64_t value)
{
  DWORD index;
  BOOLEAN result = _BitScanReverse64(&index, value);
  return (result == TRUE) ? (index ^ 63) : 64;
}
#endif

inline uint32_t CountTrailingZeroes(uint32_t value)
{
  DWORD index;
  BOOLEAN result = _BitScanForward(&index, value);
  return (result == TRUE) ? index : 32;
}

#if ENABLED(RDOC_X64)
inline uint64_t CountTrailingZeroes(uint64_t value)
{
  DWORD index;
  BOOLEAN result = _BitScanForward64(&index, value);
  return (result == TRUE) ? index : 64;
}
#endif

inline uint32_t CountOnes(uint32_t value)
{
  return __popcnt(value);
}

#if ENABLED(RDOC_X64)
inline uint64_t CountOnes(uint64_t value)
{
  return __popcnt64(value);
}
#endif
};
