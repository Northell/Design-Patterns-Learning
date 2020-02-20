#include <iostream>
#include <string>

using namespace std;
/*Декоратор часто встречается там, где надо работать с потоками данных*/
/*Распознается по создающим методам, которые принимают в параметрах объекты того же абстрактного типа, что и текущий класс*/

class Component
{
public:
	virtual ~Component() {}
	virtual string Operation() const = 0;
};

class ConcreteComponent :public Component
{
public:
	string Operation() const override
	{
		return "Concrete Component ";
	}
};

class Decorator : public Component {
protected:
	Component* component_;
public:
	Decorator(Component* component) :component_(component)
	{

	}
	//Декоратор делегирует всю работу обернутому компоненту.
	string Operation() const override {
		return this->component_->Operation();
	}
};
class ConcreteDecoratorA :public Decorator
{
	/*Декораторы могут вызывать рродительскую реализацию операции, чтобы вызвать обернутый 
	объект напрямую. Такой подход упрощает расширение классов декораторов.*/
public:
	ConcreteDecoratorA(Component* component) :Decorator(component) {

	}
	string Operation() const override {
		return "ConcreteDecoratorA(" + Decorator::Operation()+ ")\n";
	}
};

class ConcreteDecoratorB : public Decorator
{
	/*Декораторы могут выполнять свое поведение до или после вызова объекта.*/
public:
	ConcreteDecoratorB(Component* component) :Decorator(component) {
	}
	string Operation() const override {
		return "ConcreteDecoratorB ("+Decorator::Operation() + ")\n";
	}
};

/*Клиантский код работает со всеми объектами через интерфейс Компонента.
Таким оразом он остается независимым от конкретных классов, с которыми он робит*/
void ClientCode(Component* component)
{
	cout << "\nRESULT: " << component->Operation() << endl;
}
int main()
{
	/*Таким образом, клиентский код может поддерживать как простые компоненты(simple), так и декорированные (decorator1,2)*/
	Component *simple = new ConcreteComponent;
	cout << "Client: I'be got a simple component:\n";
	ClientCode(simple);
	cout << endl << endl;
	

	Component* decorator1 = new ConcreteDecoratorA(simple);
	Component* decorator2 = new ConcreteDecoratorB(decorator1);

	cout << "Client: Now I've got a decorated component ";
	ClientCode(decorator2);
	cout << endl;



	delete simple;
	delete decorator1;
	delete decorator2;

	system("pause");
	return 0;

}