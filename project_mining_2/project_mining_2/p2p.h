#pragma once
// ������ �������� TCP����������
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <locale.h>
#include <stdio.h>
#include <winsock2.h> // Wincosk2.h ������ ���� ������ windows!
#pragma comment(lib, "Ws2_32.lib")
#define MY_PORT 666 // ����, ������� ������� ������
// ������ ��� ������ ���������� �������� �������������
#define PRINTNUSERS if (p2p::nclients) printf("%d user online\n",p2p::nclients);else printf("No User on line\n");
// �������� �������, ������������� �������������� �������������
DWORD WINAPI SexToClient(LPVOID client_socket);
// ���������� ���������� � ���������� �������� �������������
/*!
\brief ������������ ����

����� ��� ���������������������� ����
*/
class p2p
{
private:
public:
	p2p();
	~p2p();
	int net();
	static int nclients;
};

