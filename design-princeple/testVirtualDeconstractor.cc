#include <iostream>
using namespace std;

class Base{
public:
    Base() { cout<<"Base Constructor"<<endl; }
    // ~Base() { cout<<"Base Destructor"<<endl; }
	//  virtual ~Base() {} // 声明一下析构函数 是 虚函数
	 virtual ~Base() { cout<<"Base Destructor"<<endl; }
};
class Derived: public Base{
public:
    Derived() { cout<<"Derived Constructor"<<endl; }
    ~Derived() { cout<<"Derived Destructor"<<endl; }
};
int main(){
    Base *p = new Derived();
    delete p;
    return 0;
}
