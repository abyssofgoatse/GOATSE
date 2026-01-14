 

#pragma once

#include "common/common.h"
#include "os/os_specific.h"

namespace Threading
{
class ScopedLock
{
public:
  ScopedLock(CriticalSection *cs) : m_CS(cs)
  {
    if(m_CS)
      m_CS->Lock();
  }
  ~ScopedLock()
  {
    if(m_CS)
      m_CS->Unlock();
  }

private:
  CriticalSection *m_CS;
};

class ScopedReadLock
{
public:
  ScopedReadLock(RWLock &rw) : m_RW(&rw) { m_RW->ReadLock(); }
  ~ScopedReadLock() { m_RW->ReadUnlock(); }
private:
  RWLock *m_RW;
};

class ScopedWriteLock
{
public:
  ScopedWriteLock(RWLock &rw) : m_RW(&rw) { m_RW->WriteLock(); }
  ~ScopedWriteLock() { m_RW->WriteUnlock(); }
private:
  RWLock *m_RW;
};

class SpinLock
{
public:
  void Lock()
  {
    while(!Trylock())
    {
      // spin!
    }
  }
  bool Trylock() { return Atomic::CmpExch32(&val, 0, 1) == 0; }
  void Unlock() { Atomic::CmpExch32(&val, 1, 0); }
private:
  int32_t val = 0;
};

class ScopedSpinLock
{
public:
  ScopedSpinLock() = default;
  ScopedSpinLock(SpinLock &spin) : m_Spin(&spin) { m_Spin->Lock(); }
  ScopedSpinLock(const ScopedSpinLock &) = delete;
  ScopedSpinLock &operator=(const ScopedSpinLock &) = delete;
  ScopedSpinLock &operator=(ScopedSpinLock &&other)
  {
    if(m_Spin != NULL)
      m_Spin->Unlock();
    m_Spin = other.m_Spin;
    other.m_Spin = NULL;
    return *this;
  }
  ScopedSpinLock(ScopedSpinLock &&other) : m_Spin(other.m_Spin) { other.m_Spin = NULL; }
  ~ScopedSpinLock()
  {
    if(m_Spin != NULL)
    {
      m_Spin->Unlock();
      m_Spin = NULL;
    }
  }

private:
  SpinLock *m_Spin = NULL;
};

namespace JobSystem
{
struct Job;
void Init(uint32_t numThreads = 0);
void Shutdown();
Job *AddJob(std::function<void()> &&cb, const rdcarray<Job *> &parents = {});
void SyncAllJobs();
uint32_t GetCountWorkers();
};

};

#define SCOPED_LOCK(cs) Threading::ScopedLock CONCAT(scopedlock, __LINE__)(&cs);
#define SCOPED_LOCK_OPTIONAL(cs, cond) \
  Threading::ScopedLock CONCAT(scopedlock, __LINE__)(cond ? &cs : NULL);

#define SCOPED_READLOCK(rw) Threading::ScopedReadLock CONCAT(scopedlock, __LINE__)(rw);
#define SCOPED_WRITELOCK(rw) Threading::ScopedWriteLock CONCAT(scopedlock, __LINE__)(rw);

#define SCOPED_SPINLOCK(cs) Threading::ScopedSpinLock CONCAT(scopedlock, __LINE__)(cs);
