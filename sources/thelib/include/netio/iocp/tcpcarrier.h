/*
 *  Copyright (c) 2010,
 *  Gavriloaie Eugen-Andrei (shiretu@gmail.com)
 *
 *  This file is part of crtmpserver.
 *  crtmpserver is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  crtmpserver is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with crtmpserver.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef NET_IOCP

#include "netio/iocp/iohandler.h"

class DLLEXP TCPCarrier
: public IOHandler {
private:
	sockaddr_in _farAddress;
	string _farIp;
	uint16_t _farPort;
	sockaddr_in _nearAddress;
	string _nearIp;
	uint16_t _nearPort;
	uint64_t _rx;
	uint64_t _tx;
	int32_t _ioAmount;
	iocp_event_tcp_read *_pReadEvent;
	iocp_event_tcp_write *_pWriteEvent;
public:
	TCPCarrier(SOCKET_TYPE fd, bool registerIOCPFD);
	virtual ~TCPCarrier();
	virtual void CancelIO();
	virtual bool OnEvent(iocp_event &event);
	virtual bool SignalOutputData();
	iocp_event_tcp_read *GetReadEvent();
	virtual void GetStats(Variant &info, uint32_t namespaceId = 0);


	sockaddr_in &GetFarEndpointAddress();
	string GetFarEndpointAddressIp();
	uint16_t GetFarEndpointPort();
	sockaddr_in &GetNearEndpointAddress();
	string GetNearEndpointAddressIp();
	uint16_t GetNearEndpointPort();
private:
	bool GetEndpointsInfo();
};

#endif /* NET_IOCP */
