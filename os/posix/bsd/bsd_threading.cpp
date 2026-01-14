 

#include "os/os_specific.h"

#include <time.h>
#include <unistd.h>

double Timing::GetTickFrequency()
{
  return 1000000.0;
}

uint64_t Timing::GetTick()
{
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return uint64_t(ts.tv_sec) * 1000000000ULL + uint32_t(ts.tv_nsec & 0xffffffff);
}

void Threading::SetCurrentThreadName(const rdcstr &name)
{
}
