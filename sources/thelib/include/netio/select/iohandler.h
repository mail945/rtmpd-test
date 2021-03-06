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

#ifdef NET_SELECT

#include "common.h"
#include "netio/iohandlertype.h"

class BaseProtocol;

/*!
	@class IOHandler
 */
class DLLEXP IOHandler {
protected:
	static uint32_t _idGenerator;
	uint32_t _id;
	SOCKET_TYPE _inboundFd;
	SOCKET_TYPE _outboundFd;
	BaseProtocol *_pProtocol;
	IOHandlerType _type;
public:
	IOHandler(SOCKET_TYPE inboundFd, SOCKET_TYPE outboundFd, IOHandlerType type);
	virtual ~IOHandler();

	/*!
		@brief Returns the id of the IO handler.
	 */
	uint32_t GetId();

	/*!
		@brief Returns the id of the inbound file descriptor
	 */
	SOCKET_TYPE GetInboundFd();

	/*!
		@brief Returns the id of the outbound file descriptor
	 */
	SOCKET_TYPE GetOutboundFd();

	/*!
		@brief Returns the IOHandler type
	 */
	IOHandlerType GetType();

	/*!
		@brief Sets the protocol for the IO handler
		@param pProtocol
	 */
	void SetProtocol(BaseProtocol *pPotocol);

	/*!
		@brief Gets the protocol of the IO handler
	 */
	BaseProtocol *GetProtocol();
	virtual bool SignalOutputData() = 0;
	virtual bool OnEvent(select_event &event) = 0;

	/*!
		@brief Returns the string value of the IO handler type
		@param type: Type of IO handler. E.g. acceptor, tct carrier, udp carrier, etc.
	 */
	static string IOHTToString(IOHandlerType type);
	virtual void GetStats(Variant &info, uint32_t namespaceId = 0) = 0;
};

#endif /* NET_SELECT */
