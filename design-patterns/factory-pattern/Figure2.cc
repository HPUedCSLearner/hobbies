 ///
 /// @file    Figure.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-28 14:31:43
 ///

// 课代表
//静态工厂方法
//
//
//工厂模式(工厂方法), 该名称有可能是特指，也有可能是统称
//生成一种系列的产品时，叫工厂模式
//生产多种系列的产品时，叫抽象工厂模式
//
//优势: 1. 满足开闭原则
//		2. 满足单一职责原则
//
//强调: 1. 该模式并不是什么时候都需要，对于简单对象的创建，
//		   不需要使用工厂模式
//		2. 当需要批量创建对象时，才需要使用; 或者是为了应对
//		   需求的变化，考虑扩展性时可以采用
//		3.不要滥用设计模式，不要为了用而用

 
#include <math.h>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class Figure
{
public:
	virtual void display() const =0;
	virtual double area()=0;

	virtual ~Figure() {}
};

class Circle
: public Figure
{
public:
	Circle(double radius)
	: _radius(radius)
	{}

	void display() const
	{	cout << "circle";	}

	double area()
	{
		return 3.14159 * _radius * _radius;
	}

	~Circle() {	cout << "~Circle()" << endl;	}

private:
	double _radius;
};

class Rectangle
: public Figure
{
public:
	Rectangle(double length, double width)
	: _length(length)
	, _width(width)
	{}

	~Rectangle() { cout << "~Rectangle()" << endl; }

	void display() const
	{	cout << "rectangle";	}

	double area()
	{	return _length * _width;	}

private:
	double _length;
	double _width;
};

class Triangle
: public Figure
{
public:
	Triangle(double a, double b, double c)
	: _a(a)
	, _b(b)
	, _c(c)
	{}

	~Triangle() {	cout << "~Triangle()" << endl;	}

	void display() const
	{	cout << "triangle";}

	double area()
	{
		double p = (_a + _b + _c) / 2;
		return sqrt(p * (p - _a) * (p - _b) * (p - _c));
	}

private:
	double _a;
	double _b;
	double _c;
};

#if 0
class Cube
: public Figure
{
public:
	Cube(double a)
	: _a(a)
	{}

	void display() const
	{	cout << "cube";	}

	double area()
	{
		return 6 * _a * _a;
	}


private:
	double _a;
};
#endif

void display(Figure * fig) // 多态特性
{
	fig->display();
	cout << "的面积是:" << fig->area() << endl;
}



//
//工厂模式(工厂方法), 该名称有可能是特指，也有可能是统称
//生成一种系列的产品时，叫工厂模式
//生产多种系列的产品时，叫抽象工厂模式
//
//优势: 1. 满足开闭原则
//		2. 满足单一职责原则
//
//强调: 1. 该模式并不是什么时候都需要，对于简单对象的创建，
//		   不需要使用工厂模式
//		2. 当需要批量创建对象时，才需要使用; 或者是为了应对
//		   需求的变化，考虑扩展性时可以采用
//		3.不要滥用设计模式，不要为了用而用


class Factory //抽象的工厂
{
public:
	virtual Figure * create() = 0;//抽象的产品

	virtual ~Factory() {}
};


class RectangleFactory
: public Factory
{
public:
	Figure * create()
	{
		// txt  xml  json(可视化)
		// load configuration file...
		// ....
		return new Rectangle(10, 20);
	}
};


class CircleFactory
: public Factory
{
public:
	Figure * create()
	{
		// load configuration file...
		// ....
		return new Circle(10);
	}
};

class TriangleFactory
: public Factory
{
public:
	Figure * create()
	{
		// load configuration file...
		// ....
		return new Triangle(3, 4, 5);
	}
};

void test0()
{
	//当前创建3个对象时，采用的数据是直接传入的
	//考虑一种情况：数据不能直接拿到, 需要通过配置文件读取

	unique_ptr<Factory> rectangleFac(new RectangleFactory());
	unique_ptr<Figure> rectangle(rectangleFac->create());


	unique_ptr<Factory> circleFac(new CircleFactory());
	unique_ptr<Figure> circle(circleFac->create());

	unique_ptr<Factory> triangleFac(new TriangleFactory());
	unique_ptr<Figure> triangle(triangleFac->create());

	display(rectangle.get());
	display(circle.get());
	display(triangle.get());
}

int main(int argc, char *argv[]) 
{
	test0();
	
	return 0;
}
