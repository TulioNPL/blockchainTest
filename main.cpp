#include "blockchain.h"
#include <ctime>
#include <vector>
#include <iostream>

using namespace std;

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