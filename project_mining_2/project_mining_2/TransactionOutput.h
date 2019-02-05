#pragma once
#include <cstdint>
#include <iostream>

using namespace std;
/*!
\brief ����� ����������

������ ����������, ������ ������ ������ ���� � ������ ����������
*/
class TransactionOutput
{
public:
	//! ���������� ������������� ������ ������
	string id;
	//! ����� �������� ���� �����.
	string reciepient;
	//! ���������� �����
	double value;
	//! ������������� ����������
	string parentTransactionId; 
	//! �����������
	TransactionOutput(string reciepient, double value, string parentTransactionId);
	//! �����������
	TransactionOutput();
	//! ����������
	~TransactionOutput();
	//! ����������� �� ����� ����������
	bool isMine(string publicKey);
	//! �����������
	void copyTransactionOutput(TransactionOutput TrO);
};

