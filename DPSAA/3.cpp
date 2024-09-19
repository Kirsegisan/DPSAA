#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstdlib>

using namespace std;
const int MAX_NUM = 999999;
const int MIN_NUM= 100000;
const int BIT_ARRAY_SIZE=(MAX_NUM/8) +1;

void createBitArray(char* bitArray){
	fill(bitArray, bitArray + BIT_ARRAY_SIZE,0);
}

void setBit(char* bitArray, int number){
	bitArray[number/8] |=(1<<(number%8));
}

bool isBitSet(const char* bitArray, int number){
	return bitArray[number/8] & (1<<(number%8));
}

void write(const char* bitArray,ofstream& outFile){
	for (int i = MIN_NUM; i <=MAX_NUM; i ++){
		if (isBitSet(bitArray,i)) {
			outFile <<i <<"\n";
		}
	}
}

void Task3() {

	auto begin = chrono::steady_clock::now();

	fstream inFile;inFile.open("input.txt");
	ofstream outFile;outFile.open("output.txt");
	
	if (!inFile.is_open() || !outFile.is_open()) {
		std::cout <<"Ошибка"<<std::endl;
	}
	
	char* bitArray = new char[BIT_ARRAY_SIZE];
	createBitArray(bitArray);
	
	int number;
	while (inFile >>number) {
		setBit(bitArray,number);
	}
	

	write(bitArray, outFile);
	
	auto end = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
	
	
	cout << "Время: " << elapsed_ms.count() << " ms\n";
	
	
	cout <<"V оперативной памяти " <<sizeof(bitArray)<<" байт"<<endl;
	
	inFile.close();
	outFile.close();	

}
