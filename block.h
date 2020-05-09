#include "Transaction.h"

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
