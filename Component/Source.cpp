#include <iostream>
#include <algorithm>
#include <string>
#include <list>

using namespace std;


/*Компоновщик - структурный паттерн, позволяет создавать дерево объектов и работать с ним так же, как с единичным объектом*/
/*Встречатся во всех задачах, которые требуют построения дерева, пример - GUI */


class Component//Компонент объявляет общие операции как для простых, так и для сложных компонентов 
{
protected:
	Component* _parent;
public:
	virtual ~Component() {};
	void SetParent(Component *parent) { this->_parent = parent; };

	Component *GetParent() const { return this->_parent; }

	/*Иногда полезно определить операции управления потомками в самом классе компонента, чтобы не предоставлять конкретные классы клиентскому коду.*/
	virtual void Add(Component *component) {}
	virtual void Remove(Component* component) {}

	/*Можно создать метод, который позволит клиентскому коду понять, может ли компонент иметь вложенные объекты*/
	virtual bool IsComposite() const { return false; }

	/*Базовый компонент сам может реализовать некоторое поведение по умолчанию, 
	либо поручить это конкретным классам, обхявив метод, содержащий поведение абстрактным.*/

	virtual string Operation() const = 0;




};

class Leaf:public Component // leaf представляет собой конечные объекты структуры. Не может иметь вложенных компонентов.
	//Обычно листья выполняют всю работу, тогда как компонент ее делегирует.
{
public:
	string Operation()const override { return "Yup"; }
};

class Composite : public Component // Composite содержит сложные компоненты, которые могут иметь вложенные объекты
{
protected:
	list<Component*> _children;

public:
	void Add(Component * component) override
	{
		this->_children.push_back(component);
		component->SetParent(this);

	}
	void Remove(Component* component) override
	{
		_children.remove(this);
		component->SetParent(nullptr);
	}
	bool IsComposite() const override {
		return true;
	}

	/* контейнер сам делает всю работУ, обходя всех детей и суммируя результаты. 
	т.к потомки контейнера передают эти вызовы своим потомкам, мы обходим все дерево.*/
	string Operation()const override { 
		string result;
		for (const Component * c : _children)
		{
			if (c == _children.back())
			{
				result += c->Operation();
			}
			else
			{
				result += c->Operation() + "+";
			}

		}
		return "Branch(" + result + ")\n";
	}

};

/*клиентский код работает со всеми компонентами через интерфейс.*/
void ClientCode(Component* component)
{
	cout << "Result: " << component->Operation();
}


/*Благодаря тому, что опреации управления потомками объявлены в компоненте, клиентский код может работать как с простыми, так и с сложными структурами.*/
void ClientCode2(Component *component1, Component *component2) {
	// ...
	if (component1->IsComposite()) {
		component1->Add(component2);
	}
	std::cout << "RESULT: " << component1->Operation();
	// ...
}

int main()
{
	Component *simple = new Leaf;
	std::cout << "Client: I've got a simple component:\n";
	ClientCode(simple);
	std::cout << "\n\n";
	/**
	 * ...а также сложные контейнеры.
	 */

	Component *tree = new Composite;
	Component *branch1 = new Composite;

	Component *leaf_1 = new Leaf;
	Component *leaf_2 = new Leaf;
	Component *leaf_3 = new Leaf;
	branch1->Add(leaf_1);
	branch1->Add(leaf_2);
	Component *branch2 = new Composite;
	branch2->Add(leaf_3);
	tree->Add(branch1);
	tree->Add(branch2);
	std::cout << "Client: Now I've got a composite tree:\n";
	ClientCode(tree);
	std::cout << "\n\n";

	std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
	ClientCode2(tree, simple);
	std::cout << "\n";

	delete simple;
	delete tree;
	delete branch1;
	delete branch2;
	delete leaf_1;
	delete leaf_2;
	delete leaf_3;

	system("pause");
	return 0;
}