#include "block.h"

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