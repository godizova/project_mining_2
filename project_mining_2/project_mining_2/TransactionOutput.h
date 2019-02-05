#pragma once
#include <cstdint>
#include <iostream>

using namespace std;
/*!
\brief выход транзакции

выходы транзакций, данный объект класса есть в каждой транзакции
*/
class TransactionOutput
{
public:
	//! уникальный идентификатор каждоо выхода
	string id;
	//! новый владелец этих монет.
	string reciepient;
	//! количество монет
	double value;
	//! идентификатор транзакции
	string parentTransactionId; 
	//! конструктор
	TransactionOutput(string reciepient, double value, string parentTransactionId);
	//! конструктор
	TransactionOutput();
	//! деструктор
	~TransactionOutput();
	//! принадлежит ли выход транзакции
	bool isMine(string publicKey);
	//! копирование
	void copyTransactionOutput(TransactionOutput TrO);
};

