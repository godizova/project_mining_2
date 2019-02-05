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
//! ������� ������� ������������
/*!
\brief �������

������� ������� ������������
*/
class wallet
{
private:
	//! ������ ���� ������������
	string privateKey;
	//! ��������� ����
	string publicKey;
	//! ��������� �����
	string generateKeyPair();
public:
	//! �����������
	wallet();
	//! �����������
	~wallet();
	//! ������ ���������� �����
	string getPrivateKey();
	//! ������ ��������� �����
	string getPublicKey();
	//! ���������� ������ � ��������� UTXO, ������������� ����� ��������, � ����.
	double getBalance();
	//! ������� � ���������� ����� ���������� �� ����� ��������.
	transaction sendFunds(string _recipient, double value);

	//! ������ UTXO (<string, TransactionOutput>), ������������� ����� ��������.
	map <string, TransactionOutput> UTXOs = map <string, TransactionOutput>();
};

