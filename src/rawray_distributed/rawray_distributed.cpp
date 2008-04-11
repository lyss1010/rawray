/////////////////////////////////////////////////////////////////////////////
// Console Entry Point : rawray_distributed.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "rawray_distributed.h"
#include "rawray/glut_window.h"
#include "rawray/options.h"
#include "distributed_node.h"

// Global vars
DistributedNode* g_distributedNode = NULL;


// Exit point
void exit_cleanup(void) {
	delete g_distributedNode;
    _CrtDumpMemoryLeaks();
}

// Console Entry point
int _tmain( int argc, _TCHAR* argv[] )
{
	// Enable memory leak messages on exit
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF );
	//_CrtSetBreakAlloc( 438 );

    // Initialize options defaults
    rawray::options::init();

    // Open GLUT window and begin rendering
	atexit( exit_cleanup );

	char c = 0;
	while( c != 's' && c != 'S' && c != 'c' && c != 'C' ) {
		std::cout << "Do you wish to run a (S)erver or (C)lient? " << std::flush;
		std::cin >> c;
		std::cout << std::endl;
	}

	switch( c ) {
		case 'c':
		case 'C':
			g_distributedNode = new DistributedNode(false);
			break;

		case 's':
		case 'S':
			g_distributedNode = new DistributedNode(true);
			break;
	}

	g_distributedNode->Run();
	while( true ) {
		std::cout << ".";
		Sleep( 1000 );
	}

	return 0;
}


// Client loop
bool ConnectToServer(uint16 port) {
    return false;
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


// Server loop
bool ListenForTasks(uint16 port, int numSockets) {
    return false;
//    int err;
//	WORD sockVersion = MAKEWORD(1, 1); // WinSock 1.1
//
//	// Initialize WinSock
//	WSADATA wsaData;
//	WSAStartup(sockVersion, &wsaData);
//
//	// Create listening socket
//	SOCKET listeningSocket;
//	listeningSocket = socket(AF_INET,		// Go over TCP/IP
//                            SOCK_STREAM,   	// This is a stream-oriented socket
//				            IPPROTO_TCP);	// Use TCP rather than UDP
//
//	if (listeningSocket == INVALID_SOCKET) {
//		err = WSAGetLastError();
//        std::cout << "Winsock error listeningsocket: " << err << std::endl;
//
//		WSACleanup();				        // Shutdown Winsock
//        return NETWORK_ERROR;
//    }
//
//	SOCKADDR_IN serverInfo;
//	serverInfo.sin_family = AF_INET;
//	serverInfo.sin_addr.s_addr = INADDR_ANY;
//	serverInfo.sin_port = htons(port);
//
//	// Bind the socket to our local server address
//	err = bind(listeningSocket, (LPSOCKADDR)&serverInfo, sizeof(sockaddr));
//	if (err == SOCKET_ERROR) {
//		err = WSAGetLastError();
//        std::cout << "Winsock error bind: " << err << std::endl;
//        
//		WSACleanup();
//		return NETWORK_ERROR;
//	}
//
//	// Make the socket listen
//	err = listen(listeningSocket, numSockets);
//	if (err == SOCKET_ERROR) {
//		err = WSAGetLastError();
//		std::cout << "Winsock error listen: " << err << std::endl;
//
//		WSACleanup();
//		return NETWORK_ERROR;
//	}
//
//	// Wait for a client
//	SOCKET theClient;
//	theClient = accept(listeningSocket,
//			   NULL,			// Optionally, address of a SOCKADDR_IN struct
//			   NULL);			// Optionally, address of variable containing
//							    // sizeof ( struct SOCKADDR_IN )
//
//	if (theClient == INVALID_SOCKET) {
//		err = WSAGetLastError();
//		std::cout << "Winsock error accept: " << err << std::endl;
//
//		WSACleanup();
//		return NETWORK_ERROR;
//	}
//
//	// Send and receive from the client, and finally,
//	closesocket(theClient);
//	closesocket(listeningSocket);
//
//	// Shutdown Winsock
//	WSACleanup();
//	return NETWORK_OK;
}