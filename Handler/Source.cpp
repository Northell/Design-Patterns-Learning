#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*������� ������������ - ������������� �������, ������� �������� ������ �� �������
������������� ������������, ���� ���-������ �� ���������� ������

��������� �� ������� �������� ����������� ������� � ��� ����������, ��������
����������� ���� �� ��������� ������������ �����������

����������� �����, �.� ��� ���������� ����� ������� ������*/

class
	Handler
{
	/*��������� ����������� ��������� ����� ���������� ������� ������������. ��
	����� ��������� ����� ��� ���������� �������.*/
public: 
	virtual Handler *SetNext(Handler *handler) = 0;
	virtual string Handle(string request) = 0;
};

class AbstractHandler : public Handler
{
	/*��������� ������� �� ��������� ����� ���� ����������� ������ �����������.*/

private:
	Handler *next_handler_;

public:
	AbstractHandler() : next_handler_(nullptr) {}

	Handler *SetNext(Handler *handler) override
	{
		this->next_handler_ = handler;
		/*������� ����������� ������ �������� ������� �����������
		������� �������� ��� ���:
		$monkey->setNext($squirrel)->setNext($dog);*/
		return handler;
	}


	string Handle(string request) override {
		if (this->next_handler_)
		{
			return this->next_handler_->Handle(request);
		}
		return {};
	}
};
	/*��� ���������� ����������� ���� ������������ ������, ���� �������� ��� ��.*/
	class MonkeyHandler : public AbstractHandler {
	public:
		string Handle(string request) override {
			if (request == "Banana") {
				return "Monkey: I'll eat the " + request + ".\n";
			}
			else
				return AbstractHandler::Handle(request);
		}
};

	class SqirrelHandler : public AbstractHandler {
	public:
		string Handle(string request) override {
			if (request == "Nut") {
				return "Squirrel: I'll eat the " + request + ".\n";
			}
			else
				return AbstractHandler::Handle(request);
		}
	};

	class DogHandler :public AbstractHandler
	{
	public:
		string Handle(string request) override {
			if (request == "MeatBall") {
				return "Dog: I'll eat the " + request + ".\n";
			}
			else
				return AbstractHandler::Handle(request);
		}
	};

	void ClientCode(Handler &handler)
	{
		/*������ ���������� ��� ������������ ��� ������ � ������������ � 
		������������. � ����������� ������� ������� ���� ����������,
		��� ���� ���������� �������� ������ �������.*/

		vector <string> food = { "Nut", "Banana","Cup of coffee","MeatBall" };
		for (const string &f : food) {
			cout << "Client: Who want's a " << f << "?\n";

			const string result = handler.Handle(f);
			if (!result.empty())
			{
				cout << " " << result;
			}
			else {
				cout << " " << f << "was left untouched.\n";
			}
		}
	}

void main()
{
	/*������ ����� ������������ ���� ������� ���� �������*/
	MonkeyHandler *monk = new MonkeyHandler;
	SqirrelHandler *sq = new SqirrelHandler;
	DogHandler *dog = new DogHandler;
	monk->SetNext(sq)->SetNext(dog);

	/*������ ������ ����� ����������� ���������� ������ ������ ����������� ������ 
	������� � �������*/
	cout << "Chain: Monkey > Squirrel >Dog\n\n";
	ClientCode(*monk);
	cout << "\n";
	cout << "Subchain: Squirrel > Dog\n\n";
	ClientCode(*sq);

	delete monk, sq, dog;

	system("pause");
}