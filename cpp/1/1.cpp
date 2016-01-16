#include <iostream>

using namespace std;

class B {
	public:
	//constructor
	B(int x=0,int y=0): m_A(x),m_B(y) {
	    std::cout << "Constructor " << std::endl; 	
		}
	
	B(const B&){
	    std::cout << "Copy Constructor " << std::endl; 	
		}
	
	//copy constructor
	
	//public methods
	int getA(){
		return m_A;
		};
	void setA(int k){
		m_A = k;
		};
	int getB(){
		return m_B;
		};
	int setB(int k){
		m_B = k;
		};
	
	
	protected:
	int m_A;
	int m_B;
	};

class D:public B {
	//constructor
	
	
	//copy constructor
	
	//public methods
	
	
	
	
	};




int main() {
	B Base;
	D Derived();
	B Copy = Base;
	//Copy = 
	
	
	
	
	
	
	
	}
