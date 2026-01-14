 

#include "common/common.h"
#include "os/os_specific.h"

class BSDCallstack : public Callstack::Stackwalk
{
public:
  BSDCallstack()
  {
    RDCEraseEl(addrs);
    numLevels = 0;
  }
  BSDCallstack(uint64_t *calls, size_t num) { Set(calls, num); }
  ~BSDCallstack() {}
  void Set(uint64_t *calls, size_t num)
  {
    numLevels = num;
    for(size_t i = 0; i < numLevels; i++)
      addrs[i] = calls[i];
  }

  size_t NumLevels() const { return 0; }
  const uint64_t *GetAddrs() const { return addrs; }
private:
  BSDCallstack(const Callstack::Stackwalk &other);

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
  return new BSDCallstack();
}

Stackwalk *Create()
{
  return new BSDCallstack(NULL, 0);
}

bool GetLoadedModules(byte *buf, size_t &size)
{
  size = 0;

  if(buf)
    memcpy(buf, "BSD_CALL", 8);

  size += 8;

  return true;
}

StackResolver *MakeResolver(bool interactive, byte *moduleDB, size_t DBSize,
                            RENDERDOC_ProgressCallback progress)
{
  RDCERR("Callstack resolving not supported on *BSD.");
  return NULL;
}
};
