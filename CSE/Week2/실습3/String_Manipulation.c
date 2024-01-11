#include "Header.h"

void Remove_Blanks_At_The_End( char *line ) {
	int i, k, newline_flag = 0;

	// 전체 문장에 대하여 line[k] 가 줄바꿈이면 flag를 1로 set, '\0'이면 ~~
	for ( k = 0; ; k++ ) {
		if(line[k] == '\n'){
			newline_flag = 1;
			break;
		}
		
		if(line[k] == '\0'){
			break;
		}
	}

	// 전체 문장에 대하여 line[i]가 space가 아니라면 break,
	for ( i = k-1; i >= 0; i-- ) { // \n or \0 에서 계속 앞으로 가면서 공백이 아닌 위치까지 이동.
		if(line[i] != ' ') break;
	}
	i++; // 첫 공백이 아닌 위치의 뒷 부분
	// flag가 1일때 문장의 마지막은 줄바꿈&space, flag가 1이 아니라면 '\0'
	if ( newline_flag == 1 ) {
		line[i] = '\n';
		line[i+1] = ' ';
	}
	else {
		line[i] = '\0';
	}
}

void Get_Blanks_Chars( char *line, int Start, int *N_Blanks, int *N_Chars ) {
	int i, blank_flag = 0;

	*N_Blanks = *N_Chars = 0;
	for ( i = Start; ; i++ ) {
		if ( (line[i] == '\n') || (line[i] == '\0') ) { // 줄바꿈이나 널문자 만나면 멈춤
			break;
		}
		else if ( line[i] == ' ' ) { 
			if ( blank_flag == 0 ) { // 공백 만나고 blank_flag가 0이면 N_Blanks 하나 증가
				++(*N_Blanks);
			}
			else { // 공백 만났는데 blank_flag가 0이 아니면 그냥 멈춤 => 한개의 단어가 끝났음을 의미.
				break;
			}
		}
		else { // 줄바꿈도 공백도 아닌 경우 blank_flag 1로 set 하고 N_chars 증가.
			blank_flag = 1;
			++(*N_Chars);
		}
	}
}
