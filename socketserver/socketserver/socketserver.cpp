// socketserver.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//#include "commomdefs.h"
//#include "test.h"
#include <iostream>

#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")

//#define IP_ADDRESS "192.168.3.183"
#define IP_ADDRESS "192.168.2.6"
#define PORT 4000
#include <string>
using namespace std;

DWORD WINAPI ClientThread(LPVOID lpParamter)
{
	SOCKET CientSocket = (SOCKET)lpParamter;
	int ret = 0;
	char recvBuffer[MAX_PATH];

	while(true)
	{
		memset(recvBuffer, 0, sizeof(recvBuffer));
		ret = recv(CientSocket, recvBuffer, MAX_PATH, 0);
		if(ret == 0 || ret == SOCKET_ERROR)
		{
			cout<<" receive error"<<endl;

			closesocket(CientSocket);
			break;

		}

		cout<< " receive data : "<<recvBuffer<<endl;
	}

	return ret;

}



/*extern "C" CS_API void __cdecl*/ void socket_test()
{
	WSADATA ws;
	SOCKET ServerSocket, CientSocket;
	sockaddr_in localAddr, clientAddr;
	int ret = 0;
	int addrLen = 0;
	HANDLE hThread = NULL;

	if(WSAStartup(MAKEWORD(2, 2), &ws) != 0)
	{
		cout<<" Init failed "<<endl;
		return ;
	}

	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(ServerSocket == INVALID_SOCKET)
	{
		cout << " create socket failed "<<endl;
		return;
	}

	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	localAddr.sin_port = PORT;//随机端口
	memset(localAddr.sin_zero, 0x00, 8);


	//bind socket;
	ret = bind(ServerSocket, (sockaddr*)&localAddr, sizeof(localAddr));

	if(ret != 0)
	{
		cout<<"bind error ,last error: "<<GetLastError()<<endl;
		return ;
	}

	ret = listen(ServerSocket, 10);
	if(ret != 0)
	{
		cout<<"listen error "<<endl;
		return ;
	}


	cout<< " server has started... "<<endl;
	while(true)
	{
		addrLen = sizeof(clientAddr);
		CientSocket = accept(ServerSocket, (sockaddr*)&clientAddr, &addrLen);
		if(CientSocket == INVALID_SOCKET)
		{
			cout<<" accept failed, last error:  "<<GetLastError()<<endl;
			break;
		}

		cout<<" cient connect : "<<inet_ntoa(clientAddr.sin_addr)<<":"<<clientAddr.sin_port<<endl;

		/*char sendbuffer[100] = "server connect";
		ret = send(CientSocket, sendbuffer, sizeof(sendbuffer), 0);*/


		hThread = CreateThread(NULL, 0, ClientThread, (LPVOID)CientSocket, 0, NULL);

		if(hThread == NULL)
		{
			cout<< " create thread failed"<<endl;
			break;
		}
		CloseHandle(hThread);
	}

	closesocket(ServerSocket);
	//closesocket(CientSocket);
	WSACleanup();
	return;

}
int _tmain(int argc, _TCHAR* argv[])
{
	string s;
	s.c_str();
	socket_test();
	return 0;
}

