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