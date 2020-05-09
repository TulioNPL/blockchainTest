#include "blockchain.h"
#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

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