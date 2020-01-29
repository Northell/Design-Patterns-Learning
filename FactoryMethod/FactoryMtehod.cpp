
#include "pch.h"
#include <iostream>
#include <string>

using namespace std;
/* Реализация фабричного метода*/



/*Интерфейс Product объявляет операции, которые должы выполнять все 
конкректные продукты*/
class Product		//Шаг 1: Создаем интерфейс для фабричного метода
{
public:
	virtual ~Product() {};
	virtual string Operation() const = 0;

};




//========================================

/*Конкретные продукты представляют различные реализации интерфейса Product()*/
class ConcreteProduct1:public Product
{
public:
	string Operation() const override
	{
		return "Создан продукт номер 1";
	}
};


class ConcreteProduct2 :public Product
{
public:
	string Operation() const override
	{
		return "Создан продукт номер 2";
	}
};

//================================================


/*Создатель объявляет фабричный метод. который должен возвращать объект 
класса Product(). Подклассы создателя обычно предоставляют реализацию этого
метода.*/
class Creator
{
	/*!!!Создатель может также обеспечить реализацию фабричного метода 
	по умолчанию*/
public:
	virtual ~Creator() {};
	virtual Product* FactoryMethod() const = 0;

	/*!!! Несмотря на название, Создатель не создает продукт.
	Обычно там содержится базовая бизнес-логика, которая основана на объектах
	Product(), возвращаемых фабричным методм. Подклассы могут косвенно
	менять эту бизнес-логику, переопределяя фабричный метод и возвращая в него другой тип
	продукта.*/

	string SomeOperation() const
	{	//Вызывем фабричный метод, чтобы получить объект-продукт
		Product* product = this->FactoryMethod();
		//Далее работаем с этим продуктом:
		return  "Создатель: Один и тот же код, но через разные создатели: " 
		+ product->Operation();
	}
};

//===================


/*Конкретные создатели переопределяют тип возвращаемого продукта*/

class ConcreteCreator1 :public Creator
{
	/*!!! Сигнатура метода по-проежнему использует тип абстрактного продукта,
	хотя фактически из метода возвразается конкретный прдукт.
	Таким образом СОздатель может оставаться независимым от конкретных классов
	продутов.*/
public:
	Product* FactoryMethod() const override
	{
		return new ConcreteProduct1();
	}
};

class ConcreteCreator2 :public Creator
{
	/*!!! Сигнатура метода по-проежнему использует тип абстрактного продукта,
	хотя фактически из метода возвразается конкретный прдукт.
	Таким образом СОздатель может оставаться независимым от конкретных классов
	продутов.*/
public:
	Product* FactoryMethod() const override
	{
		return new ConcreteProduct2();
	}
};
//============================

/*Клиентский код работает с экземпляром конкретного создателя, хотя и через 
базовый интерфейс. Пока клиент продолжает работать с создателем через базовый
интерфейс, вы можете передать ему любой подкласс создателя.*/

void ClientCode(const Creator& creator)
{
	cout << "Клиент: я не знаю про классы создателя, но это работает\n"
		<< creator.SomeOperation() << endl;
}

/*Приложение выбирает тип создателя в зависимости от конфигурации или среды.*/
int main() 
{
	setlocale(LC_ALL, "rus");
	cout << "Приложение: Заупск с ConcreteCreator1.\n";
	Creator* creator = new ConcreteCreator1();
	ClientCode(*creator);
	cout << endl;

	cout << "Приложение: Заупск с ConcreteCreator2.\n";
	Creator* creator2 = new ConcreteCreator2();
	ClientCode(*creator2);
	cout << endl;

	delete creator;
	delete creator2;
	return 0;

}