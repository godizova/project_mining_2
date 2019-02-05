#include "TransactionOutput.h"
#include "sha256.h"


TransactionOutput::TransactionOutput(string rec, double val, string parTransId)
{
	reciepient = rec;
	value = val;
	parentTransactionId = parTransId;
	SHA256 sha256;
	id = sha256(reciepient + to_string(value) + parentTransactionId);
}

TransactionOutput::TransactionOutput()
{
}

//
//TransactionOutput::TransactionOutput()
//{
//	reciepient = '0';
//	value = 0;
//	parentTransactionId = '0';
//	SHA256 sha256;
//	id = sha256(reciepient + to_string(value) + parentTransactionId);
//}


TransactionOutput::~TransactionOutput()
{
	
}

bool TransactionOutput::isMine(string publicKey)
{
	return (publicKey == reciepient);;
}

void TransactionOutput::copyTransactionOutput(TransactionOutput TrO)
{
	reciepient = TrO.reciepient;
	value = TrO.value;
	parentTransactionId = TrO.parentTransactionId;
	SHA256 sha256;
	id = sha256(reciepient + to_string(value) + parentTransactionId);
}

