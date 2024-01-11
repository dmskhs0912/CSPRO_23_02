#include "Array.h"
#include <cstdlib>
#include<iostream>
using namespace std;
Array::Array(int size)
{
	//사이즈를 확인하고 양수이면 new를 사용하여 배열 data를 할당, len값 초기화
	if(size<0)
	{
		cerr << "ERROR : The size must be positive." << endl;
		exit(-1);
	}
	else
	{
		data = new int[size];
		len = size;
	}
}
Array::~Array()
{
	delete (data);
}
int Array::length() const // member function 뒤에 const는 함수 내부에서 객체 수정 불가하게 함.
{
	return len;
}


int& Array::operator[](int i) // 배열에 원소 삽입
{
	static int tmp;

	if(i >= 0 && i < len)
	{
		return data[i];
	}
	else
	{
		cerr << "Array bound error!" << endl;
		return tmp;
	}
}

int Array::operator[](int i) const // 배열의 원소값 반환
{
	if(i >= 0 && i<len)
	{
		return data[i];
	}
	else
	{
		cerr << "Array bound error!" << endl;
		return 0;
	}
}
void Array::print() 
{
	int i;
	cout<<"[";
	for(i = 0; i < len; i++) {
		cout << data[i];
		if(i == len-1) cout << "]";
		else cout << " ";
	}
	cout<<endl;
}
