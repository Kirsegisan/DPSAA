#include <iostream>
#include <bitset>
#include <cstdlib>
#include <Windows.h>
#include <vector>
using namespace std;

//const char n = sizeof(unsigned long long) * 8;

vector<int> T2B(int inputData[], int size){
	unsigned long long x =0;
	unsigned long long maska;
	
	for (int i =0; i < size; i++){
		if (inputData[i]>=0 && inputData[i] < 64){
			maska = 1ULL <<inputData[i];
			cout <<bitset<n>(maska)<<endl;
			x = (x | maska);
		} else {
			cout <<"Значение "<< inputData[i] <<" выходит за пределы [0,63]. "<<endl;
		}
	}
	cout <<bitset<n>(x)<<endl;
	vector<int> outData;
	
	for (int i =0; i < 64; i ++){
		maska=1ULL <<i;
		if (x & maska) {
			outData.push_back(i);
		}
	}
	return outData;
	
}

void Task_2B() {
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
	vector<int> answer = T2B(data,size);
	cout<<"Установленные биты: ";
	for (int i =0 ; i < answer.size(); i ++){
		cout <<answer[i] <<" ";
	}
	cout <<endl;
	delete[] data;

}
