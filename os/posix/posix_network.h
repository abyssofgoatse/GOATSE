 

#pragma once

namespace Network
{
uint32_t GetIPFromTCPSocket(int socket);
Socket *CreateAbstractServerSocket(uint16_t port, int queuesize);
Socket *CreateTCPServerSocket(const rdcstr &bindaddr, uint16_t port, int queuesize);
}
