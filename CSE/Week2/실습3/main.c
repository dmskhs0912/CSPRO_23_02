#include "Header.h"

int main(int argc, char *argv[]) {
	FILE *fp;
	char *line1, *line2, *tmpline; // 두 개의 입력 버퍼 line1, line2 
	int  Count = 0, Blanks = 0, OBuf_idx=0;
	int  i, B_Flag = 0, B_Line = 0;

	if ( argc != 2 ) {
		printf("Usuage: fmt filename | > outfile\n");
	}
	fp = fopen(argv[1],"r");
	if ( fp == NULL ) {
		printf("File open error.\n");
	}
	line1 = (char *)malloc(BNUM * sizeof(char));
	line2 = (char *)malloc(BNUM * sizeof(char));  // 입력 버퍼 할당
	if ( line1 == NULL || line2 == NULL ) {
		printf("Memory allocation error\n");
		exit(-1);
	}

	if ( fgets(line1, BNUM, fp) == NULL ) { // 한 줄 읽기
		// empty file, just return
		return 0;
	}
	Remove_Blanks_At_The_End(line1); // 불필요한 끝 부분 공백 제거
	if ( line1[0]=='\n' ) {
		putchar('\n');
	}
	Count = 0; // 현재 줄에 실제로 출력할 글자의 개수. 글자 하나 출력할 때마다 하나씩 증가.
	while ( 1 ) {  // EOF 나올 때까지 반복
		if ( B_Line == 0 ) {  // B_Line은 Remove_Blanks_... 함수 실행 이후 그 줄이 빈줄이면 1로 set. (이 경우 해당 라인은 출력x)
			Print_Line( line1, &Count, &B_Flag); // B_Flag는 현재 줄을 완전히 출력했을 때 LIMIT보다 적으면 1로 set. 
		}
		else {
			B_Line = 0;
		}
		if ( Count != 0 ) {
			B_Flag = 1;
		}
		if ( fgets(line2, BNUM, fp) == NULL ) { // 다음 라인 읽기
			break;	// EOF. Exit the while loop
		}
		Remove_Blanks_At_The_End(line2); // L2 끝 공백 제거
		if ( line2[0] == ' ' && Count != 0) { // 더 출력할 수 있는데 다음 줄이 공백으로 시작이면 한줄 띄워서 가야함.
			putchar('\n');
			B_Flag = 0;
			Count = 0;
		}
		else if ( line2[0] == '\n' ) { 
			if ( B_Flag == 1 ) { // 다음 줄이 줄바꿈이고 더 출력할 수 있으면 그냥 줄바꿈.
				putchar('\n');
				B_Flag = 0;
			}
			putchar('\n');
			B_Line = 1;
			Count = 0;
		}
		tmpline = line1; // L2를 L1으로 바꿈 (다음 줄 처리를 위해)
		line1 = line2;
		line2 = tmpline;
	}
	if ( line1[0] != '\n' ) { // 마지막 줄 처리 위함.
		// if the last line is not empty line,
		// check if the last char is '\n' and ouput it if it is.
		for ( i = 0; ; i++ ) {
			if ( (line1[i] == '\n') || (line1[i] == '\0') ) {
				break;
			}
		}
		if ( line1[i] == '\n' ) {
			putchar('\n');
		}
	}
}



