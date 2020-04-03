#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;
/*������ - ������������� �������, ����������� ������ ������ ����������� ���������
��������, � ����� ��������������� ��. ��� ���� ������ �� ���������� 
������������ ���������� ��������, � ������ �� ����� ������� � ���������� ����������
�������.*/

/*��������� ���� ����� � ������� ������������. �� ��� �� ������������, �� � �� 
����� ����������� ����� ���������� �������� �� ����� ���������� ���������.*/
class Memento
{
	/*��������� ������ ������������� ������ ���������� ���������� ������, ����� ���
	���� �������� ��� ��������. ������� �� �� ���������� ��������� ���������*/
public:
	virtual string GetName() const = 0;
	virtual string date() const = 0;
	virtual string state() const = 0;
};

class ConcreteMemento : public Memento {
	/*���������� ������ �������� �������������� ��� �������� ��������� ���������*/
private: 
	string state_;
	string date_;

public:
	ConcreteMemento(string state) : state_(state)
	{
		this->state_ = state;
		time_t now = time(NULL);
		this->date_ = ctime(&now);
	}
	/*��������� ����������� ���� �����, ����� ��������������� ���� ���������.*/
	string state() const override
	{
		return this->state_;
	}
	/*��������� ������ ������������ �������� ��� ����������� ����������*/

	string GetName() const override
	{
		return this->date_ + "/" + this->state_.substr(0, 9) + "...}";;
	}
	string date() const override {
		return this->date_;
	}
};

class Originator
{
	/*��������� �������� ��������� ������ ���������, ������� ����� �� �������� 
	��������. �� ����� ��������� ����� ���������� ��������� ������ ������ � �����
	�������������� ��������� �� ����.*/
private:
	string state_;
	string GenerateRandomString(int length = 10)
	{
		const char alpjanum[] = "0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		int stringLength = sizeof(alpjanum) - 1;
		string random_string;
		for (int i = 0; i < length; i++)
		{
			random_string += alpjanum[rand() % stringLength];
		}
		return random_string;
	}

	public:
		Originator(string state) : state_(state)
		{
			cout << "Originator : My initial state is " << this->state_ << "\n";

		}
		/*������-������ ��������� ����� �������� �� ��� ���������� ���������.
		������� ������ ������ ��������� ��������� ����������� ��������� � �������
		������ save ����� �������� ������� ������-������.*/

		void DoSomething()
		{
			cout << "Originator: I'm doing something important.\n";
			this->state_ = this->GenerateRandomString(30);
			cout << "Originator: and my state has changed to: " << this->state_ << "\n";
		}

		/*��������� ������� ��������� ������ ������
		*/
		Memento *Save()
		{
			return new ConcreteMemento(this->state_);
		}
		/*��������������� ��������� ��������� �� ������� ������
	*/
	
		void Restore(Memento *memento) {
			this->state_ = memento->state();
			cout << "Originator: My state has changed to: " << this->state_ << "\n";
		}

};
class Caretaker
{		/*������ �� ������� �� ������ ����������� ������. ����� �������,
		�� �� ����� ������� � ��������� ���������, ����������� ������ ������.
		�� �������� �� ����� �������� ����� ������� ��������� ������.*/

private:
	vector<Memento *> mementos_;

	Originator *originator_;

public:
	Caretaker(Originator *originator) : originator_(originator)
	{
		this->originator_ = originator;
	}
	void Backup()
	{
		cout << "\nCaretaker: Saving Originator's state... \n";
		this->mementos_.push_back(this->originator_->Save());
	}
	void Undo() {
		if(!this->mementos_.size())
		{
			return;
		}
		Memento *memento = this->mementos_.back();
		this->mementos_.pop_back();
		cout << "Caretaker: Restoring state to: " << memento->GetName() << "\n";
		try {
			this->originator_->Restore(memento);
		}
		catch(...)
		{
			this->Undo();
		}
	}
	void ShowHistory() const
	{
		cout << "Caretaker: Here's the list of mementos:\n";
		for (Memento *memento : this->mementos_) {
			cout << memento->GetName() << "\n";
		}
	}


};

void ClientCode()
{
	Originator *origin = new Originator("Super-duper-super-puper-super");
	Caretaker *caretaker = new Caretaker(origin);
	caretaker->Backup();
	origin->DoSomething();
	
	caretaker->Backup();
	origin->DoSomething();

	caretaker->Backup();
	origin->DoSomething();

	cout << "\nClient: Now, let's rollback!\n\n";
	caretaker->Undo();
	cout << "\nClient: Once more!\n\n";
	caretaker->Undo();
	delete origin, caretaker;
	
}
void main()
{
	srand(static_cast<unsigned int> (time(NULL)));
	ClientCode();
	system("pause");
}