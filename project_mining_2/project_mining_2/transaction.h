#pragma once
#include <cstdint>
#include <iostream>
#include <openssl\rsa.h>
#include <openssl\evp.h>
#include <map> 
#include <vector> 
#include "TransactionInput.h"
#include "TransactionOutput.h"
#include "sha256.h"

using namespace std;
/*!
\brief транзкция

каждая транзакция будет являться объектом этого класса
*/
class transaction
{
	// OPENSSL
	// sender И reciepient ЕСТЬ КЛЮЧИ ТАК ЧТО ИХ И СОЗДАТЬ ПОСЛЕ ПОДКЛЮЧЕНИЯ
	// изменить придется практически все, де они взаимодействуют
	// зато фметоды generateSignature и  verifiySignature теперть лече решить
	// на всякий случай, если потеряю: https://stackoverflow.com/questions/36695994/verify-signature-in-c-using-openssl
private:
	//! хэш транзакции.
	string transactionId; 	 
	//!подпись, чтобы кто-либо еще не тратил средства в кошельке.
	string signature;
	//! грубый подсчет количества транзакций.
	int sequence = 0;
		
public://! входы транзакций
	vector <TransactionInput> inputs; 
	//! выходы транзакций
	vector <TransactionOutput> outputs;
	//! Адрес получателя / открытый ключ.
	string reciepient;
	//! кол-во передаваемых валют
	double value;
	//!адрес отправителя / открытый ключ.
	string sender; 

	//! конструктор
	transaction(string from, string to, double value, vector<TransactionInput> inputs);
	//! конструктор для генезис тр-и
	transaction(string from, string to, double value); 
	//! конструктор
	transaction();
	//! деструктор
	~transaction();
	//! создание подписи
	void generateSignature(string privateKey); 
	//! проверка подписи. Надо убрать приватный ключ
	bool verifiySignature(string privateKey);
	//!  Возвращает true, если новая транзакция может быть создана, много проверок внутри
	bool processTransaction();
	//! возвращает сумму значений входов (UTXO)
	double getInputsValue(); 
	//! возвращает сумму выходов:
	double getOutputsValue(); 
	//! возвращает ID транзакции
	string transactionIdGet(); 
	//! счет хеша транзакции
	string calulateHash();
	//! вывод некоторых полей
	friend ostream& operator<<(ostream& stream, const transaction& abook);
};

