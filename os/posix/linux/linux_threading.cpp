 
#include "os/os_specific.h"

#include "common/common.h"

#include <errno.h>
#include <semaphore.h>
#include <sys/prctl.h>
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
  prctl(PR_SET_NAME, (unsigned long)name.c_str(), 0, 0, 0);
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

// works for all posix except apple, hence being here
struct PosixSemaphore : public Semaphore
{
  ~PosixSemaphore() {}

  sem_t h;
};

Semaphore *Semaphore::Create()
{
  PosixSemaphore *sem = new PosixSemaphore();
  int err = sem_init(&sem->h, 0, 0);
  // only documented errors are too large initial value (impossible for 0) or for shared semaphores
  // going wrong (we're not shared)
  RDCASSERT(err == 0, (int)errno);
  return sem;
}

void Semaphore::Destroy()
{
  PosixSemaphore *sem = (PosixSemaphore *)this;
  sem_destroy(&sem->h);
  delete sem;
}

void Semaphore::Wake(uint32_t numToWake)
{
  PosixSemaphore *sem = (PosixSemaphore *)this;
  for(uint32_t i = 0; i < numToWake; i++)
    sem_post(&sem->h);
}

void Semaphore::WaitForWake()
{
  PosixSemaphore *sem = (PosixSemaphore *)this;

  // handle extremely moronic stupid signal interruptions
  do
  {
    int ret = sem_wait(&sem->h);

    if(ret == -1)
    {
      if(errno == EINTR)
        continue;

      RDCWARN("Semaphore wait failed: %d", errno);
    }
  } while(false);
}

Semaphore::Semaphore()
{
}

Semaphore::~Semaphore()
{
}

};
