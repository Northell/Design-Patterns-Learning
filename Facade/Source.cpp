#include<iostream>
#include <string>
using namespace std;

/*����� ����� ����������� � ���������� �����������, � ������ ������� �������� 
�� �������� ������������ ��� API*/
/*����� ����������� � ������, ������� ����� ������� ���������, �� ����������
�������� ����� ������ ������ �������. ���� ����� ������ ���� ������ �� ���������
������ ��������� ������� �������.*/

class SubSystem1
{
public:
	string Operation1() const {
		return "SubSystem1: Ready!\n";
	}
	string OperationN() const {
		return "SubSistem1: Go!\n";
	}

};

/*��������� ������ ����� �������� � ������� ��������� ������������*/
class SubSystem2
{
public:
	string Operation1() const {
		return "SubSystem2: Get Ready!\n";
	}
	string OperationZ() const {
		return "SubSistem1: Fire!\n";
	}

}; 

class Facade {
	/*����� ������ ������������� ������� ��������� ��� ������� ������ ����� �� ����������� ���������.
	�� ���������� ������� �������� ��������������� ��������� ������ ����������. ����� �������� �� ���������� ��������� ������.
	��� ��� �������� ������� �� ������������ ��������� ����������.*/
protected:
	SubSystem1* subsystem1_;
	SubSystem2* subsystem2_;

	/*������ ����� ������������ ������������ ������� ����������
	��� ��������� ������� �� ��������������*/
public:
	Facade(
		SubSystem1 *subsystem1 = nullptr, SubSystem2* subsystem2 = nullptr)
	{
		if (subsystem1 == nullptr)

			this->subsystem1_ = new SubSystem1;
		else
			this->subsystem1_ = subsystem1;
		
		
		if (subsystem2 == nullptr)

			this->subsystem2_ = new SubSystem2;
		else
			this->subsystem2_ = subsystem2;
		
	}

	~Facade() { delete subsystem1_, subsystem2_; }
	/*������ ������ ������ ��� �������� ������� � ������� ����������������
	���������. ������ ������� �������� ������ ����� ������������ ����������.*/
	string Operation()
	{
		string result = "Facade initializes subsystems:\n";
		result += this->subsystem1_->Operation1();
		result += this->subsystem2_->Operation1();
		result += "Facade orders subsystems to perform the action:\n";
		result += this->subsystem1_->OperationN();
		result += this->subsystem2_->OperationZ();
		return result;
	}



};

/*���������� ��� �������� �� �������� ������������ ����� ������� ��������� ������*/
void ClientCode(Facade *facade)
{
	cout << facade->Operation();
}

int main()
{
	SubSystem1 * subsystem1 = new SubSystem1;
	SubSystem2 *subsystem2 = new SubSystem2;
	Facade *facade = new Facade(subsystem1, subsystem2);
	ClientCode(facade);
	delete facade;

	
	system("pause");
	return 0;
}