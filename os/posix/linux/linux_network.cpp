 

#include "os/os_specific.h"
#include "os/posix/posix_network.h"

namespace Network
{
void SocketPostSend()
{
  // only needed for awful hack on Android
}

uint32_t Socket::GetRemoteIP() const
{
  return GetIPFromTCPSocket((int)socket);
}

Socket *CreateServerSocket(const rdcstr &bindaddr, uint16_t port, int queuesize)
{
  return CreateTCPServerSocket(bindaddr, port, queuesize);
}
};
