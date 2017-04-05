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

#ifdef NET_IOCP
#include "netio/iocp/iohandler.h"
#include "netio/iocp/iohandlermanager.h"
#include "protocols/baseprotocol.h"

uint32_t IOHandler::_idGenerator = 0;

IOHandler::IOHandler(SOCKET_TYPE inboundFd, SOCKET_TYPE outboundFd, IOHandlerType type) {
	_pProtocol = NULL;
	_type = type;
	_id = ++_idGenerator;
	_inboundFd = inboundFd;
	_outboundFd = outboundFd;
	IOHandlerManager::RegisterIOHandler(this);
//	_pEvtLog = NULL;
}

IOHandler::~IOHandler() {
	if (_pProtocol != NULL) {
		_pProtocol->SetIOHandler(NULL);
		_pProtocol->EnqueueForDelete();
		_pProtocol = NULL;
	}
	IOHandlerManager::UnRegisterIOHandler(this);
}

uint32_t IOHandler::GetId() {
	return _id;
}

SOCKET_TYPE IOHandler::GetInboundFd() {
	return _inboundFd;
}

SOCKET_TYPE IOHandler::GetOutboundFd() {
	return _outboundFd;
}

IOHandlerType IOHandler::GetType() {
	return _type;
}

void IOHandler::SetProtocol(BaseProtocol *pPotocol) {
	_pProtocol = pPotocol;
}

BaseProtocol *IOHandler::GetProtocol() {
	return _pProtocol;
}

string IOHandler::IOHTToString(IOHandlerType type) {
	switch (type) {
		case IOHT_ACCEPTOR:
			return "IOHT_ACCEPTOR";
		case IOHT_TCP_CARRIER:
			return "IOHT_TCP_CARRIER";
		case IOHT_UDP_CARRIER:
			return "IOHT_UDP_CARRIER";
		case IOHT_TCP_CONNECTOR:
			return "IOHT_TCP_CONNECTOR";
		case IOHT_TIMER:
			return "IOHT_TIMER";
		case IOHT_INBOUNDNAMEDPIPE_CARRIER:
			return "IOHT_INBOUNDNAMEDPIPE_CARRIER";
		case IOHT_STDIO:
			return "IOHT_STDIO";
		default:
			return format("#unknown: %hhu#", type);
	}
}

//void IOHandler::SetEventLogger(EventLogger *pEvtLogger) {
//	_pEvtLog = pEvtLogger;
//}
#endif /* NET_IOCP */
