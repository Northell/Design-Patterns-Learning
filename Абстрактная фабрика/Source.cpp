#include <iostream>
#include <string>
using namespace std;

class AbstractProductA
{
public:
	virtual int check() const = 0;
};

class ConcreteProductA1 :public AbstractProductA
{
public:
	int check() const override
	{
		return 1;
	}
};

class ConcreteProductA2 :public AbstractProductA
{
public:
	int check()	const override
	{
		return 2;
	}
};


class AbstractProductB
{
public:
	virtual string check() const = 0;
};

class ConcreteProductB1 :public AbstractProductB
{
public:
	string check() const override
	{
		return "This ConcreteProductB1";
	}
};

class ConcreteProductB2 :public AbstractProductB
{
public:

	string check() const override
	{
		return "This ConcreteProductB2";
	}
};

class AbstractFactory
{
public:
	virtual AbstractProductA* CreateProductA() const= 0;
	virtual AbstractProductB* CreateProductB()const  = 0;

};

class ConcreteFactory1 :public AbstractFactory
{
public:
	AbstractProductA *CreateProductA() const override
	{
		return new ConcreteProductA1();
	}
	AbstractProductB *CreateProductB() const override
	{
		return new ConcreteProductB1();
	}
};


class ConcreteFactory2 :public AbstractFactory
{
public:
	AbstractProductA *CreateProductA() const override
	{
		return new ConcreteProductA2();
	}
	AbstractProductB *CreateProductB() const override
	{
		return new ConcreteProductB2();
	}
};

void ClientCode(AbstractFactory &Fact)
{
	const AbstractProductA *pA = Fact.CreateProductA();
	const AbstractProductB *pB = Fact.CreateProductB();

	cout << pA->check() << endl << pB->check() << endl;
	delete pA, pB;
}
int main()
{
	std::cout << "Client: Testing client code with the first factory type:\n";
	ConcreteFactory1 *f1 = new ConcreteFactory1();
	ClientCode(*f1);
	delete f1;
	std::cout << std::endl;
	std::cout << "Client: Testing the same client code with the second factory type:\n";
	ConcreteFactory2 *f2 = new ConcreteFactory2();
	ClientCode(*f2);
	delete f2;
	return 0;
}
