#include "header.h"

void printcount(int *count){
    for(int i=0; i<10; i++){
        printf("%d ", count[i]);   // count 배열 쭉 출력하기
    }
    printf("\n");
}