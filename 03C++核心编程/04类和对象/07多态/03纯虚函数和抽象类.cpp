#include<iostream>
using namespace std;

//纯虚函数和抽象类
class Base
{
public:
	virtual void func() = 0;  //纯虚函数（某个类只要有一个纯虚函数，这个类就称为抽象类）
	//抽象类特点：1. 无法实例化对象；2. 抽象类的子类必须重写父类中的纯虚函数，否则也属于抽象类
};

class Son:public Base
{
public:
	virtual void func() 
	{
		cout << "func函数的调用！" << endl;
	}
};

void test01()
{
	//Base b;  //错误，抽象类无法实例化对象
	//new Base;  //错误，抽象类无法实例化对象
	//Son s;  //子类必须重写父类中的纯虚函数，否则无法实例化对象

	Base *base = new Son;
	base->func();
}

int main()
{
	test01();

	system("pause");

	return 0;
}