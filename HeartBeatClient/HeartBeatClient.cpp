#include "stdafx.h"
#include "stdio.h"
#include "winsock2.h" 
#include "ws2tcpip.h" 
#include "mswsock.h"
#pragma comment(lib,"ws2_32.lib") 


DWORD WINAPI workThread(LPVOID lpParam);

int main()
{
	CreateThread(0, 0, workThread, NULL, 0, NULL);

	//���߳�����������exit�˳�
	bool run = true;
	while (run)
	{
		char st[40];
		gets_s(st);

		if (!strcmp("exit", st))
		{
			run = false;
		}
	}
	WSACleanup();

	return 0;
}

DWORD WINAPI workThread(LPVOID lpParam)
{
	SOCKET sock;
	sockaddr_in ServerAddress;
	WSADATA wsdata;
	bool bsocket;
	
	WSAStartup(0x0202, &wsdata);

	sock = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	bsocket = true;
	//Ȼ��ֵ����ַ�������������ϵĹ㲥��ַ������Ϣ��  
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = INADDR_BROADCAST;
	ServerAddress.sin_port = htons(9000);
	bool opt = true;
	//���ø��׽���Ϊ�㲥���ͣ�  
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char FAR *)&opt, sizeof(opt));
	int nlen = sizeof(ServerAddress);
	while (true)
	{
		Sleep(1000);
		//�ӹ㲥��ַ������Ϣ  
		char *smsg = "�һ�����";
		int ret = sendto(sock, smsg, 256, 0, (sockaddr*)&ServerAddress, nlen);
		if (ret == SOCKET_ERROR)
		{
			printf("%d \n", WSAGetLastError());
		}
		else
		{
			printf("��������.\n");
		}
	}
	printf_s("�߳��˳�.\n");
	return 0;
}