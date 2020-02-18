#include <iostream>
#include <algorithm>
#include <string>
#include <list>

using namespace std;


/*����������� - ����������� �������, ��������� ��������� ������ �������� � �������� � ��� ��� ��, ��� � ��������� ��������*/
/*���������� �� ���� �������, ������� ������� ���������� ������, ������ - GUI */


class Component//��������� ��������� ����� �������� ��� ��� �������, ��� � ��� ������� ����������� 
{
protected:
	Component* _parent;
public:
	virtual ~Component() {};
	void SetParent(Component *parent) { this->_parent = parent; };

	Component *GetParent() const { return this->_parent; }

	/*������ ������� ���������� �������� ���������� ��������� � ����� ������ ����������, ����� �� ������������� ���������� ������ ����������� ����.*/
	virtual void Add(Component *component) {}
	virtual void Remove(Component* component) {}

	/*����� ������� �����, ������� �������� ����������� ���� ������, ����� �� ��������� ����� ��������� �������*/
	virtual bool IsComposite() const { return false; }

	/*������� ��������� ��� ����� ����������� ��������� ��������� �� ���������, 
	���� �������� ��� ���������� �������, ������� �����, ���������� ��������� �����������.*/

	virtual string Operation() const = 0;




};

class Leaf:public Component // leaf ������������ ����� �������� ������� ���������. �� ����� ����� ��������� �����������.
	//������ ������ ��������� ��� ������, ����� ��� ��������� �� ����������.
{
public:
	string Operation()const override { return "Yup"; }
};

class Composite : public Component // Composite �������� ������� ����������, ������� ����� ����� ��������� �������
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

	/* ��������� ��� ������ ��� ������, ������ ���� ����� � �������� ����������. 
	�.� ������� ���������� �������� ��� ������ ����� ��������, �� ������� ��� ������.*/
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

/*���������� ��� �������� �� ����� ������������ ����� ���������.*/
void ClientCode(Component* component)
{
	cout << "Result: " << component->Operation();
}


/*��������� ����, ��� �������� ���������� ��������� ��������� � ����������, ���������� ��� ����� �������� ��� � ��������, ��� � � �������� �����������.*/
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
	 * ...� ����� ������� ����������.
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