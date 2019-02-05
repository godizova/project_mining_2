#pragma once
#include <vector>
#include "block.h"
#include <map> 
//#include "TransactionOutput.h"

// сам класс блокчейна. 
/*!
\brief сам класс блокчейна

явл€етс€ основным классом блокчейна, содержит в себе всю цепочку блоков и поддерживаемые ее функции.
*/
class BlockChain
{
public:
	//! сложность майнинга блока (кол-во нулей в начале)
	static int difficulty ;
	//! минимальна€ сумма дл€ передачи транзакции
	static double minimumTransaction ;
	//! список всех неизрасходованных транзакций.
	static map <string, TransactionOutput> UTXOs;
	//! нулева€ транзакци€ первому кошельку
	static transaction genesisTransaction;
	//! конструктор
	BlockChain();
	//! деструктор
	~BlockChain();	
	//! добавление нового блока в цепочку
	void AddBlock(Block bNew);
	//! возвращаем предыдущий блок, нужно дл€ создани€ хеша следующего
	Block GetLastBlock() const;
	//!проверка блоков на правильность, сравнение хешей блоков, чтобы никто ничего не вписал
	bool isChainValid();
	//! вывод всей цепочки блоков
	void display();
	//! возвращение цепочки блоков
	vector<Block> GetvChain();
private:
	//! хранима€ цепочка блоков
	static vector<Block> vChain; 
	

};

