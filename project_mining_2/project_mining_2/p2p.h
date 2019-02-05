#pragma once
// Пример простого TCPэхосервера
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <locale.h>
#include <stdio.h>
#include <winsock2.h> // Wincosk2.h должен быть раньше windows!
#pragma comment(lib, "Ws2_32.lib")
#define MY_PORT 666 // Порт, который слушает сервер
// макрос для печати количества активных пользователей
#define PRINTNUSERS if (p2p::nclients) printf("%d user online\n",p2p::nclients);else printf("No User on line\n");
// прототип функции, обслуживающий подключившихся пользователей
DWORD WINAPI SexToClient(LPVOID client_socket);
// глобальная переменная – количество активных пользователей
/*!
\brief одноранговая сеть

класс для реализацииодноранговой сети
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

