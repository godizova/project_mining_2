#pragma once
#include <vector>
#include "block.h"
#include <map> 
//#include "TransactionOutput.h"

// ��� ����� ���������. 
/*!
\brief ��� ����� ���������

�������� �������� ������� ���������, �������� � ���� ��� ������� ������ � �������������� �� �������.
*/
class BlockChain
{
public:
	//! ��������� �������� ����� (���-�� ����� � ������)
	static int difficulty ;
	//! ����������� ����� ��� �������� ����������
	static double minimumTransaction ;
	//! ������ ���� ����������������� ����������.
	static map <string, TransactionOutput> UTXOs;
	//! ������� ���������� ������� ��������
	static transaction genesisTransaction;
	//! �����������
	BlockChain();
	//! ����������
	~BlockChain();	
	//! ���������� ������ ����� � �������
	void AddBlock(Block bNew);
	//! ���������� ���������� ����, ����� ��� �������� ���� ����������
	Block GetLastBlock() const;
	//!�������� ������ �� ������������, ��������� ����� ������, ����� ����� ������ �� ������
	bool isChainValid();
	//! ����� ���� ������� ������
	void display();
	//! ����������� ������� ������
	vector<Block> GetvChain();
private:
	//! �������� ������� ������
	static vector<Block> vChain; 
	

};

