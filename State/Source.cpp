#include <iostream>
#include<typeinfo>
#include<string>

using namespace std;


/*��������� - ��� ������������� �������, ����������� ����������� �������� ��������� �������
��� ����� ��� ���������.

���������, ��������� �� ���������, ���������� � ��������� ������. ��������������
����� ������ ������ �� ���� �� ����� ��������-��������� � ����������
��� ������.

��������� ��� ����������� � �������� ���������� �����-�����, ����������� ��
���������� switch*/

class Context;
class State
{
	/*������� ����� ��������� ��������� ������, ������� ������ ����������� ��� ����������
	���������, � ����� ������������� �������� ������ �� ������ ��������,
	��������� � ����������. ��� �������� ������ ����� �������������� �����������
	��� �������� ��������� ������� ���������.
	*/

protected:
	Context *cont_;

public:
	virtual ~State() {}
	void set_context (Context *cont)
	{
		this->cont_ = cont;
	}
	virtual void Handle1() = 0;
	virtual void Handle2() = 0;
};

class Context
{
	/*�������� ���������� ���������, �������������� ������� ��� ��������, �� ����� 
	������ ������ �� ���������� ��������� ���������, ������� ���������� 
	������� ��������� ���������.*/

private:
	State *state_;

public:
	Context(State *state) : state_(nullptr)
	{
		this->TransitionTo(state);
	}
	~Context() { delete state_; }
	void TransitionTo(State *state) {
		cout << "Context: Transition to " << typeid(*state).name() << "\n";
		if (this->state_ != nullptr)
			delete this->state_;
		this->state_ = state;
		this->state_->set_context(this);
	}
	void Request1() {
		this->state_->Handle1();

	}
	void Request2() { this->state_->Handle2(); }
};

class ConcreteStateA :public State
{
public:
	void Handle1() override;
	void Handle2() override
	{
		cout << "ConcreteStateA handles request2.\n";
	}
};

class ConcreteStateB :public State
{
public:
	void Handle1() override
	{
		cout << "ConcreteStateB handles request1.\n";
	};
	void Handle2() override
	{
		cout << "ConcreteStateB handles request2.\n";
		cout << "ConcreteStateB wants to change the state of the context.\n";
		this->cont_->TransitionTo(new ConcreteStateA);
	
	}
};

void ConcreteStateA ::  Handle1(){
	cout << "ConcreteStateeA handles request1.\n";
	cout << "ConcreteStateA wants to change the state of the context.\n";
	this->cont_->TransitionTo(new ConcreteStateB);
}

void ClientCode()
{
	Context *cont = new Context(new ConcreteStateA);
	cont->Request1();
	cont->Request2();
	delete cont;
}
int main()
{
	ClientCode();
	system("pause");
	return 0;
}