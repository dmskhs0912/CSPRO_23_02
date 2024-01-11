#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* input(int *casenum, int *arr);
void initialize(int *count);
int Find_the_degits(int pagenum);
void precount();
void counter(int pagenum, int *count);
void printcount(int *count);

extern long long dp[11][10];