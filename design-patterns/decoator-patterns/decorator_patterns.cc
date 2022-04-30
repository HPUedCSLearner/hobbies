#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;

class AbstractHero { // 抽象英雄
public:
    virtual void ShowStatus() = 0;
    virtual ~AbstractHero() {}
public:
    int mHp;
    int mMp;
    int mAt;
    int mDf;
};

class HeroA : public AbstractHero { // 具体英雄
public:
    HeroA()
    { mHp = 0; mMp = 0; mAt = 0; mDf = 0; }

    virtual void ShowStatus() {
        cout << "血量" << mHp << endl;
        cout << "魔法" << mMp << endl;
        cout << "攻击" << mAt << endl;
        cout << "防御" << mDf << endl;
    }
};

class AbstractEquipment : public AbstractHero { // 抽象装饰器 （其实还是英雄）
public:
    AbstractEquipment(AbstractHero * hero)
    :pHero(hero) {}
    virtual ~AbstractEquipment(){}
    virtual void ShowStatus(){} // 空实现
public:
    AbstractHero * pHero;
};

class KuangtuEquipment : public AbstractEquipment { // 具体的装饰器 （其实还是英雄）
public:
    KuangtuEquipment(AbstractHero * hero)
    :AbstractEquipment(hero){ addKuangtuAttr(); }
    void addKuangtuAttr(){
        cout << "英雄穿上狂徒铠甲之后..." << endl;
        printf("this->mAt = %p, this->pHero->mAT = %p\n", &this->mAt, &this->pHero->mAt);
        // this->mAt = 0x60000379d150, this->pHero->mAT = 0x60000379d130
        this->mAt = this->pHero->mAt + 99;
        this->mDf = this->pHero->mDf + 1;
        this->mHp = this->pHero->mHp + 1;
        this->mMp = this->pHero->mMp + 1; // 涉及抽象类 和 对象的 内存布局
        delete this->pHero;
    }
    // delete this->pHero; // 这个语句放这里为什么不可以❌
    virtual void ShowStatus() {
        // addKuangtu();
        cout << "血量" << mHp << endl;
        cout << "魔法" << mMp << endl;
        cout << "攻击" << mAt << endl;
        cout << "防御" << mDf << endl;
    }
};

void test1() {
    AbstractHero * hero = new HeroA;
    hero->ShowStatus();

    cout << "----------------" << endl;
    
    // 给裸奔的英雄 增加狂徒装备后，属性发生改了改变
    hero = new KuangtuEquipment(hero);
    hero->ShowStatus();

    hero = new KuangtuEquipment(hero);
    hero->ShowStatus();

    hero->ShowStatus(); // 再次执行此语句的时候 -> segmentation fault  ./a.out
}

int main() {
    test1();
    return 0;
}