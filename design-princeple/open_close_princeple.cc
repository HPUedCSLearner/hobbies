#include <iostream>
// 课代表
// 1、基类派生类构造函数，和，析构函数调用顺序
//  abstractCalculator()
//  PlusCal()
//  ~PlusCal()
//  ~abstractCalculator()
// 2、声明基类的虚析构函数
//  virtual ~Base(){}
// 3、当我们需要在添加新功能的时候，只需要增加代码，不需要更改源代码，- > 【就是开闭原则】- > 对拓展开放，对修改关闭

class abstractCalculator {
public:
    virtual int getResult() = 0;
    virtual void setOperatorNumber(int a, int b) = 0;

    virtual ~abstractCalculator(){ std::cout << "~abstractCalculator()" << std::endl; };
    abstractCalculator(){ std::cout << "abstractCalculator()" << std::endl; };
};

class PlusCal : public abstractCalculator {
private:
    int _a, _b;
public:
    PlusCal() { std::cout << "PlusCal()" << std::endl; }
    ~PlusCal() { std::cout << "~PlusCal()" << std::endl; } // 测试shared_ptr

    virtual int getResult() { return _a + _b; }
    virtual void setOperatorNumber(int a, int b) {
        this->_a = a;
        this->_b = b;
    }
};

// 当我们需要在添加新功能的时候，只需要增加代码，不需要更改源代码，- > 【就是开闭原则】- > 对拓展开放，对修改关闭
class SubCal : public abstractCalculator {
private:
    int _a, _b;
public:
    virtual int getResult() { return _a - _b; }
    virtual void setOperatorNumber(int a, int b) {
        this->_a = a;
        this->_b = b;
    }
};

void test1() { // test for new, delete
    abstractCalculator * plusCal = new PlusCal;
    delete plusCal;
}
void test2() { // test for smart_pointer
    std::shared_ptr<abstractCalculator> plusCal = std::make_shared<PlusCal>();
}
void test3() { // test for open close princeple
    std::shared_ptr<abstractCalculator> plusCal = std::make_shared<PlusCal>();
    plusCal->setOperatorNumber(33, 44);
    std::cout << plusCal->getResult() << std::endl;

    std::shared_ptr<abstractCalculator> subCal = std::make_shared<SubCal>();
    subCal->setOperatorNumber(33, 44);
    std::cout << subCal->getResult() << std::endl;
}

int main() {
    test3();
    return 0;
}