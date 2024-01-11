#ifndef __STR__
#define __STR__

class Str{
	private:
		char *str; // string 내용
		int len; // string 길이
	public:
		Str(int leng); // 길이를 인자로 받는 생성자
		Str(char *neyong); // 초기화할 내용을 받는 생성자
		~Str();
		int length(void); // string의 길이 리턴 함수
		char *contents(void); // string의 내용 리턴 함수
		int compare(class Str& a); // a의 내용과 strcmp
		int compare(char *a); // a의 내용과 strcmp
		void operator=(char *a); // string 내용 대입
		void operator=(class Str& a); // Str 내용 대입

};
#endif
