 

#include <arpa/inet.h>
#include <unistd.h>
#include "os/os_specific.h"
#include "os/posix/posix_network.h"

namespace Network
{
void SocketPostSend()
{
  // we need to throttle android sending to ensure it never gets ahead of the PC otherwise the
  // forwarded port may encounter a EWOULDBLOCK error.
  // adb is buggy and will scompletely drop all writes as soon as a write blocks:
  // https://issuetracker.google.com/issues/139078301
  //
  // Throttling the device end is a hack but is reasonably reliable as we assume the PC side is fast
  // enough to read it. Since we batch most sends, sleeping on each send is not too costly, but this
  // may have some impact especially around small packets (we force a flush on the end of each
  // chunk/packet).
  usleep(1500);
}

uint32_t Socket::GetRemoteIP() const
{
  // Android uses abstract sockets which are only "localhost" accessible
  return MakeIP(127, 0, 0, 1);
}

Socket *CreateServerSocket(const rdcstr &, uint16_t port, int queuesize)
{
  return CreateAbstractServerSocket(port, queuesize);
}
};
