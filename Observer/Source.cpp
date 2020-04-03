#include <iostream>
#include <list>
#include <string>

/*����������� - ������������� �������, ������� ��������� �������� ��������� 
������ ������� �� ���������� ������ ���������. ��� ���� ����������� ����� 
�������� ������������� � ������������ �� ���� ����������.

����������� ��� ��� ����������� ���������� ������ ��������� ����� ������������.
����������� ��������� ��������� ����������� ����������� �� �������, �������������
� ������ �����������.

����������� ����� ���������� �� ��������� �������� � ������� ����������, �������
�������� ���������� ���������.*/

using namespace std;

class IObserver
{
	/*������� �������� ��������, ����������� ����� �������� ������� � �����������
	�� �������, ������������ � ������ ��������*/

public:
	virtual ~IObserver() {};
	virtual void Update(const string &message_from_subject) = 0;
};

class ISubject
{
public:
	virtual ~ISubject() {};
	virtual void Attach(IObserver *observer) = 0;
	virtual void Detach(IObserver *observer) = 0;
	virtual void Notify() = 0;
};

class Subject :public ISubject
{
	/*�������� ������� ��������� ������ ����������
	� ��������� ������������ � ��� ����������*/
public:
	virtual ~Subject()
	{
		cout << "Goodbye, I was the Subject.\n";
	}

	//������ ��������� ���������.

	void Attach(IObserver *observer) override
	{
		list_observer_.push_back(observer);
	}
	void Detach(IObserver *observer) override
	{
		list_observer_.remove(observer);
	}
	void Notify() override
	{
		list<IObserver *>::iterator iterator = list_observer_.begin();
		HowManyObserver();
		while (iterator != list_observer_.end())
		{
			(*iterator)->Update(message_);
			++iterator;
		}

	}
	void CreateMessage(string message = "Empty")
	{
		this->message_ = message;
		Notify();
	}
	void HowManyObserver()
	{
		cout << "There are " << list_observer_.size() << " observers in the list.\n";
	}
	/*������ ������ �������� - ������ ����� ����, ��� ������ ��������. ��������
	����� �������� ��������� ������ ������-������, ������� ��������� �����
	����������� ������� ���, ����� ������ ��������� ���-�� ������(��� ����� �����)*/
	void SomeBusinessLogic()
	{
		this->message_ = "change message message";
		Notify();
		cout << "I'm anout to do some thing importamt\n";
	}
private:
	list<IObserver *> list_observer_;
	string message_;
};

class Observer :public IObserver
{
public:
	Observer(Subject &subject) : subject_(subject)
	{
		this->subject_.Attach(this);
			cout << "Hi, I'm the observer \""<< ++Observer::static_number_ << "\".\n";
			this->number_ = Observer::static_number_;
	}
	virtual ~Observer()
	{
		cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
	}

	void Update(const string &message_from_subject) override
	{
		message_from_subject_ = message_from_subject;
		PrintInfo();
	}
	void RemoveFromTheList()
	{
		subject_.Detach(this);
		cout << "Observer\"" << number_ << "\" removed from the list.\n";
	}

	void PrintInfo()
	{
		cout << "Observer \"" << this->number_ << "\" removed from the list.\n";
	}

private:
	string message_from_subject_;
	Subject &subject_;
	static int static_number_;
	int number_;
};

int Observer::static_number_ = 0;

void ClientCode()
{
	Subject *sub = new Subject;
	Observer *observ1 = new Observer(*sub);
	Observer *observ2 = new Observer(*sub);
	Observer *observ3 = new Observer(*sub);
	Observer *observ4;
	Observer *observ5;

	sub->CreateMessage("Hello World!)");
	observ3->RemoveFromTheList();

	sub->CreateMessage("The weather is not today!");
	observ4 = new Observer(*sub);
	observ2->RemoveFromTheList();
	observ5 = new Observer(*sub);
	sub->CreateMessage("My new car is great! ;)");
	observ5->RemoveFromTheList();
	observ4->RemoveFromTheList();
	observ1->RemoveFromTheList();

	delete observ1, observ2, observ3, observ4, observ5, sub;

}
int main()
{
	ClientCode();
	system("pause");
	return 0;
}