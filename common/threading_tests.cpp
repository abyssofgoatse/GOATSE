 

#include "common/threading.h"
#include "os/os_specific.h"

#if ENABLED(ENABLE_UNIT_TESTS)

#include "catch/catch.hpp"

static int value = 0;

TEST_CASE("Test spin lock", "[threading]")
{
  int finalValue = 0;

  rdcarray<Threading::ThreadHandle> threads;
  rdcarray<int> threadcount;

  threads.resize(8);
  threadcount.resize(8);

  Threading::SpinLock lock;

  for(int i = 0; i < 8; i++)
  {
    threadcount[i] = (rand() & 0xff) << 4;

    finalValue += threadcount[i];
  }

  for(int i = 0; i < 8; i++)
  {
    threads[i] = Threading::CreateThread([&lock, &threadcount, i]() {
      for(int c = 0; c < threadcount[i]; c++)
      {
        lock.Lock();
        value++;
        lock.Unlock();
      }
    });
  }

  for(Threading::ThreadHandle t : threads)
  {
    Threading::JoinThread(t);
    Threading::CloseThread(t);
  }

  CHECK(finalValue == value);
}

#endif    // ENABLED(ENABLE_UNIT_TESTS)
