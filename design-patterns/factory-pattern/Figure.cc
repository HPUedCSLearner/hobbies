 ///
 /// @file    Figure.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-28 14:31:43
 ///

// 课代表
//静态工厂方法
//
//缺点: 1. 不满足开闭原则
//		2. 不满足单一职责原则

#include <math.h>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class Figure
{
public:
	virtual void display() const = 0;
	virtual double area() = 0;

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

void display(Figure * fig)
{
	fig->display();
	cout << "的面积是:" << fig->area() << endl;
}



//静态工厂方法
//
//缺点: 1. 不满足开闭原则
//		2. 不满足单一职责原则
class Factory
{
public:
	static Figure * createRectangle()
	{
		// txt  xml  json(可视化)
		// load configuration file...
		// ....
		return new Rectangle(10, 20);
	}

	static Figure * createCircle()
	{
		// load configuration file...
		// ....
		return new Circle(10);
	}

	static Figure * createTriangle()
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
	//

	// load configuration file...
	// ....
	unique_ptr<Figure> rectangle(Factory::createRectangle());
	unique_ptr<Figure> circle(Factory::createCircle());
	unique_ptr<Figure> triangle(Factory::createTriangle());

	display(rectangle.get());
	display(circle.get());
	display(triangle.get());
}

int main(int argc, char *argv[]) 
{
	test0();
	
	return 0;
}
