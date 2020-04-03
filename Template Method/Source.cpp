#include <iostream>
#include <string>

using namespace std;
/*Шаблонный метод - поведенческий паттерн, задающий скелет алгоритма в суперклассе
и заставляющий подклассы реализовать конкретные шаги этого алгоритма.

Встречаются во многих библиотечных классах С++. Разработчики создают их, чтобы
позволить клиентам легко и быстро расширять стандартный код при помощи 
наследования.*/

class AbstractClass
{
	/*Абстрактный класс определяет шаблонный метод, содержащий скелет некоторого
	алгоритма, состоящего из вызовов (обычно) абстрактных примитивных операций.
	
	Конкретные подклассы должны реализовать эти операции, но оставить сам 
	шаблонный метод без изменений.*/

public:
	void TemplateMethod() const
	{
		this->BaseOperation1();
		this->RequiredOperations1();
		this->BaseOperation2();
		this->Hook1();
		this->RequiredOperations2();
		this->BaseOperation2();
		this->Hook2();
	}
protected:
	//Эти операции уже имеют реализации
	void BaseOperation1() const
	{
		cout << "AbstractClass says: I am doing the bulk of the work\n";

	}
	void BaseOperation2() const
	{
		cout << "AbstractClass says: But I let subclasses override some operations\n"; 
	}
	void BaseOperation3() const
	{

		cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
	}
	//Эти операции должны быть реализованы в подклассах
	virtual void RequiredOperations1() const = 0;
	virtual void RequiredOperations2() const = 0;

	/*Это хуки. Подклассы переопределять их, но это не обязательно, поскольку
	у хуков уже есть стандартная(но пустая) реализация. Хуки предоставляют
	дополнительные точки расширения в некоторых критических местах алгоритма.*/
	virtual void Hook1() const {}
	virtual void Hook2() const {}

};

class ConcreteClass1 : public AbstractClass
{
	/*Конкретные классы должны реализовать все абстрактные операции базового класса.
	они также могут переопределить некоторые операции с реализацией по умолчанию.*/
protected:
	void RequiredOperations1() const override
	{
		cout << "ConcreteClass1 says: Implemented Operation1\n";
	}
	void RequiredOperations2() const override
	{
		cout << "ConcreteClass1 says: Implemented Operation2\n";
	}
};

class ConcreteClass2 : public AbstractClass
{
	/*Обычно конкретные классы переопределяют только часть
	операций базового класса.*/
protected:
	void RequiredOperations1() const override
	{
		cout << "ConcreteClass2 says: Implemented Operation1\n";


}
	void RequiredOperations2() const override
	{
		cout << "ConcreteClass2 says: Implemented Operation2\n";

}
	void Hook1() const override
	{
		cout << "ConcreteeClass2 says: Overridden Hook1\n";
	}

};

/*Клиентский код вызывает шаблонный метод для выполнения алгоритма. Клиентский
код не должен знать конкретный класс объекта, с которым работает, при условии,
что он работает с объектами через интерфейс их базового класса.*/

void ClientCode(AbstractClass *class_)
{
	class_->TemplateMethod();
}
int main()
{
	cout << "Same cliennt code can work with different subclasses:\n";
	ConcreteClass1 *Class1 = new ConcreteClass1;
	ClientCode(Class1);
	cout << "\n";
	cout << "Same client code can work with different subclasses:\n";
	ConcreteClass2 *Class2 = new ConcreteClass2;
	ClientCode(Class2);

	delete Class1, Class2;
	system("pause");
	return 0;
}