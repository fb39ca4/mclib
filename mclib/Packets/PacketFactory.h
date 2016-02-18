#ifndef PACKETS_PACKET_FACTORY_H_
#define PACKETS_PACKET_FACTORY_H_

#include "../DataBuffer.h"
#include "../Protocol.h"
#include "Packet.h"

namespace Minecraft {
namespace Packets {

class PacketFactory {
public:
    static MCLIB_API Packet* CreatePacket(Protocol::State state, DataBuffer data, std::size_t length);
    static void MCLIB_API FreePacket(Packet* packet);
};

} // ns Packets
} // ns Minecraft

#endif