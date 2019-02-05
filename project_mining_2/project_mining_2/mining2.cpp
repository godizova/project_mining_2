// mining2.cpp: определяет точку входа для консольного приложения.
//

#include "Block.h"
#include <iostream>
#include <Windows.h>
#include "BlockChain.h"
#include "wallet.h"
#include "transaction.h"
#include <string>
#include "TransactionOutput.h"
#include <locale.h>

using namespace std;

int BlockChain::difficulty = 2;// сложность майнига хэша
double BlockChain::minimumTransaction = 0.1; // минимальный размер передаваемых данных
map <string, TransactionOutput> BlockChain::UTXOs = map <string, TransactionOutput>();// выходы транзакций
transaction BlockChain::genesisTransaction = transaction();// нулевая транзакция
vector<Block> BlockChain::vChain;// вектор блоков (сама цепочка)

int main()
{
	setlocale(LC_ALL, "Rus");

	system("color F0");
	system("MODE CON: COLS=100 LINES=50");
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwSize.Y = 10000;//10000 строк
	SetConsoleScreenBufferSize(hConsole, csbi.dwSize);

	//----------------------------------------------------------------------------------------
	
	
	
	//-----
	BlockChain bChain = BlockChain();// класс блокчейна


	// Создание кошельков:
	wallet walletA = wallet();
	wallet walletB = wallet();
	wallet coinbase = wallet();
	//Test public and private keys
	cout << "Публичный ключ WalletA: " << walletA.getPublicKey() << endl
		<< "Приватный ключ WalletA: " << walletA.getPrivateKey() << endl;

	////Create a test transaction from WalletA to walletB 
	//transaction transaction1 =  transaction(walletA.getPublicKey(), walletB.getPublicKey(), 5);
	//transaction1.generateSignature(walletA.getPrivateKey());
	////Verify the signature works and verify it from the public key
	//cout << "Is signature verified: ";
	//cout << transaction1.verifiySignature(walletA.getPrivateKey()) <<  endl;

	// создаем транзакцию генезиса, которая отправляет 100 NoobCoin в walletA :
	bChain.genesisTransaction = transaction(coinbase.getPublicKey(), walletA.getPublicKey(), 100);
	bChain.genesisTransaction.generateSignature(coinbase.getPrivateKey());	 // вручную подписываем транзакцию генезиса	
	bChain.genesisTransaction.transactionIdGet() = "0"; //вручную установить идентификатор транзакции
	bChain.genesisTransaction.outputs.push_back(TransactionOutput(bChain.genesisTransaction.reciepient, bChain.genesisTransaction.value, bChain.genesisTransaction.transactionIdGet())); // вручную добавьте вывод транзакций
	bChain.UTXOs.insert(pair<string, TransactionOutput>(bChain.genesisTransaction.outputs.at(0).id, bChain.genesisTransaction.outputs.at(0))); //важно сохранить первую транзакцию в списке UTXOs.


	cout << endl <<" Создание и генерация блока генезиса ...  " << endl;
	Block genesis = Block("0");
	genesis.addTransaction(bChain.genesisTransaction);
	bChain.AddBlock(genesis);
	

	//getchar();
	bool tesst = false;
	// тестирование
	cout << endl << " Создание и генерация блока...  " << endl;
	Block block1 = Block(genesis.GetHash());
	cout << "\nБаланс WalletA: " << walletA.getBalance() << endl;
	cout << "\nWalletA пытается отправить средства (40) WalletB ..." << endl;
	tesst = block1.addTransaction(walletA.sendFunds(walletB.getPublicKey(), 40.0));
	if (tesst)
		bChain.AddBlock(block1);
	cout << "\nБаланс WalletA: " << walletA.getBalance() << endl;
	cout << "Баланс WalletB: " << walletB.getBalance() << endl;


	cout << endl << " Создание и генерация блока...  " << endl;
	Block block2 =  Block(block1.GetHash());
	cout << "\nWalletA пытается отправить средств больше (1000), чем у него есть ..." << endl;
	tesst = block2.addTransaction(walletA.sendFunds(walletB.getPublicKey(), 1000.0));
	if (tesst)
		bChain.AddBlock(block2);
	cout << "\nБаланс WalletA: " << walletA.getBalance() << endl;
	cout << "Баланс WalletB: " << walletB.getBalance() << endl;

	

	//getchar();
	cout << endl << " Создание и генерация блока...  " << endl;
	Block block3 =  Block(bChain.GetvChain().back().GetHash());
	cout << "\nWalletB пытается отправить деньги (20)  WalletA..." << endl;
	tesst = block3.addTransaction(walletB.sendFunds(walletA.getPublicKey(), 20.0));
	if (tesst)
		bChain.AddBlock(block3);
	cout << "\nБаланс WalletA: " << walletA.getBalance() << endl;
	cout << "Баланс WalletB: " << walletB.getBalance() << endl;
	
	bChain.isChainValid();

	//getchar();
	//bChain.display();

	

	//getchar();

	cout << endl << " Создание и генерация блока...  " << endl;
	Block block4 = Block(bChain.GetvChain().back().GetHash());
	cout << "\nWalletB пытается отправить деньги (10)  WalletA..." << endl;
	tesst = block4.addTransaction(walletB.sendFunds(walletA.getPublicKey(), 10.0));
	if (tesst)
		bChain.AddBlock(block4);
	cout << "\nБаланс WalletA: " << walletA.getBalance() << endl;
	cout << "Баланс WalletB: " << walletB.getBalance() << endl;

	//getchar();
	bChain.display();
	bChain.isChainValid();

	getchar();
	getchar();

	return 0;
}

