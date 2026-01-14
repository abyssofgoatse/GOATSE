 

#include "os/os_specific.h"

#include <dispatch/dispatch.h>
#include <mach/mach_time.h>

double Timing::GetTickFrequency()
{
  mach_timebase_info_data_t timeInfo;
  mach_timebase_info(&timeInfo);

  uint64_t numer = timeInfo.numer;
  uint64_t denom = timeInfo.denom;
  return ((double)denom / (double)numer) * 1000000.0;
}

uint64_t Timing::GetTick()
{
  return mach_absolute_time();
}

void Threading::SetCurrentThreadName(const rdcstr &name)
{
}

uint32_t Threading::NumberOfCores()
{
  long ret = sysconf(_SC_NPROCESSORS_ONLN);
  if(ret <= 0)
    return 1;
  return uint32_t(ret);
}

namespace Threading
{

struct AppleSemaphore : public Semaphore
{
  ~AppleSemaphore() {}

  dispatch_semaphore_t h;
};

Semaphore *Semaphore::Create()
{
  AppleSemaphore *sem = new AppleSemaphore();
  sem->h = dispatch_semaphore_create(0);
  return sem;
}

void Semaphore::Destroy()
{
  AppleSemaphore *sem = (AppleSemaphore *)this;
  dispatch_release(sem->h);
  delete sem;
}

void Semaphore::Wake(uint32_t numToWake)
{
  AppleSemaphore *sem = (AppleSemaphore *)this;
  for(uint32_t i = 0; i < numToWake; i++)
    dispatch_semaphore_signal(sem->h);
}

void Semaphore::WaitForWake()
{
  AppleSemaphore *sem = (AppleSemaphore *)this;
  // no timeout, so no point checking return value as that's the only failure case
  dispatch_semaphore_wait(sem->h, DISPATCH_TIME_FOREVER);
}

Semaphore::Semaphore()
{
}

Semaphore::~Semaphore()
{
}

};
