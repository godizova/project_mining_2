#pragma once
#include <cstdint>
#include <iostream>
#include "TransactionOutput.h"

using namespace std;
/*!
\brief вход транзакции

входы транзакций, данный объект класса есть в каждой транзакции
*/
class TransactionInput
{
public:
	//! —сылка на TransactionOutputs -> transactionId
	string transactionOutputId;  
	//! —одержит выход транзакции 
	TransactionOutput  UTXO;

	//! конструктор
	TransactionInput(string  transactionOutputId, TransactionOutput  utxo);
	//! деструктор
	~TransactionInput();
};

