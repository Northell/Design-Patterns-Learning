#include <iostream>
#include <string>

/*������� - ������������� �������, ����������� ������������
������� �������� � ��������� �������*/

/*��� ��������� ����������� ���������� ������, ����������� �� �
�������, � ����� ������� ������� � ������ ������.*/



using namespace std;

class Command
{
	/*��������� ������� ��������� ����� ��� ���������� ������*/
public:
	virtual ~Command()
	{

	}
	virtual void Execute() const = 0;
	/*��������� ������� �������� ���������� ������� �������� �������������*/

};
class SimpleCommand : public Command
{
private:
	string pay_load_;
public: 
	explicit SimpleCommand(string pay_load) : pay_load_(pay_load) {}

	void Execute() const override
	{
		cout << "SimpleCommand: Seem I can do simple things like printing (" <<
			this->pay_load_ << ")\n";
	}
};

class Receiver
{
	/*������ ����������� �������� ����� ������ ������-������. ��� ����� ���������
	��� ���� ��������, ��������� � ����������� �������. ���������� ����� ����� 
	����� ��������� �����������.*/

public:
	void DoSomething(const string &a)
	{
		cout << "Receiver: Working on (" << a << ")\n";
	}

	void DoSomethingElse(const string &b)
	{
		cout << "Receiver: Also worting on (" << b << ")\n";
	}
};


class ComplexCommand : public Command
{
	/*�� ���� � �������, ������� ���������� ����� ������� ��������,
	��� ���������� �����������.*/
private:
	Receiver *rec_;
	string a_, b_; // ������ � ���������, ����������� ��� ������� ������� ����������
public:
	/*������� ������� ����� ��������� ���� ��� ��������� ��������-�����������
	������ � ������ ������� � ��������� ����� �����������*/
	ComplexCommand(Receiver *rec, string a, string b) :rec_(rec), a_(a), b_(b) {}

	void Execute() const override
	{
		cout << "ComplexCommand: Complex stuff shiold be done by a receiver object.\n";
		this->rec_->DoSomething(this->a_);
		this->rec_->DoSomethingElse(this->b_);
	}
};
	class Invoker
	{
		/*����������� ������ � ����� ��� ����������� ���������. �� ���������� ������ �������.*/
	private:
		Command *on_start_;
		Command *on_finish_;
	public:
		~Invoker() { delete on_start_, on_finish_; }

		void SetOnStart(Command *com)
		{
			this->on_start_ = com;
		}
		void SetOnFinish(Command *com)
		{
			this->on_finish_ = com;
		}

		void DoSomethingImportant() {
			/*����������� �� ������� �� ������� ���������� ������� � �����������.
			����������� �������� ������ ���������� ��������, �������� �������.*/
			cout << "Invoker: Does anybody want something done before I begin?\n";
			if (this->on_start_) {
				this->on_start_->Execute();
			}
			cout << "Invoker: ...doing something really important...\n";
			cout << "Invoker: Does anybody want something done before I finish?\n";
			if (this->on_finish_) {
				this->on_finish_->Execute();
			}
		}
	
};
void main()
{/*���������� ��� ����� ��������������� ����������� ������ ���������.*/
	Invoker *invoker = new Invoker;
	invoker->SetOnStart(new SimpleCommand("say Hi"));
	Receiver *rec = new Receiver;
	invoker->SetOnFinish(new ComplexCommand(rec, "Send email", "Save report"));
	invoker->DoSomethingImportant();

	delete invoker;
	delete rec;

	system("pause");
}