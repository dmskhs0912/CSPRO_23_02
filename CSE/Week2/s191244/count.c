#include "header.h"

long long dp[11][10];

void initialize(int *count){  // count table 0으로 초기화 함수
    for(int i=0; i<10; i++)
        count[i] = 0;
}

int Find_the_degits(int pagenum) // 자리수 구하기 함수
{
    int i=0;
    int power=1;
    while(pagenum / power != 0){ // 10의 거듭제곱으로 계속 나눠서 몫이 0이 될때까지 반복 => i가 자리수.
        i++;
        power *= 10;
    }
    return i;
}


/*                                    알고리즘 설명
dp[i][j]는 i자리 숫자가 포함하는 j의 개수이다. 예를 들어 dp[3][1]은 세 자리 숫자 100~999 중에서 1의 개수를 갖고 있다. 
precount() 함수를 통해 dp table을 모두 채운다. 특정 규칙에 의해 쉽게 구할 수 있다. (dp[n][i] = 10^(n-1) + 9(dp[1][i] + ... + dp[n-1][i])   if n > 0, i > 0)
이후 counter() 함수에서는 주어진 전체 페이지 수의 자릿수를 파악하고 어느 자릿수에 가까운지 확인한다. 예를 들어 페이지 수가 17000이라면 100000보다 10000이 17000에 더 가까우므로 
계산의 베이스는 10000이 된다. 이 경우, dp[1][0~9] + dp[2][0~9] + dp[3][0~9] + dp[4][0~9] 값을 count에 저장한 후, 10000부터 시작해 각 자릿수를 하나씩 체크해 count를 증가시킨다.
만약 페이지 수가 75000이라면 이 수는 10000보다 100000에 더 가까우므로 계산의 베이스를 100000-1으로 한다. 이 경우 dp[1~5][0~9] 값을 count에 저장한 후, 99999부터 시작해 수를 75001까지 줄여가며 
각 자릿수를 체크해 count를 감소시킨다.

1차적으로 dp를 통해 실행 시간이 대폭 감소할 수 있다. 하지만 페이지 수가 999,999,999인 경우 큰 의미가 없어진다. 따라서 숫자가 치우친 경우를 대비해 더 가까운 자릿수로부터 반복문을 수행하게 했다.
*/
void precount() 
{
    for(int i = 1; i < 10; i++) 
        dp[1][i]++;   // 한 자리 수는 1~9까지 각각 1개씩

    for(int i = 2; i < 11; i++) {        // dp[n][i] = 10^(n-1) + 9(dp[1][i] + ... + dp[n-1][i])   if n > 0, i > 0
        for(int j = 1; j < 10; j++) {
            dp[i][j] += pow(10, i-1);
            for(int k = 1; k < i; k++)
                dp[i][j] += 9*dp[k][j];
        }
    }

    for(int i = 2; i < 11; i++) { 
        dp[i][0] = (9*i*pow(10, i-1)) - 9*dp[i][1]; // 0은 전체 수 개수에서 1~9까지를 뺀 나머지
    }
}

void counter(int pagenum, int *count)
{
    int num, num2;
    int comp1, comp2;

    num = Find_the_degits(pagenum); // 자리 수 구하기


    comp1 = pagenum - pow(10, num-1);
    comp2 = pow(10, num) - pagenum;

    if(comp1 < comp2) {  // pagenum이 자신보다 큰 자릿수의 첫 숫자보다 자신의 자리수의 첫 숫자에 더 가까운 경우
        if(num > 1) {
            for(int i = 1; i < num; i++){
                for(int j = 0; j < 10; j++)
                    count[j] += dp[i][j];        // dp table에 미리 계산된 결과 count로 합산
            } 
        }

        for(int i=pow(10, num-1); i<=pagenum; i++){        // 자신의 자릿수의 첫 숫자부터 pagenum까지 반복하며 숫자 세기
            count[i%10]++;
            for(int degit=10; i/degit!=0; degit*=10){
                num2 = i/degit;
                count[num2%10]++;   // 각각 자릿수 더하기
            }
        }
    }

    else {  // pagenum이 자신보다 큰 자리수의 첫 숫자에 더 가까운 경우 (ex. pagenum==75000이면 10000보단 100000에 더 가까움)
        for(int i = 1; i <= num; i++){
            for(int j = 0; j < 10; j++)
                count[j] += dp[i][j];        // pagenum보다 더 큰 자릿수까지 계산함
        }

        for(int i = pow(10, num)-1; i > pagenum; i--) {
            count[i%10]--;
            for(int degit = 10; i/degit != 0; degit *= 10) {
                num2 = i / degit;
                count[num2%10]--;   // 자신보다 큰 자릿수의 첫 숫자 -1 부터 pagenum+1까지 반복하며 숫자 세고 count에서 차감
            }
        }
    }


}