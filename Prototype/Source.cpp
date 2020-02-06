#include <iostream>
#include <string>
#include <unordered_map>


using namespace std;

enum Type {
	PROTOTYPE_1 = 0,
	PROTOTYPE_2
};

class Prototype		//Общий интерфейс прототипов
{
	string prototype_name;
	float prototype_field;

public:
	Prototype() {};
	Prototype(string prototype_name) :prototype_name(prototype_name) {};
	virtual ~Prototype() {};
	virtual Prototype* Clone() const = 0;
	virtual void Method(float field) {
		prototype_field = field;
		cout << "Call method from " << prototype_name << " " << endl;
	}
};


class ConcretePrototype1 :public Prototype //конкретный прототип
{
private:
	float concrete_prototype_field1_;
public:
	ConcretePrototype1(string prototype_name,
		float concrete_prototype_field)
		:Prototype(prototype_name),
		concrete_prototype_field1_(concrete_prototype_field) {}


	Prototype *Clone() const override { return new ConcretePrototype1(*this); }
};


class ConcretePrototype2 :public Prototype
{
private:
	float concrete_prototype_field2_;
public:
	ConcretePrototype2(string prototype_name,
		float concrete_prototype_field)
		:Prototype(prototype_name),
		concrete_prototype_field2_(concrete_prototype_field) {}


	Prototype *Clone() const override { return new ConcretePrototype2(*this); }
};

class PrototypeFactory
{
private:
	unordered_map<Type, Prototype *, hash<int>> prototypes_;
public:
	PrototypeFactory() {
		prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1", 50.f);
		prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2", 60.f);

	}
	~PrototypeFactory() {
		delete prototypes_[Type::PROTOTYPE_1];
		delete prototypes_[Type::PROTOTYPE_2];

	}
	Prototype *CreatePrototype(Type type)
	{
		return prototypes_[type]->Clone();
	}

};

	void Client(PrototypeFactory &prototype_factory)
	{
		cout << "Let's create a Prototype 1\n";
		Prototype *prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
		prototype->Method(90);
		delete prototype;

		cout << "\n Let's create a Prototype 2\n";
		prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
		prototype->Method(10);
		delete prototype;
	}
int main()
{
	PrototypeFactory * prototype_factory = new PrototypeFactory();
	Client(*prototype_factory);
	delete prototype_factory;


	system("pause");
	return 0;
}