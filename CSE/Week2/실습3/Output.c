#include "Header.h"

void Print_Line( char *line, int *Count, int *B_Flag ) {
	int i, N_Blanks, N_Chars, Start=0;
	// Start는 현재 이 인덱스까지 출력이 진행되어 왔음을 의미. 항상 단어의 끝을 가리킴.
	// N_Blanks는 Start 이후 존재하는 공백 개수
	// N_Chars는 다음 단어의 글자 수 

	Get_Blanks_Chars( line, Start, &N_Blanks, &N_Chars );
	while ( N_Chars != 0 ) { // N_Chars가 0이 될 때까지 반복
		if ( (*B_Flag == 1) && ((*Count + N_Chars + 1) <= LIMIT) ) {  // B_Flag가 1이고 다음 단어까지 출력할 여유 있으면

			/* In this part, N_Blanks == 0 in order that L1 and L2 should be merged.
			* "N_Blanks != 0" means that L2 is written at the next line.
			*/
			if ( N_Blanks != 0 ) {
				printf("Something Wrong!\n");
				exit(-1);
			}

			putchar(' '); // 공백 하나 출력
			*B_Flag = 0; // B_Flag 0으로 set
			for ( i = Start; i < Start + N_Chars; i++ ) {
				putchar(line[i]); // 단어 출력
			}
			Start = Start + N_Chars;
			*Count = *Count + N_Chars + 1;
			Get_Blanks_Chars( line, Start, &N_Blanks, &N_Chars );
		}
		else if ( (*Count + N_Blanks + N_Chars) <= LIMIT ) { // B_Flag가 0이고 공백+다음 단어 출력할 여유 있으면
			for ( i = Start; i < Start + N_Blanks + N_Chars; i++ ) {
				putchar(line[i]); // 공백 + 단어 출력
			}
			Start = Start + N_Blanks + N_Chars; //Start 위치 조정
			*Count = *Count + N_Blanks + N_Chars; // Count 개수 조정
			Get_Blanks_Chars( line, Start, &N_Blanks, &N_Chars ); // 다시 다음 공백, 단어 글자 수 읽기
		}
		else { // 다음 출력 여유 없으면
			if ( *Count == 0 ) { // Count 0이면
				for ( i = Start; i < Start + N_Blanks + N_Chars; i++ ) {
					putchar(line[i]); // 출력
				}
				Start = Start + N_Blanks + N_Chars; // Start 위치 조정
				putchar('\n'); // 줄바꿈
				Get_Blanks_Chars( line, Start, &N_Blanks, &N_Chars ); // 다음 공백, 단어 글자 수 읽기
				Start = Start + N_Blanks; // Start를 공백 수만큼 증가?
			}
			else { // Count != 0 이면
				putchar('\n'); // 줄바꿈
				*B_Flag = 0;
				for ( i = Start + N_Blanks; i < Start + N_Blanks + N_Chars; i++ ) {
					putchar(line[i]);
				}
				Start = Start + N_Blanks + N_Chars;
				*Count = N_Chars;
				Get_Blanks_Chars( line, Start, &N_Blanks, &N_Chars );
			}
		}
	}
}
