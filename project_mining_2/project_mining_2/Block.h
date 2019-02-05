#pragma once

#include <cstdint>
#include <iostream>
#include <list>
#include "transaction.h"
#include <vector>

using namespace std;
/*!
\brief ���� � �������

������ ���� � ������� ����� ���� ���������.
*/
class Block
{
public:	
	//! �����������
	Block(string previousHash);
	//! ����������� ��� ������� �����
	Block();
	//! �����������
	~Block();
	//! ��������� ���� (string)
	string calculateHash(); 
	//! ������ ��� ���� �����
	string GetHash();  
	//! ������ ��� ���� ����������� �����
	string GetpreviousHash();
	//! �������� ����� � ��������� ����������
	void MineBlock(int nDifficulty);
	//! ��������������� ������ ������ ��� ������ �����
	friend ostream& operator<<(ostream& stream, const Block& abook);
	//! ������� ������ ���� id ����������, �������� ����� ���
	string getMerkleRoot(vector<transaction> transactions);
	//! ���������� ���������� � ������ ���������� �����
	bool addTransaction(transaction transn);
	//! ������ �������
	vector<transaction> GetTransactions();
private:
	//! ��� ����� (string)
	string hash; 
	//! ��� ����������� ����� (string)
	string previousHash;  
	//! ��������� ������� ��� ���������� ������ � 01.01.1970. (time_t)
	string timeStamp; 
	//! ���-�� ������� ���������� ����, ����� ��� �����������
	int nonce;
	//! ��� ���� ���������� ����������
	string merkleRoot;
	//! ������ ���������� �����, �� ������ ������ ����� ���� ���������� � �����
	vector<transaction> transactions;
};

