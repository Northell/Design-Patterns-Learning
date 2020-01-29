
#include "pch.h"
#include <iostream>
#include <string>

using namespace std;
/* ���������� ���������� ������*/



/*��������� Product ��������� ��������, ������� ����� ��������� ��� 
����������� ��������*/
class Product		//��� 1: ������� ��������� ��� ���������� ������
{
public:
	virtual ~Product() {};
	virtual string Operation() const = 0;

};




//========================================

/*���������� �������� ������������ ��������� ���������� ���������� Product()*/
class ConcreteProduct1:public Product
{
public:
	string Operation() const override
	{
		return "������ ������� ����� 1";
	}
};


class ConcreteProduct2 :public Product
{
public:
	string Operation() const override
	{
		return "������ ������� ����� 2";
	}
};

//================================================


/*��������� ��������� ��������� �����. ������� ������ ���������� ������ 
������ Product(). ��������� ��������� ������ ������������� ���������� �����
������.*/
class Creator
{
	/*!!!��������� ����� ����� ���������� ���������� ���������� ������ 
	�� ���������*/
public:
	virtual ~Creator() {};
	virtual Product* FactoryMethod() const = 0;

	/*!!! �������� �� ��������, ��������� �� ������� �������.
	������ ��� ���������� ������� ������-������, ������� �������� �� ��������
	Product(), ������������ ��������� ������. ��������� ����� ��������
	������ ��� ������-������, ������������� ��������� ����� � ��������� � ���� ������ ���
	��������.*/

	string SomeOperation() const
	{	//������� ��������� �����, ����� �������� ������-�������
		Product* product = this->FactoryMethod();
		//����� �������� � ���� ���������:
		return  "���������: ���� � ��� �� ���, �� ����� ������ ���������: " 
		+ product->Operation();
	}
};

//===================


/*���������� ��������� �������������� ��� ������������� ��������*/

class ConcreteCreator1 :public Creator
{
	/*!!! ��������� ������ ��-��������� ���������� ��� ������������ ��������,
	���� ���������� �� ������ ������������ ���������� ������.
	����� ������� ��������� ����� ���������� ����������� �� ���������� �������
	��������.*/
public:
	Product* FactoryMethod() const override
	{
		return new ConcreteProduct1();
	}
};

class ConcreteCreator2 :public Creator
{
	/*!!! ��������� ������ ��-��������� ���������� ��� ������������ ��������,
	���� ���������� �� ������ ������������ ���������� ������.
	����� ������� ��������� ����� ���������� ����������� �� ���������� �������
	��������.*/
public:
	Product* FactoryMethod() const override
	{
		return new ConcreteProduct2();
	}
};
//============================

/*���������� ��� �������� � ����������� ����������� ���������, ���� � ����� 
������� ���������. ���� ������ ���������� �������� � ���������� ����� �������
���������, �� ������ �������� ��� ����� �������� ���������.*/

void ClientCode(const Creator& creator)
{
	cout << "������: � �� ���� ��� ������ ���������, �� ��� ��������\n"
		<< creator.SomeOperation() << endl;
}

/*���������� �������� ��� ��������� � ����������� �� ������������ ��� �����.*/
int main() 
{
	setlocale(LC_ALL, "rus");
	cout << "����������: ������ � ConcreteCreator1.\n";
	Creator* creator = new ConcreteCreator1();
	ClientCode(*creator);
	cout << endl;

	cout << "����������: ������ � ConcreteCreator2.\n";
	Creator* creator2 = new ConcreteCreator2();
	ClientCode(*creator2);
	cout << endl;

	delete creator;
	delete creator2;
	return 0;

}