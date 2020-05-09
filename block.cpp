#include "block.h"
#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

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