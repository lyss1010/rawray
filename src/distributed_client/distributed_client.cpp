/////////////////////////////////////////////////////////////////////////////
// Console Entry Point : distributed_client.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "distributed_client.h"
#include "rawray/options.h"

// Exit point
void exit_cleanup(void) {
    _CrtDumpMemoryLeaks();
}


// Client loop
int ConnectToServer(uint16 port) {
    return NETWORK_ERROR;
//	int err;
//	WORD sockVersion = MAKEWORD(1, 1);
//
//	// Initialize Winsock as before
//	WSADATA wsaData;
//	WSAStartup(sockVersion, &wsaData);
//
//	// Store information about the server
//	LPHOSTENT hostEntry;
//    in_addr iaHost;
//
//    iaHost.s_addr = inet_addr("127.0.0.1");
//    hostEntry = gethostbyaddr((const char *)&iaHost, sizeof(in_addr), AF_INET);
//	if (!hostEntry) {
//		err = WSAGetLastError();
//        std::cout << "Winsock error gethostbyaddr: " << err << std::endl;
//
//		WSACleanup();
//		return NETWORK_ERROR;
//	}
//
//	// Create the socket
//	SOCKET theSocket;
//	theSocket = socket(AF_INET,			// Go over TCP/IP
//			            SOCK_STREAM,	// This is a stream-oriented socket
//			            IPPROTO_TCP);	// Use TCP rather than UDP
//
//	if (theSocket == INVALID_SOCKET) {
//		err = WSAGetLastError();
//        std::cout << "Winsock error socket: " << err << std::endl;
//
//		WSACleanup();
//		return NETWORK_ERROR;
//	}
//
//	// Fill a SOCKADDR_IN struct with address information
//	SOCKADDR_IN serverInfo;
//	serverInfo.sin_family = AF_INET;
//	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
//	serverInfo.sin_port = htons(port);
//
//	// Connect to the server
//	err = connect(theSocket, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr));
//	if (err == SOCKET_ERROR) {
//		err = WSAGetLastError();
//        std::cout << "Winsock error connect: " << err << std::endl;
//
//		WSACleanup();
//		return NETWORK_ERROR;
//	}
//
//	// Send/receive, then cleanup:
//	closesocket(theSocket);
//
//	WSACleanup();
//    return NETWORK_OK;
}


// Console Entry point
int _tmain( int argc, _TCHAR* argv[] )
{
	// Enable memory leak messages on exit
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF );
	//_CrtSetBreakAlloc( 438 );

    std::cout << "Distributed Client..." << std::endl;

    int err = ConnectToServer( 42000 );
    if( err == NETWORK_OK ) {
        std::cout << "OK :)" << std::endl;
    } else {
        std::cout << "FAILED :(" << std::endl;
    }

	return 0;
}
