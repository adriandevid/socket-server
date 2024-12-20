#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <WinSock2.h>
#include <windows.h>
#include <WS2tcpip.h>

/// <summary>
/// 
/// </summary>
/// <param name="v">vetor</param>
/// <param name="l">inicio</param>
/// <param name="r">fim</param>
/// <param name="t">valor para pesquisa</param>
/// <returns>indice</returns>
// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int main(void) {
	WSADATA socket_data;

	int socket_startup = WSAStartup(MAKEWORD(2, 2), &socket_data);

	SOCKET socket_instance = socket(AF_INET, SOCK_STREAM, NULL);

	sockaddr_in socket_address;
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(8080);
	
	int inet_parse = inet_pton(AF_INET, "127.0.0.1", &socket_address.sin_addr);

	if (inet_parse == SOCKET_ERROR) {
		wprintf(L"bind failed with error: %ld\n", WSAGetLastError());
		closesocket(socket_instance);
		WSACleanup();
		return 1;

	}
	int socket_bind_address = bind(socket_instance, (SOCKADDR*)&socket_address, sizeof(socket_address));

	if (socket_bind_address == SOCKET_ERROR) {
		wprintf(L"bind failed with error: %ld\n", WSAGetLastError());
		closesocket(socket_instance);
		WSACleanup();
		return 1;
	}

	int socket_listen = listen(socket_instance, 1);

	if (socket_bind_address == SOCKET_ERROR) {
		wprintf(L"bind failed with error: %ld\n", WSAGetLastError());
		closesocket(socket_instance);
		WSACleanup();
		return 1;
	}
	
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	while (true) {
		SOCKET AcceptSocket = accept(socket_instance, NULL, NULL);
		int recv_socket_message = recv(AcceptSocket, recvbuf, recvbuflen, 0);

		//iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (AcceptSocket > 0)
			printf("Bytes received: %s\n", recvbuf);
		else if (AcceptSocket == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: ");

		if (AcceptSocket > 0)
			return 1;
	}

	closesocket(socket_instance);
	WSACleanup();

	return 0;
}