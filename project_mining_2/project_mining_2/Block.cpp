#define  _CRT_SECURE_NO_WARNINGS


#include "Block.h"
#include "ctime"
#include "sha256.h"
#include "BlockChain.h"

// ����������� ��� ������
Block::Block(string PreviousHash)
{
	previousHash = PreviousHash;
	//timeStamp = new Date().getTime();
	time_t ts = time(&ts);// ������� ���� � 1.01.1900 � �������� (����� ��� � ������������� �� ������� ����)
	timeStamp = ctime(&ts);
	//hash = calculateHash();
	nonce = -1;
	MineBlock(BlockChain::difficulty);
	transactions = vector<transaction>();
}
// ����������� ������� �����
Block::Block()
{
	previousHash = "0";
	//timeStamp = new Date().getTime();
	time_t ts = time(&ts);// ������� ���� � 1.01.1900 � �������� (����� ��� � ������������� �� ������� ����)
	timeStamp = ctime(&ts);
	hash = "0";
	nonce = -1;
	transactions = vector<transaction>();
}
// ���������� �����
Block::~Block()
{
}
// ���������� ����� ��� �� ������ ����������� ������
string Block::calculateHash()
{
	SHA256 sha256;
	string calculatedhash = sha256(	previousHash + timeStamp + to_string(nonce) + merkleRoot);
	return calculatedhash;
}
// ������� �����. ����������� �������� nonce �� ���������� ���� hash.
void Block::MineBlock(int nDifficulty) {
	merkleRoot = getMerkleRoot(transactions);
	char *cstr = new char[nDifficulty + 1];
	for (int i = 0; i < nDifficulty; ++i) {
		cstr[i] = '0';
	}
	cstr[nDifficulty] = '\0';

	string str(cstr);

	do {
		nonce++;
		hash = calculateHash();
	} while (hash.substr(0, nDifficulty) != str);
	//cout << "Block mined: " << hash<< endl << "nonse: " << nonce << endl;
}
// ����������� ������ ���������� � ���������� ������ merkle.
string Block::getMerkleRoot(vector<transaction> transactions)
{
	SHA256 sha256;
	int count = transactions.size();
	vector<string> previousTreeLayer = vector<string>();
	for (transaction tr : transactions) {
		previousTreeLayer.push_back(tr.transactionIdGet());
	}	
	vector<string> treeLayer = previousTreeLayer;
	while (count > 1) {
		treeLayer = vector<string>();
		for (int i = 1; i < previousTreeLayer.size(); i++) {
			treeLayer.push_back(sha256(previousTreeLayer[i - 1]) + previousTreeLayer[i]);
		}
		count = treeLayer.size();
		previousTreeLayer = treeLayer;
	}
	string merkleRoot = (transactions.size() == 1) ? treeLayer.at(0) : "";
	return merkleRoot;
}
// ���������� ���������� � ���� ����
bool Block::addTransaction(transaction transn)
{
	// ������������ ���������� � ���������, ������������� ��, ���� ���� �� �������� 
	//������ ��������, � ����� ����������.
	if (transn.sender == "0" && transn.reciepient == "0") return false; //��� �� ������ ����������
	if ((previousHash != "0")) {
		if ((transn.processTransaction() != true)) {
			cout << endl << "���������� �� ����������. �����������." << endl;
			return false;
		}
	}
	transactions.push_back(transn);
	cout << "������� ��������� ���������� � ����" << endl;
	return true;
}
vector<transaction> Block::GetTransactions()
{
	return transactions;
}
// ���������� ��� �����
string Block::GetHash() {
	//cout << hash;
	return hash;
}
// ���������� ��� ����������� �����
string Block::GetpreviousHash()
{
	return previousHash;
}
// ��������������� ������ ��� ����� �����
ostream & operator<<(ostream & stream, const Block & abook)
{
	stream << "\t���: " << abook.hash << endl;
	stream << "\t���������� ���: " << abook.previousHash << endl;
	//stream << "\tdata: " << abook.transactions << endl;
	for (int i = 0; i < abook.transactions.size(); i++)
		cout << "\t����������:"<< abook.transactions[i];
	stream << "\t�����: " << abook.timeStamp ;
	stream << "\t�������: " << abook.nonce << endl;
	stream << "======" << endl;
	return stream;
}
