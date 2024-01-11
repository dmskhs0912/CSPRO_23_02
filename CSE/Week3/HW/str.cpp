#include <iostream>
#include <string.h>
#include <stdlib.h> // exit() 사용 위해 include
#include "Str.h"
using namespace std;

Str::Str(int leng) // 길이를 인자로 받는 생성자
{
    if(leng < 0){
        cerr << "ERROR : Invalid length. The length must be nonnegative." << endl; // 인자로 주어진 길이가 음수이면 에러메시지 출력과 종료.
        exit(-1);
    }
    else{
        len = leng; // 인자로 받은 길이 len에 저장
        str = new char[len+1]; // str에 len+1만큼 메모리 할당. +1은 널 문자 자리
    }
}

Str::Str(char *neyong) // 초기화할 내용을 인자로 받는 생성자
{
    len = strlen(neyong); // len에 neyong의 길이 저장
    str = new char[len+1]; // str에 len+1만큼 메모리 할당
    strcpy(str, neyong); // neyong의 내용을 str에 복사
}

Str::~Str() // 소멸자
{
    delete str; // str에 할당된 메모리 free
}

int Str::length()
{
    return len; // string의 길이 리턴
}

char* Str::contents()
{
    return str; // string의 내용 리턴
}

int Str::compare(class Str& a) // a의 내용과 strcmp (인자가 Str 객체인 경우)
{
    return strcmp(str, a.contents()); // 내용이 같으면 0, str이 a의 내용보다 사전적으로 뒤에 나오는 경우 양수, 앞에 나오는 경우 음수 리턴
}

int Str::compare(char *a) // 인자가 char*으로 오는 경우
{
    return strcmp(str, a); // 위와 동일
}

void Str::operator=(char *a) // 내용 대입 (인자가 char*로 오는 경우)
{
    len = strlen(a); // len에 대입할 a의 길이 저장
    delete str; 
    str = new char[len+1]; // a의 길이에 맞춰 str 다시 할당
    strcpy(str, a); // a의 내용을 str에 복사 
}

void Str::operator=(class Str& a) // 인자가 Str 객체인 경우
{
    len = a.length(); // length() 메소드를 이용해 len에 a의 길이 저장
    delete str;
    str = new char[len+1]; // a의 길이에 맞춰 str 다시 할당
    strcpy(str, a.contents()); // a의 내용을 str에 복사
}
