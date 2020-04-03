#include <iostream>
#include <string>

using namespace std;
/* ����������� - ��� ������, ������� ���������� ���������� ����� �������� 
� �������� ��������� ��������. �� �������� ������ �� �������, ��������� ����
������� (�������� �������, ����������� � ������), � ����� �������� ����� 
���������� �������. ����� ��� �� ��������� ��� � �������� ������, ������� ��� 
������� ��� ������� - �������� ����� ����������� ��� ��������.

����������� �����, ����� ���� �������� ��������� ��� �������� ��������� ������. 
��� �������� ��������� �����-���� ���������� ��������� �� � ����� ��������� ���������
���������� �������. ���� ����� ���������� ��� ��������� ������ ������ ��������� �������.
���������� ����� ���� ������ �� ��������� ������ ������ �������.*/


class Subject
{
	/*��������� �������� �������� ����� �������� ��� ��� ��������� ��������,
	��� � ��� �����������. */
public: 
	virtual void Request() const = 0;
};


class RealSubject : public Subject
{
	/*�������� ������� �������� ��������� ������� ������ ������.*/
public:

	void Request() const override
	{
		cout << "RealSubject: Handing reauest\n";
	}
};

class Proxy :public Subject
{
private: 
	RealSubject *real_sub_;
	bool CheckAccess() const
	{
		//��������� �������� �������� ������ ��������� �����.

		cout << "Proxy: Checking access prior to firing a real request.\n";
		return true;
	}
	void LogAccess() const
	{
		cout <<" Proxy: Logging the time of request.\n";

	}
public:
	/*����������� ������ ������ �� ������ ������ �����������. ������ ����� 
	���� ������ ��������� ���, ���� �������� ����������.*/
	Proxy(RealSubject * real_subject) :real_sub_(new RealSubject(*real_subject)) {}

	~Proxy() {
		delete real_sub_;
	}

	void Request() const override
	{
		if (this->CheckAccess())
		{
			this->real_sub_->Request();
			this->LogAccess();
		}
	}
};

/*���������� ��� ������ �������� �� ����� ��������� ����� ��������� ��������*/

void ClientCode(const Subject &sub)
{
	sub.Request();
}
void main()
{
	cout << "Client: Executing the client code with a real subject: \n";
	RealSubject *realsub = new RealSubject;
	ClientCode(*realsub);
	cout << "\n";
	cout << "Client: Executing the client code with a proxy: \n";
	Proxy *proxy = new Proxy(realsub);
	ClientCode(*proxy);
	delete realsub;
	delete proxy;
	
	system("pause");
}