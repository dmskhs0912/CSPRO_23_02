#include "header.h"

int* input(int *casenum, int *arr)
{
    int num;
    scanf("%d", casenum);   // 테스트 케이스 수 입력
    arr = (int*)malloc((*casenum) * sizeof(int));    // 테스트 케이스 수 만큼 메모리 할당
    for(int i = 0; i < *casenum; i++)
        scanf("%d", &arr[i]);   // 각각 테스트케이스에 대해 pagenum 입력
    return arr;  // 메모리 할당 받은 배열 반환

}



