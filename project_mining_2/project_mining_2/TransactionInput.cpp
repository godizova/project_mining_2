#include "TransactionInput.h"

#include <cstdint>
#include <iostream>


TransactionInput::TransactionInput(string  tranOutputId, TransactionOutput  utxo)
{
	transactionOutputId = tranOutputId;
	UTXO = TransactionOutput(utxo.reciepient, utxo.value, utxo.parentTransactionId);
}


TransactionInput::~TransactionInput()
{
}
