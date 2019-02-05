#include "transaction.h"
#include "BlockChain.h"



string transaction::calulateHash()
{
	SHA256 sha256;
	sequence++;// увеличиваем последовательность, чтобы избежать двух одинаковых транзакций с одинаковым хешем
	string calculatedhash = sha256(sender + reciepient + to_string(value) + to_string(sequence));

	return calculatedhash;
}


transaction::transaction(string from, string to, double Value, vector<TransactionInput> in)
{
	sender = from;
	reciepient = to;
	value = Value;
	transactionId = calulateHash();
	inputs = in;
	outputs = vector <TransactionOutput>();
}

transaction::transaction(string from, string to, double val)
{
	sender = from;
	reciepient = to;
	value = val;
	transactionId = calulateHash();
	//inputs = vector <TransactionInput>();
	outputs = vector <TransactionOutput>();
}

transaction::transaction()
{
	sender = '0';
	reciepient = '0';
	value = 0;
	transactionId = calulateHash();
	//inputs = vector <TransactionInput>();
	outputs = vector <TransactionOutput>();
	
}


transaction::~transaction()
{
}

void transaction::generateSignature(string privateKey)
{
	SHA256 sha256;
	string data = sender + reciepient + to_string(value);
	signature = sha256(data + privateKey);
}

bool transaction::verifiySignature(string privateKey)
{
//	EVP_MD_CTX *ctx = EVP_MD_CTX_create();
//	const EVP_MD *md = EVP_get_digestbyname("SHA256");
//
//	//SHA256 sha256;
//	string data = sha256(sender + reciepient + to_string(value));
//	
//
//	if (!md) {
//		printf("Error creating md");
//	}
//	EVP_VerifyInit(ctx, md, NULL);
//
//	EVP_VerifyUpdate(ctx, data.c_str(), data.length);// дописать чо там осталось
//
//	BIO *mem = BIO_new(BIO_s_mem());
//	BIO_puts(mem, sender.c_str());
//	RSA *cipher;
//	PEM_read_bio_RSAPublicKey(mem, &cipher, NULL, NULL);
//	EVP_PKEY *pkey = EVP_PKEY_new();
//	EVP_PKEY_set1_RSA(pkey, cipher);// для создания публичного ключа в виде переменной EVP_PKEY* для 76
//
//	unsigned char *ucBuffer = new unsigned char();
//	strcpy((char *)ucBuffer, signature.c_str());// преобразование string в *unsigned char для 76
//
//	return EVP_VerifyFinal(ctx, ucBuffer, signature.length, pkey);
	
	SHA256 sha256;
	string data = sender + reciepient + to_string(value);

	if (signature == sha256(data + privateKey))
	{
		return true;

	}
	else
		return false;
}

bool transaction::processTransaction()
{
	// тут должен быть verifiySignature  но т.к. я не смогла его сделать без приватного ключа, пока без него

	// собираем транзакционные входы (убедитесь, что они не были израсходованы):
	BlockChain blChain = BlockChain();// класс блокчейна для обращения к статиеской переменной
	for (TransactionInput i : inputs) {
		//i.UTXO = blChain.UTXOs.at(i.transactionOutputId);
		i.UTXO.copyTransactionOutput(blChain.UTXOs.at(i.transactionOutputId));
	}

	// проверяем, действительно ли транзакция действительна:
	if (getInputsValue() < blChain.minimumTransaction) {
		cout <<"\n\nВходы транзакций небольшие: " << getInputsValue();
		return false;
	}

	// генерировать транзакционные выходы:
	double leftOver = getInputsValue() - value; //получить значение входных данных, а затем изменить слева:
	transactionId = calulateHash();
	outputs.push_back(TransactionOutput(reciepient, value, transactionId)); //отправлять значение получателю
	outputs.push_back(TransactionOutput(sender, leftOver, transactionId)); //отправьте слева на «изменение» обратно отправителю		

	// добавлять выходы в список
	for (TransactionOutput o : outputs) {
		blChain.UTXOs.insert(pair<string, TransactionOutput>(o.id, o));
	}

	// удалять транзакционные входы из списков UTXO как потраченные:
	for (TransactionInput i : inputs) {
		//if (i.UTXO == null) continue; //if Transaction can't be found skip it 
		blChain.UTXOs.erase(i.UTXO.id);
	}

	return true;
}
// возвращает сумму значений входов (UTXO)
double transaction::getInputsValue()
{
	double total = 0.0;
	for (TransactionInput i : inputs) {
		//if (i.UTXO == NULL) continue; //если транзакция не найдена, пропустить ее
		total += i.UTXO.value;
	}
	return total;
}
// возвращает сумму выходов:
double transaction::getOutputsValue()
{
	double total = 0;
	for (TransactionOutput &o : outputs) {
		total += o.value;
	}
	return total;
}
// возвращает ID транзакции
string transaction::transactionIdGet()
{
	return transactionId;
}

ostream & operator<<(ostream & stream, const transaction & abook)
{
	stream << "\n\t\tАдрес получателя: " << abook.reciepient << endl;
	stream << "\t\tКоличество: " << abook.value << endl;
	stream << "\t\tАдрес отправителя: " << abook.sender << endl;
	return stream;
}
