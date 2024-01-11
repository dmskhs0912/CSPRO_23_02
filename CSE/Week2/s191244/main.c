#include "header.h"



int main()
{
    int casenum;  // 테스트 케이스 수
    int *arr;   // 각 테스트 케이스에 해당하는 pagenum이 들어갈 배열
    int count[10];  // 0~9 숫자 개수 저장할 배열


    arr = input(&casenum, arr);

    precount();  // dp table 채우기
    
    for(int i=0; i<casenum; i++){  // 각각 테스트 케이스에 대해 계산 후 출력
        initialize(count);  // count 초기화
        counter(arr[i], count); // 계산
        printcount(count); // 출력
    }
    return 0;

}