#include <iostream>
#include <list>

// 课代表：
// 1、问题： 在使用delete的时候的，需要虚析构函数的实现
// 2、观察者模式 ： 是一对多的依赖关系
//    观察者 对 被观察物体是 被动的依赖的关系 （和 现实中不同 ： 观察者 观察到 观察物体状态 发生变化，再调整自己的状态）
//    被观察物体的状态发生变化时候，会通知观察者，更新观察者的状态

class abstractObserver { // 抽象观察者
public:
    virtual void update() = 0; // 接口
};

class abstractSubjuct { // 抽象物体
public:
    virtual void addObserver(abstractObserver *) = 0; // 接口
    virtual void rmvObserver(abstractObserver *) = 0; // 依赖关系
    virtual void notify() = 0; // 刷新观察者的状态
    // virtual ~abstractSubjuct();
};

class observerA : public abstractObserver {
public:
    observerA() { std::cout << "observerA is born" << std::endl; }
    virtual void update() { std::cout << "observerA's status is changed" << std::endl; } // 接口实现； 这个virtual可以省略
};
class observerB : public abstractObserver {
public:
    observerB() { std::cout << "observerB is born" << std::endl; }
    virtual void update() { std::cout << "observerB's status is changed" << std::endl; }
};
class observerC : public abstractObserver {
public:
    observerC() { std::cout << "observerC is born" << std::endl; }
    virtual void update() { std::cout << "observerC's status is changed" << std::endl; }
};
class observerD : public abstractObserver {
public:
    observerD() { std::cout << "observerD is born" << std::endl; }
    virtual void update() { std::cout << "observerD's status is changed" << std::endl; }
};
class observerE : public abstractObserver {
public:
    observerE() { std::cout << "observerE is born" << std::endl; }
    virtual void update() { std::cout << "observerE's status is changed" << std::endl; }
};

class Subjuct : public abstractSubjuct {
public:
    Subjuct() {}
    virtual void addObserver(abstractObserver* observer) { list_Observers.push_back(observer); }
    virtual void rmvObserver(abstractObserver* observer) { list_Observers.remove(observer); }
    virtual void notify() {
        for (auto it = list_Observers.begin(); it != list_Observers.end(); ++it) {
            (*it)->update();
        }
    }
    // virtual ~Subjuct();
private:
    std::list<abstractObserver * > list_Observers;
};

void test() {
    // 创建观察者
    abstractObserver * observer_a = new observerA;
    abstractObserver * observer_b = new observerB;
    abstractObserver * observer_c = new observerC;
    abstractObserver * observer_d = new observerD;
    abstractObserver * observer_e = new observerE;
    // 创建观察目标
    abstractSubjuct * subjuct = new Subjuct;
    subjuct->addObserver(observer_a);
    subjuct->addObserver(observer_b);
    subjuct->addObserver(observer_c);
    subjuct->addObserver(observer_d);
    subjuct->addObserver(observer_e);

    // 更新观察者
    subjuct->notify();

    // 删除一些观察者
    subjuct->rmvObserver(observer_d);
    std::cout << std::endl << std::endl;

    // 更新观察者
    subjuct->notify();

//     delete observer_a;
//     delete observer_b;
//     delete observer_c;
//     delete observer_d;
//     delete observer_e;
//     delete subjuct;
}

int main() {
    test();
    return 0;
}