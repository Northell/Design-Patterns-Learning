#include <iostream>
#include <string>

using namespace std;

class Target				//Целевой класс объявляет интерфейс, с которым может работать клиентский код
{
public:
	virtual ~Target() = default;
	virtual string Request() const
	{
		return "Target: the default target's behavior\n";
	}
	

};

class Adaptee			//Адаптируемый класс(Содержит некоторое полезное поведение, но его интерфейс несовместим с клиентским кодом)
{

public:
	string SpecigicRequest() const
	{
		return "\n.eetpadA eht fo roivaheb laicepS";
	}

};

class Adapter : public Target		//Адаптер позволяет совместить несовмещаемое
{
	Adaptee *_adaptee;
public:
	Adapter(Adaptee *_adaptee) { _adaptee = this->_adaptee; };
	string Request() const override {
		string to_reverse = this->_adaptee->SpecigicRequest();
		reverse(to_reverse.begin(), to_reverse.end());
		return "Adapter: (TRANSLATED) " + to_reverse;
	}
};

void ClientCode(const Target * target )  //Клиентский код поддерживает все классы, испольлзующие целевой интерфейс
{
	cout << target->Request();
}

int main()
{
	cout << "Client: I can work just fine with the Target objects\n";
	Target *target = new Target();
	ClientCode(target);
	cout << "\n\n";
	Adaptee *adaptee = new Adaptee();
	cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
	cout << "Adaptee: " << adaptee->SpecigicRequest() << endl << endl;
	cout << "Client: But I can work with it via the Adapter:\n";
	Adapter *adapter = new Adapter(adaptee);
	ClientCode(adapter);
	cout << "\n";

	delete adapter;
	delete adaptee;
	delete target;
	system("pause");
	return 0;
}