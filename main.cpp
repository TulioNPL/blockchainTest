#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

//Trasactions
struct Transaction {
	double value;	//sent value
	string payerKey;
	string receiverKey;
	time_t timestamp; //Time when the transaction was made
};

//Block
class Block {
	private:
		int idx;	//index
		size_t blockHash;	//current block hash
		size_t prevHash;//previous block hash
		size_t generateHash();

	public:
		Block(int idx, Transaction d, size_t prevHash); //Constructor
		size_t getHash();	//get current block Hash
		size_t getPrevHash();	//get previous block Hash
		Transaction data;
		bool isHashValid();	//function to validate Hash
};

//Block constructor
Block::Block(int idx, Transaction d, size_t prevHash) {
	this->idx = idx;
	data = d;
	this->prevHash = prevHash;
	blockHash = generateHash();
}

size_t Block::generateHash() {
	hash<string> hash1;
	hash<size_t> hash2;
	hash<size_t> finalHash;
	string toHash = to_string(data.value) + data.receiverKey + data.payerKey + to_string(data.timestamp);

	return finalHash(hash1(toHash) + hash2(prevHash));
}

size_t Block::getHash() {
	return blockHash;
}

size_t Block::getPrevHash() {
	return prevHash;
}

bool Block::isHashValid() {
	return generateHash() == blockHash;
}

//Blockchain
class Blockchain {
	private:
		Block createGenesis(); //function to generate the first block
		
	public:
		vector<Block> chain; //Public chain
		Blockchain();	//Constructor
		void addBlock(Transaction data);
		bool isChainValid();

		Block *getLatestBlock(); //Pointer for test only!

		
};

//Constructor
Blockchain::Blockchain() {
	Block genesis = createGenesis();
	chain.push_back(genesis);
}

Block Blockchain::createGenesis() {
	time_t current;
	Transaction d;
	d.value = 0;
	d.receiverKey = "None";
	d.payerKey = "None";
	d.timestamp = time(&current);

	hash<int> hash1;
	Block genesis(0,d,hash1(0));

	return genesis;
}

//Pointer for test only!
Block *Blockchain::getLatestBlock() {
	return &chain.back();
}

void Blockchain::addBlock(Transaction d) {
	int idx = (int)chain.size() -1;
	Block newBlock(idx, d, getLatestBlock()->getHash());	
}

bool Blockchain::isChainValid() {
	vector<Block>::iterator i;
	int chainLen = (int)chain.size();

	for(i = chain.begin(); i != chain.end(); ++i) {
		Block currentBlock = *i;

		if(!currentBlock.isHashValid()) {
			return false;
		}

		if(chainLen > 1) {
			Block prevBlock = *(i-1);
			if(currentBlock.getPrevHash() != prevBlock.getHash()) {
				return false;
			}
		}
	}

	return true;
}

int main() {
	//Start blockchain
	Blockchain testCoin;

	//First added block
	Transaction data1;
	time_t data1Time;
	data1.value = 3.141516;
	data1.receiverKey = "Tulio";
	data1.payerKey = "Izabella";
	data1.timestamp = time(&data1Time);	
	
	testCoin.addBlock(data1);

	cout << "Is chain valid? " << endl 
		<< testCoin.isChainValid() << endl;
	
	//Second added block
	Transaction data2;
	time_t data2Time;
	data2.value = 5.16;
	data2.receiverKey = "Pedro";
	data2.payerKey = "Izabella";
	data2.timestamp = time(&data1Time);

	testCoin.addBlock(data2);

	cout << "Is chain valid?" << endl
		<< testCoin.isChainValid() << endl;

	//Hacking test
	Block *hackedBlock = testCoin.getLatestBlock();
	hackedBlock->data.value = 100;
	hackedBlock->data.receiverKey = "Bertone";

	cout << "Is chain valid?" << endl
		<< testCoin.isChainValid() << endl;
	
}

