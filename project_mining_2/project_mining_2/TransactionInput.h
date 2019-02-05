#pragma once
#include <cstdint>
#include <iostream>
#include "TransactionOutput.h"

using namespace std;
/*!
\brief ���� ����������

����� ����������, ������ ������ ������ ���� � ������ ����������
*/
class TransactionInput
{
public:
	//! ������ �� TransactionOutputs -> transactionId
	string transactionOutputId;  
	//! �������� ����� ���������� 
	TransactionOutput  UTXO;

	//! �����������
	TransactionInput(string  transactionOutputId, TransactionOutput  utxo);
	//! ����������
	~TransactionInput();
};

