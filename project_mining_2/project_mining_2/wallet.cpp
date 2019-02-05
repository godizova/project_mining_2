#include "wallet.h"
#include <ctime>
#include <string>
#include <Windows.h>
#include <ctime>
#include <random>
#include "BlockChain.h"

string wallet::generateKeyPair()
{
	int quantity = 16;
	//srand(time(NULL) + m++);
	mt19937 gen(clock());
	//default_random_engine generator;
	uniform_int_distribution<> distribution('a', 'z');
	char *cstrPrivate = new char[quantity];

	for (int i = 0; i < quantity; ++i) {
		//cstrPrivate[i] = char('a' + rand() % ('z' - 'a'));
		cstrPrivate[i] = distribution(gen);

	}
	cstrPrivate[quantity] = '\0';
	string str(cstrPrivate);//надо сделать возврат строки?
	cout << str << endl << endl;
	return str;
}

wallet::wallet()
{
	privateKey = generateKeyPair();
	publicKey = generateKeyPair();
}


wallet::~wallet()
{
}

string wallet::getPrivateKey()
{
	return privateKey;
}

string wallet::getPublicKey()
{
	return publicKey;
}

// возвращает баланс и сохраняет UTXO, принадлежащий этому кошельку, в этом.
double wallet::getBalance()
{
	double total = 0;	
	BlockChain blChain = BlockChain();// класс блокчейна для обращения к статиеской переменной

	for (auto item : blChain.UTXOs) {
		TransactionOutput UTXO = item.second;
		if (UTXO.isMine(publicKey)) { //если вывод принадлежит мне (если монеты принадлежат мне)
			UTXOs.insert(pair<string, TransactionOutput>(UTXO.id, UTXO)); //добавим его в наш список нерастраченных транзакций.
			total += UTXO.value;
		}
	}
	return total;
}

// Создает и возвращает новую транзакцию из этого кошелька.
transaction wallet::sendFunds(string _recipient, double value)
{
	if (getBalance() < value) { //собирать баланс и проверять средства.
		cout << "\nНе достаточно средств для отправки транзакции. Отказ транзакции." << endl;
		return transaction();
	}
	//создаем список массивов входов
	vector<TransactionInput> inputs = vector<TransactionInput>();

	double total = 0;
	for (auto item : UTXOs) {
		TransactionOutput UTXO = item.second;
		total += UTXO.value;
		inputs.push_back(TransactionInput(UTXO.id, UTXO));
		if (total > value) break;
	}

	transaction newTransaction = transaction(publicKey, _recipient, value, inputs);
	newTransaction.generateSignature(privateKey);

	for (TransactionInput input : inputs) {
		UTXOs.erase(input.transactionOutputId);
	}
	return newTransaction;
}


