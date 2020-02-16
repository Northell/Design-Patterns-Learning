#include <iostream>
#include <string>
using namespace std;

/* Мост- структурынй паттерн, который разделяет бизнес-логику или отдельный класс на несколько иерархий, которые потом можно развивать по отдельности*/
/* Применим в основном для кроссплатформенных приложений, для поддержки нескольких бд, а так же при использовании разного API*/

class Implementation // создаем общий интерфейс
{
public:
	virtual ~Implementation() {};
	virtual string OperationDegradation() const = 0;

};

class ConcreteImpA:public Implementation
{

public:
	string OperationDegradation() const override
	{
		return "Call Operation A\n";
	}
};

class ConcreteImpB :public Implementation
{

public:
	string OperationDegradation() const override
	{
		return "Call Operation B\n";
	}
};


class Abstraction //Устанавливает интерфейс для управляющей части двух иерархий классов. 
				  //Содержит ссылку на объект из иерархии реализации и делегирует ему всю настоящую работу
{
protected:
	Implementation* _implem;
public:
	Abstraction(Implementation* value) :_implem(value) {} //Пихаем в конструктор с параметром обхекта реализации, и сразу присваиваем к реализации внутри
	virtual ~Abstraction() {};
	virtual string Operation() const { return "Abstraction: Base operation with\n" + this->_implem->OperationDegradation(); }

};

class ExternedAbstraction:public Abstraction //Можно расширить реализацию без изменения классов реализации
{
public:
	ExternedAbstraction(Implementation*_implem) :Abstraction(_implem)
	{

	}
	string Operation() const override { return "ExtendedAbstraction: Extended operation with:\n"+ this->_implem->OperationDegradation(); }

};

void ClientCode(const Abstraction& abstract)	//Клиентский код  должен зависеть от обстракции за исключением связывванием объекта абстракции с определенным объектом реализации 
{												// Клиентский код должен работать с любой сконфигурированной комьинацией реализации и абстракции
	cout << abstract.Operation();
}

int main()
{
	Implementation* _implem = new ConcreteImpA;
	Abstraction* abstract = new Abstraction(_implem);
	ClientCode(*abstract);

	delete abstract;
	delete _implem;


	Implementation* _implem1 = new ConcreteImpB;
	Abstraction* abstract1 = new ExternedAbstraction(_implem1);
	ClientCode(*abstract1);

	delete abstract1;
	delete _implem1;
	


	system("pause");
	return 0;
}