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
\brief ���������

������ ���������� ����� �������� �������� ����� ������
*/
class transaction
{
	// OPENSSL
	// sender � reciepient ���� ����� ��� ��� �� � ������� ����� �����������
	// �������� �������� ����������� ���, �� ��� ���������������
	// ���� ������� generateSignature �  verifiySignature ������� ���� ������
	// �� ������ ������, ���� �������: https://stackoverflow.com/questions/36695994/verify-signature-in-c-using-openssl
private:
	//! ��� ����������.
	string transactionId; 	 
	//!�������, ����� ���-���� ��� �� ������ �������� � ��������.
	string signature;
	//! ������ ������� ���������� ����������.
	int sequence = 0;
		
public://! ����� ����������
	vector <TransactionInput> inputs; 
	//! ������ ����������
	vector <TransactionOutput> outputs;
	//! ����� ���������� / �������� ����.
	string reciepient;
	//! ���-�� ������������ �����
	double value;
	//!����� ����������� / �������� ����.
	string sender; 

	//! �����������
	transaction(string from, string to, double value, vector<TransactionInput> inputs);
	//! ����������� ��� ������� ��-�
	transaction(string from, string to, double value); 
	//! �����������
	transaction();
	//! ����������
	~transaction();
	//! �������� �������
	void generateSignature(string privateKey); 
	//! �������� �������. ���� ������ ��������� ����
	bool verifiySignature(string privateKey);
	//!  ���������� true, ���� ����� ���������� ����� ���� �������, ����� �������� ������
	bool processTransaction();
	//! ���������� ����� �������� ������ (UTXO)
	double getInputsValue(); 
	//! ���������� ����� �������:
	double getOutputsValue(); 
	//! ���������� ID ����������
	string transactionIdGet(); 
	//! ���� ���� ����������
	string calulateHash();
	//! ����� ��������� �����
	friend ostream& operator<<(ostream& stream, const transaction& abook);
};

