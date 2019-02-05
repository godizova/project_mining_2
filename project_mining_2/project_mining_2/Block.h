#pragma once

#include <cstdint>
#include <iostream>
#include <list>
#include "transaction.h"
#include <vector>

using namespace std;
/*!
\brief блок в цепочке

Каждый блок в цепочке будет этим элементом.
*/
class Block
{
public:	
	//! конструктор
	Block(string previousHash);
	//! конструктор для генезис блока
	Block();
	//! десктруктор
	~Block();
	//! генерация хеша (string)
	string calculateHash(); 
	//! геттер для хеша блока
	string GetHash();  
	//! геттер для хеша предыдущего блока
	string GetpreviousHash();
	//! смайнинг блока с указанной сложностью
	void MineBlock(int nDifficulty);
	//! Переопределение потока вывода для каждоо блока
	friend ostream& operator<<(ostream& stream, const Block& abook);
	//! считает корень всех id транзакций, создавая общий хеш
	string getMerkleRoot(vector<transaction> transactions);
	//! содавление транзакции к вектор транзакций блока
	bool addTransaction(transaction transn);
	//! геттер вектора
	vector<transaction> GetTransactions();
private:
	//! хеш блока (string)
	string hash; 
	//! хеш предыдущего блока (string)
	string previousHash;  
	//! временной отрезок как количество секунд с 01.01.1970. (time_t)
	string timeStamp; 
	//! кол-во попыток вычисления хеша, нужно для хеширования
	int nonce;
	//! хеш всех предыдущих транзакций
	string merkleRoot;
	//! вектор транзакций блока, на данный момент толко одна транзакция в блоке
	vector<transaction> transactions;
};

