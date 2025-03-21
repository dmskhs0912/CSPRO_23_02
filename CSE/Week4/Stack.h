#include "LinkedList.h"


//1. 템플릿 클래스로 확장해야함
//2. Stack형식으로 Delete 함수 재정의해야함
//주의: first, current_size는 class의 멤버 변수이기 때문에 this 포인터를 사용하여 가져와야함

//LinkedList class를 상속받음
template <class T>
class Stack : public LinkedList<T>{
	public:
		bool Delete (T &element){
			Node<T> *current = this -> first;
			if(this->first == 0) return false;
			
			element = this->first->data;
			this->first = this->first->link;
			delete current;
			this->current_size--;
		
			return true;
			}
};
