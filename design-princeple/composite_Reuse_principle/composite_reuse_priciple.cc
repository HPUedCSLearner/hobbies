#include<iostream>

//  课代表
//  1、能用组合，就不要用继承，（因为继承的耦合性太强）
//  2、组合复用原则 一句话 - > 能用组合，就不要用继承

class Car {
public:
    virtual void run() = 0;
    virtual ~Car(){};
};

class BYD : public Car {
public:
    void run() { std::cout << "BYD 启动" << std::endl; }
};
class BMW : public Car {
public:
    void run() { std::cout << "BMW 启动" << std::endl; }
};
class AUDI : public Car {
public:
    void run() { std::cout << "AUDI 启动" << std::endl; }
};

// 1、通过继承来实现
class PersonHasBYD : public BYD {
public:
    void DouFeng() {
        run();
    }
};
// 通过继承来实现的话，这是一种极强耦合关系，人和车不应该有这么强的耦合关系
// 如果想要换其他车，就要一直创建很多的类，因为耦合性太强了
void test1() {
    std::shared_ptr<PersonHasBYD> personHsaByd = std::make_shared<PersonHasBYD>();
    personHsaByd->DouFeng();
}

// 2、通过组合（-聚合）来实现
class Person {
public:
    Person() : car(nullptr) {}
    void buyCar(Car* _car) { 
        car = _car;
        std::cout << "buy a car, after " << std::endl;
    }
    void DouFeng() {
        if (car) {
            this->car->run();
        } else {
            std::cout << "don't have a car, can not DouFeng" << std::endl;
        }
    }
private:
    Car* car; // 作为成员变量，并且不负责此变量的生命周期，是组合关系
};

void test2() {
    // 市场上的车
    Car* bydCar = new BYD;
    Car* bmwCar = new BMW;
    Car* audiCar = new AUDI;
    // 张三买车之后，就可以兜风了
    Person zhangshan;
    zhangshan.DouFeng();
    zhangshan.buyCar(bmwCar);
    zhangshan.DouFeng();

    // person不负责car的生命周期，是组合关系
    delete bydCar;
    delete bmwCar;
    delete audiCar;

}

// 2、通过组合（-组合）来实现 - 负责car的生命周期
class Composite_Person {
public:
    Composite_Person() : car(nullptr) {}
    void buyCar(Car* _car) { 
        car = _car;
        std::cout << "buy a car, after " << std::endl;
    }
    void DouFeng() {
        if (car) {
            this->car->run();
        } else {
            std::cout << "don't have a car, can not DouFeng" << std::endl;
        }
    }
    ~Composite_Person() {
        if (car) {
            delete car; // 负责car的生命周期（可以少些很多delete了）
            car = nullptr;
        }
    }
private:
    Car* car; // 作为成员变量，并且不负责此变量的生命周期，是组合关系
};

void test3() {
    // 市场上的车
    Car* bydCar = new BYD;
    Car* bmwCar = new BMW;
    Car* audiCar = new AUDI;
    // 张三买车之后，就可以兜风了
    Composite_Person zhangshan;
    zhangshan.DouFeng();
    zhangshan.buyCar(audiCar);
    zhangshan.DouFeng();

}

int main() {
    // test1();
    // test2();
    test3();
    return 0;
}