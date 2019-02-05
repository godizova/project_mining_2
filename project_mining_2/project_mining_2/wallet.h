#pragma once

#include <cstdint>
#include <iostream>
#include <openssl\rsa.h>
#include <openssl\bio.h>
#include <map>
#include <list>
#include "TransactionOutput.h"
#include "TransactionOutput.h"
#include "transaction.h"


using namespace std;
//! кошелек каждого пользователя
/*!
\brief кошелек

кошелек каждого пользователя
*/
class wallet
{
private:
	//! личный ключ пользователя
	string privateKey;
	//! публичный ключ
	string publicKey;
	//! генерация ключа
	string generateKeyPair();
public:
	//! конструктор
	wallet();
	//! десткруктор
	~wallet();
	//! геттер приватного ключа
	string getPrivateKey();
	//! геттер публичноо ключа
	string getPublicKey();
	//! возвращает баланс и сохраняет UTXO, принадлежащий этому кошельку, в этом.
	double getBalance();
	//! Создает и возвращает новую транзакцию из этого кошелька.
	transaction sendFunds(string _recipient, double value);

	//! только UTXO (<string, TransactionOutput>), принадлежащие этому кошельку.
	map <string, TransactionOutput> UTXOs = map <string, TransactionOutput>();
};

