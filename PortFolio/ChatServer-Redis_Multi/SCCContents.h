#pragma once
#include <SerialLizeBuffer_AND_RingBuffer/Packet.h>
#include <Common/CommonProtocol.h>


void MAKE_CS_CHAT_RES_LOGIN(BYTE status, INT64 accountNo, SmartPacket& sp);
void MAKE_CS_CHAT_RES_SECTOR_MOVE(INT64 accountNo, WORD sectorX, WORD sectorY, Packet* pPacket);
void MAKE_CS_CHAT_RES_MESSAGE(INT64 accountNo, WCHAR* pID, WCHAR* pNickName, WORD messageLen, WCHAR* pMessage, Packet* pPacket);
