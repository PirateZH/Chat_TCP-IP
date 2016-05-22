// socketclient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;


//#define IP_ADDRESS "192.168.3.183"
#define IP_ADDRESS "192.168.2.6"
#define PORT 4000

void client_test()
{
	WSADATA ws;
	SOCKET ClientSocket;
	sockaddr_in ServerAddr;

	if(WSAStartup(MAKEWORD(2, 2), &ws) != 0)
	{
		cout<< " Init failed"<<endl;
		return;
	}

	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(ClientSocket == INVALID_SOCKET)
	{
		cout<<" create socket failed"<<endl;
		return;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	ServerAddr.sin_port = PORT;
	memset(ServerAddr.sin_zero, 0x00, 8);

	int ret = connect(ClientSocket, (sockaddr*)&ServerAddr, sizeof(ServerAddr));

	if(ret != 0)
	{
		cout << " connect failed : "<<GetLastError()<<endl;
		return;
	}

	cout<<" connect sucessfully"<<endl;

	/*char revbuffer[MAX_PATH];
	memset(revbuffer, 0, sizeof(revbuffer));
	ret = recv(ClientSocket, revbuffer, sizeof(revbuffer), 0);
	if(ret == 0 )
		cout<<"recv failed "<<endl;
	else
		cout<<revbuffer<<endl;*/

	const char *sendbuffer;
	char data[5];
	data[0] = 'A';
	data[1] = '\r';
	data[2] = '\n';
	data[3] = 'b';
	data[4] = '\0';
	
	sendbuffer = data;
	cout<<sendbuffer<<endl;

	/*string s ="client0";
	sendbuffer = s.c_str();*/

	while(true)
	{
		//cin.getline(sendbuffer, sizeof(sendbuffer));
		ret = send(ClientSocket, sendbuffer, strlen(sendbuffer), 0);
		if(ret == 0 )
		{
			cout<<"send failed "<<endl;

		}
		Sleep(500);
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	client_test();
	return 0;
}

