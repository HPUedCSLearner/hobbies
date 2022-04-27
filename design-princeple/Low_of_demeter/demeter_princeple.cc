#include <string>
#include <iostream>
#include <vector>

// 课代表
// 1、Demeter law ,又称 最少知道原则
//     第一种方式，直接一个一个去每一个楼盘问，直接和楼盘打交道 （不是最少知道，很累～）
//     第二种方式，人 中介 楼盘 ：不用和楼盘打交道，不需要知道楼盘的内部实现，直接和中介打交道，将人和楼盘解耦

class AbstractBuilding {
public:
    virtual void sale() = 0;
    virtual std::string getQuality() = 0;
    virtual ~AbstractBuilding() {}
};

// 楼盘A
class BuildingA : public AbstractBuilding {
public:
    BuildingA() : mQuality("低品质") {}
    virtual void sale() { std::cout << "楼盘A (" << mQuality << ") 被售卖！" << std::endl; }
    virtual std::string getQuality() { return mQuality; }
private:
    std::string mQuality;
};

// 楼盘B
class BuildingB : public AbstractBuilding {
public:
    BuildingB() : mQuality("高品质") {}
    void sale() { std::cout << "楼盘B (" << mQuality << ") 被售卖！" << std::endl; }
    virtual std::string getQuality() { return mQuality; }
private:
    std::string mQuality;
};

// 如果一个人，想要买高品质的楼盘 ： 第一种方式，直接一个一个去每一个楼盘问，直接和楼盘打交道
void test1() {
    std::string personNeedBuilding = "高品质";
    // 人 先去问问楼盘A
    BuildingA * ba = new BuildingA;
    if (personNeedBuilding == ba->getQuality()) { // 如果是此人想要的楼盘，那么此楼盘会被出售
        ba->sale();
    }
    delete ba;
    // 人 再去问问楼盘B
    std::shared_ptr<BuildingB> bb = std::make_shared<BuildingB>();
    // auto bb = std::make_shared<BuildingB>(); // c++11 支持 auto
    if (personNeedBuilding == bb->getQuality()) {
        bb->sale();
    }
    // 人 再去问问。。。。
}

// 中介类 （让人直接和中介类打交道，将人和楼盘解耦
class Media {
public:
    void addBuildings(AbstractBuilding* building) {
        vBuildings.push_back(building);
    }
    AbstractBuilding * findBuilding(std::string needQuelity) {
        for ( auto it = vBuildings.begin(); it != vBuildings.end(); ++it ) {
            if ((*it)->getQuality() == needQuelity) {
                return *it;
            }
        }
        return nullptr;
    }
private:
    std::vector<AbstractBuilding*> vBuildings; // AbstractBuilding * 作为中介的成员变量 （不负责它的生命周期，聚合关系）
};

// 人 不用和楼盘打交道，不需要知道楼盘的内部实现，直接和中介打交道，将人和楼盘解耦
void test2() {
    // 市面上的楼盘 ...
    AbstractBuilding * ba = new BuildingA;
    AbstractBuilding * bb = new BuildingB;
    // 中介 中介收集市面上的楼盘信息
    std::shared_ptr<Media> media = std::make_shared<Media>();
    media->addBuildings(ba);
    media->addBuildings(bb);
    // 人 需要的品质的楼盘
    std::string personNeedQuality = "高品质";
    // 人 找中介 看看有没有自己的需要的
    AbstractBuilding * result = media->findBuilding(personNeedQuality);

    if (result != nullptr) {
        std::cout << "需要的楼盘 " << personNeedQuality << " 还有" << std::endl;
        result->sale();
    } else {
        std::cout << "需要的楼盘 " << personNeedQuality << " 已经卖完了" << std::endl;
    }

    delete ba;
    delete bb;
}

int main() {
    // test1();
    test2();
    return 0;
}