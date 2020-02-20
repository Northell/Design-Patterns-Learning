#include <iostream>
#include <string>

using namespace std;
/*��������� ����� ����������� ���, ��� ���� �������� � �������� ������*/
/*������������ �� ��������� �������, ������� ��������� � ���������� ������� ���� �� ������������ ����, ��� � ������� �����*/

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
	//��������� ���������� ��� ������ ���������� ����������.
	string Operation() const override {
		return this->component_->Operation();
	}
};
class ConcreteDecoratorA :public Decorator
{
	/*���������� ����� �������� ������������� ���������� ��������, ����� ������� ��������� 
	������ ��������. ����� ������ �������� ���������� ������� �����������.*/
public:
	ConcreteDecoratorA(Component* component) :Decorator(component) {

	}
	string Operation() const override {
		return "ConcreteDecoratorA(" + Decorator::Operation()+ ")\n";
	}
};

class ConcreteDecoratorB : public Decorator
{
	/*���������� ����� ��������� ���� ��������� �� ��� ����� ������ �������.*/
public:
	ConcreteDecoratorB(Component* component) :Decorator(component) {
	}
	string Operation() const override {
		return "ConcreteDecoratorB ("+Decorator::Operation() + ")\n";
	}
};

/*���������� ��� �������� �� ����� ��������� ����� ��������� ����������.
����� ������ �� �������� ����������� �� ���������� �������, � �������� �� �����*/
void ClientCode(Component* component)
{
	cout << "\nRESULT: " << component->Operation() << endl;
}
int main()
{
	/*����� �������, ���������� ��� ����� ������������ ��� ������� ����������(simple), ��� � �������������� (decorator1,2)*/
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