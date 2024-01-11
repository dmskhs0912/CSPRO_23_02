#include <iostream>
#include "Str.h"
using namespace std;

int main()
{
    Str a("I'm a girl");
    cout << a.contents();
    a = "I'm a boy\n";
    cout << a.contents();
    cout << a.compare("I'm a a") << endl;
    cout << a.length() << endl; // length() method test
    Str b(12); // 길이를 이용한 생성자 test
    b = "aaaaaaaaaabb"; 
    cout << b.contents() << endl;
    a = b; // Str 객체끼리 대입 연산자 test
    cout << a.contents() << endl << b.contents() << endl;
    cout << a.length() << endl;
    cout << a.compare(b) << endl; // Str 객체끼리 compare test
    return 0;
}