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

#ifdef NET_KQUEUE

#include "netio/kqueue/iohandler.h"

class UDPCarrier
: public IOHandler {
private:
	sockaddr_in _peerAddress;
	sockaddr_in _nearAddress;
	string _nearIp;
	uint16_t _nearPort;
	uint64_t _rx;
	uint64_t _tx;
	Variant _parameters;
	int32_t _ioAmount;
private:
	UDPCarrier(SOCKET_TYPE fd);
public:
	virtual ~UDPCarrier();

	virtual bool OnEvent(struct kevent &event);
	virtual bool SignalOutputData();
	virtual void GetStats(Variant &info, uint32_t namespaceId = 0);

	Variant &GetParameters();
	void SetParameters(Variant parameters);
	bool StartAccept();

	string GetFarEndpointAddress();
	uint16_t GetFarEndpointPort();
	string GetNearEndpointAddress();
	uint16_t GetNearEndpointPort();

	static UDPCarrier* Create(string bindIp, uint16_t bindPort, uint16_t ttl,
			uint16_t tos, string ssmIp);
	static UDPCarrier* Create(string bindIp, uint16_t bindPort,
			BaseProtocol *pProtocol, uint16_t ttl, uint16_t tos, string ssmIp);
private:
	bool Setup(Variant &settings);
	bool GetEndpointsInfo();

};

#endif /* NET_KQUEUE */
