#include <iostream>
#include <string>
#include <array>

using namespace std;

/*Посетитель - поведенческий паттерн, который позволяет добавить новую
операцию для целой иерархии классов, не изменяя код этих классов.
Посетитель нельзя заменить простой перегрузкой методов.

Встречается довольно редко из-за своей сложности и нюансов реализации.*/

class ConcreteComponentA;
class ConcreteComponentB;

class Visitor
{
	/*Интерфейс Посетителя объявляет набор метод посещени, соответствующих классам
	компонентов. Сигнатура метода посещения позволяет посетителю опредедлить
	конкретный класс компонента, с которым он имеет дело.*/
public:
	virtual void VisitConcreteComponentA(const ConcreteComponentA *element) const = 0;
	virtual void VisitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};

class Component
{
	/*Интерфейс Компонента объявляет метод accept, который в качестве аргумента
	может получать любой объект, реализующий интерфейс посетителя.*/
public:
	virtual ~Component() {}
	virtual void Accept(Visitor *visitor) const = 0;
};

class ConcreteComponentA : public Component
{
	/*Каждый конкретный Компонент должен реализовать метод acceot таким образом,
	чтобы он вызывал метод посетителя, соответствующий классу компонента.
	
	Мы вызываем visitConcreteComponentA, что соответствует названию текущего 
	класса. Таким образом мы позволяем посетителю узнать, с каким классом 
	компонента он работает.*/
public:
	void Accept(Visitor *visitor) const override {
		visitor->VisitConcreteComponentA(this);
	}
	/*Конкретные Компоненты могут иметь особые методы, не объявленные в их базовом классе
	или интерфейсе. Посетитель все же может использовать эти методы, поскольку
	он знает о конкретном классе компонента.*/
	string ExclusiveMethodOfConcreteComponentA() const { return "A"; }
};

class ConcreteComponentB :public Component 
{
	/*то же самое здесь: VisitorConcreteComponentB=>ConcreteComponentB */
public:
	void Accept(Visitor *visitor) const override
	{
		visitor->VisitConcreteComponentB(this);
	}
	string SpecialMethodOfConcreteComponentB() const {	return "B";	}
};
/*Конкретные посетители реализуют несколько версий одного и того же алгоритма, 
которые могут работать со всеми классами конкретных компонентов.

Максимальную выгоду от паттерна Посетитель вы почувствуете, испольлзуя его со сложной 
стректурй объектов, такой как дерево Компоновщика. В этом случае было бы полезно
хранить некоторое промежуточное состояние алгоритма при выполнении методов посетителя
над различными объектами струтуры.*/

class ConcreteVisitor1 :public Visitor {
public:
	void VisitConcreteComponentA(const ConcreteComponentA *elem) const override
	{
		cout << elem->ExclusiveMethodOfConcreteComponentA() << "+ ConcreteVisitor1\n";

	}
	void VisitConcreteComponentB(const ConcreteComponentB *element) const override
	{
		cout << element->SpecialMethodOfConcreteComponentB() << "+ ConcreteVisitor1\n";

	}
};
class ConcreteVisitor2 :public Visitor {
public:
	void VisitConcreteComponentA(const ConcreteComponentA *elem) const override
	{
		cout << elem->ExclusiveMethodOfConcreteComponentA() << "+ ConcreteVisitor2\n";

	}
	void VisitConcreteComponentB(const ConcreteComponentB *element) const override
	{
		cout << element->SpecialMethodOfConcreteComponentB() << "+ ConcreteVisitor2\n";

	}
};

/*КЛиентский код может выполнять операции посетителя над любым набором
элементов, не выясняя их конкретных классов. Операция принятия направляет вызов
к соответствующей операции в объекте посетителя.*/

void ClientCode(array<const Component *, 2> components, Visitor *visitor)

{
	for (const Component *comp:components)
	{
		comp->Accept(visitor);
	}
}
int main()
{
	array<const Component *, 2> components = { new ConcreteComponentA, new ConcreteComponentB };
	cout << "The client code works with all visitors via the base visitor interface:\n";
	ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
	ClientCode(components, visitor1);
	cout << "\n";
	cout << "It allows the same client code to work with different types of visitors:\n";
	ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
	ClientCode(components, visitor2);

	for (const Component *comp : components) {
		delete comp;
	}
	delete visitor1, visitor2;
	system("pause");
	return 0;
}