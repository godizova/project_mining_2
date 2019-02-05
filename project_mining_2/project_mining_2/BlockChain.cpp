#include "BlockChain.h"
#include "Block.h"
//vector<Block> BlockChain::vChain;



BlockChain::BlockChain()// ������� ��������� ������� ����� � ������������? � ���� �� �� ������ �� ���� ��� ���� ����������� ��� ���, ��� ������������ � ���������?
{
	//vChain = vector<Block>();
}


BlockChain::~BlockChain()
{
}

void BlockChain::AddBlock(Block bNew) {
	// !! ����� ����������� ��� ������������ �������? ����� �� ��� ���� ���������� ���? �� ��������� ��� ������� ���
	//bNew.previousHash = GetLastBlock().GetHash();
	//cout << "����������� ����" << bNew << endl;
	//bNew.MineBlock(difficulty);
	vChain.push_back(bNew);
}

Block BlockChain::GetLastBlock() const {
	return vChain.back();
}
//�������� ������ �� ������������, ��������� ����� ������, ����� ����� ������ �� ������
bool BlockChain::isChainValid()
{
	Block currentBlock;
	Block previousBlock;

	char *cstr = new char[difficulty + 1];
	for (int i = 0; i < difficulty; ++i) {
		cstr[i] = '0';
	}
	cstr[difficulty] = '\0';

	string str(cstr);
	// ��������� ������� ������ ����������������� ���������� � ������ ��������� �����.
	map<string, TransactionOutput> tempUTXOs =  map<string, TransactionOutput>();
	tempUTXOs.insert(pair<string, TransactionOutput>(genesisTransaction.outputs.at(0).id, genesisTransaction.outputs.at(0)));
	// ���������� ������� ��� �������� �����:
	for (int i = 1; i < vChain.size(); i++) {
		currentBlock = vChain.at(i);
		previousBlock = vChain.at(i - 1);
		// ���������� ������������������ ��� � ������������ ���:
		if(currentBlock.GetHash() != currentBlock.calculateHash())
		{
			cout << i << " :Current Hashes not equal 1" << endl;
			return false;
		}
		// ���������� ���������� ��� � ������������������ ���������� ���
		if (previousBlock.GetHash() != currentBlock.GetpreviousHash()) {
			cout << i << " Current Hashes not equal 2" << endl;
			return false;
		}
		// ���������, �������� �� ���
		if (currentBlock.GetHash().substr(0, difficulty) != str) {
			cout << i << " This block hasn't been mined" << endl;
			return false;
		}
		// ���� ����� ���������� �������:
		//TransactionOutput tempOutput;
		for (int t = 0; t <currentBlock.GetTransactions().size(); t++) {
			transaction currentTransaction = currentBlock.GetTransactions().at(t);

			/*if (!currentTransaction.verifiySignature()) { // ��������� verifiySignature
				cout << "#Signature on Transaction(" << t << ") is Invalid" << endl;
				return false;
			}*/
			if (currentTransaction.getInputsValue() != currentTransaction.getOutputsValue()) {
				cout << "#Inputs - ����������, ������ ������ �� ���������� (" << t << ")"<< endl;
				return false;
			}

			for (TransactionInput input : currentTransaction.inputs) {
				TransactionOutput tempOutput = TransactionOutput (tempUTXOs.at(input.transactionOutputId).reciepient, tempUTXOs.at(input.transactionOutputId).value, tempUTXOs.at(input.transactionOutputId).parentTransactionId);

				if (tempOutput.parentTransactionId == "") {
					cout << "#������������ ���� ����������(" << t << ") ����������� " << endl;
					return false;
				}	

				if (input.UTXO.value != tempOutput.value) {
					cout << "#������������ ���� ����������(" << t << ") ��������  is Invalid" << endl;
					return false;
				}

				tempUTXOs.erase(input.transactionOutputId);
			}

			for (TransactionOutput output : currentTransaction.outputs) {
				tempUTXOs.insert(pair<string, TransactionOutput>(output.id, output));
			}

			if (currentTransaction.outputs.at(0).reciepient != currentTransaction.reciepient) {
				cout <<"#Transaction(" << t << ") output reciepient is not who it should be"<< endl;
				return false;
			}
			if (currentTransaction.outputs.at(1).reciepient != currentTransaction.sender) {
				cout << "#Transaction(" << t << ") output 'change' is not sender."<< endl;
				return false;
			}

		}


	}
	cout << "Blockchain is valid" << endl;
	return true;
}

void BlockChain::display()
{
	cout << "\n�������� \n";
	for (int i = 0; i < vChain.size(); i++)
	{
		cout << "\n����� �����:" << i << endl;
		cout << vChain[i];
	}
}

vector<Block> BlockChain::GetvChain()
{
	return vChain;
}

