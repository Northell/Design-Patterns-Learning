#include <iostream>
#include <string>
using namespace std;

/* ����- ����������� �������, ������� ��������� ������-������ ��� ��������� ����� �� ��������� ��������, ������� ����� ����� ��������� �� �����������*/
/* �������� � �������� ��� ������������������ ����������, ��� ��������� ���������� ��, � ��� �� ��� ������������� ������� API*/

class Implementation // ������� ����� ���������
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


class Abstraction //������������� ��������� ��� ����������� ����� ���� �������� �������. 
				  //�������� ������ �� ������ �� �������� ���������� � ���������� ��� ��� ��������� ������
{
protected:
	Implementation* _implem;
public:
	Abstraction(Implementation* value) :_implem(value) {} //������ � ����������� � ���������� ������� ����������, � ����� ����������� � ���������� ������
	virtual ~Abstraction() {};
	virtual string Operation() const { return "Abstraction: Base operation with\n" + this->_implem->OperationDegradation(); }

};

class ExternedAbstraction:public Abstraction //����� ��������� ���������� ��� ��������� ������� ����������
{
public:
	ExternedAbstraction(Implementation*_implem) :Abstraction(_implem)
	{

	}
	string Operation() const override { return "ExtendedAbstraction: Extended operation with:\n"+ this->_implem->OperationDegradation(); }

};

void ClientCode(const Abstraction& abstract)	//���������� ���  ������ �������� �� ���������� �� ����������� ������������ ������� ���������� � ������������ �������� ���������� 
{												// ���������� ��� ������ �������� � ����� ������������������ ����������� ���������� � ����������
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