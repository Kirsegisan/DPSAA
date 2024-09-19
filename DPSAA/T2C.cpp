#include <iostream>
#include <bitset>
#include <cstdlib>
#include <Windows.h>
#include <vector>
using namespace std;

const char n = sizeof(unsigned long long) * 8;

vector<int> T2C(int inputData[], int size){
	unsigned char bitArray[8] ={0};
	unsigned char maska;
	
	for (int i =0; i < size; i++){
		if (inputData[i]>=0 && inputData[i] < 64){
			int byteIndex = inputData[i] / 8;
			int bitIndex = inputData[i] %8;
			maska =1 << bitIndex;
			bitArray[byteIndex] |= maska;
		} else{
			cout<<"Число "<<inputData[i] <<"выходит за пределы [0,63]"<<endl;
		}
}
			
	vector<int> outData;
	
	for (int i =0; i < 64; i ++){
		int byteIndex = i/8;
		int bitIndex = i % 8;
		maska = 1<<bitIndex;
		if (bitArray[byteIndex] & maska){
			outData.push_back(i);
		}
}
	return outData;
}

void Task_2V() {
	int size;
	cout<<"Введите размер массива до 64: ";
	cin >>size;
	
	if (size > 64) {
		cout <<"Размер не должен превышать 64 "<<endl;
		return ;
	}
	
	int* data = new int[size];
	cout <<"Введите значения от 0 до 63"<<endl;
	for (int i =0 ; i < size; i++){
		int angle;
		cin >> angle;
		if ( 0 <= angle && angle < 64){
			data[i] = angle;
		} else{
			cout<<"Неверно. Введите число от 0 до 63"<<endl;
			i--;
		}
	}
	auto begin = chrono::steady_clock::now();

	vector<int> answer = T2C(data,size);

	auto end = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);

	cout << "Время: " << elapsed_ms.count() << " ms\n";
	cout<<"Установленные биты: ";
	for (int i =0 ; i < answer.size(); i ++){
		cout <<answer[i] <<" ";
	}
	cout <<endl;
	delete[] data;

}
