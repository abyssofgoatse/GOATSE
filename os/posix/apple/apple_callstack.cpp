 
#include "common/common.h"
#include "os/os_specific.h"

class AppleCallstack : public Callstack::Stackwalk
{
public:
  AppleCallstack()
  {
    RDCEraseEl(addrs);
    numLevels = 0;
  }
  AppleCallstack(uint64_t *calls, size_t num) { Set(calls, num); }
  ~AppleCallstack() {}
  void Set(uint64_t *calls, size_t num)
  {
    numLevels = num;
    for(size_t i = 0; i < numLevels; i++)
      addrs[i] = calls[i];
  }

  size_t NumLevels() const { return 0; }
  const uint64_t *GetAddrs() const { return addrs; }
private:
  AppleCallstack(const Callstack::Stackwalk &other);

  uint64_t addrs[128];
  size_t numLevels;
};

namespace Callstack
{
void Init()
{
}

Stackwalk *Collect()
{
  return new AppleCallstack();
}

Stackwalk *Create()
{
  return new AppleCallstack(NULL, 0);
}

bool GetLoadedModules(byte *buf, size_t &size)
{
  size = 0;

  if(buf)
    memcpy(buf, "APPLCALL", 8);

  size += 8;

  return true;
}

StackResolver *MakeResolver(bool interactive, byte *moduleDB, size_t DBSize,
                            RENDERDOC_ProgressCallback progress)
{
  RDCERR("Callstack resolving not supported on Apple.");
  return NULL;
}
};
