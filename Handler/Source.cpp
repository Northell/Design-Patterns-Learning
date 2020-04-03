#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*Цепочка обязанностей - поведенческий паттерн, который передает запрос по цепочке
потенциальных обработчиков, пока кто-нибудь не обработает запрос

ИЗбавляет от жесткой привязки отправителя запроса к его получателю, позволяя
выстраивать цепь из различных обработчиков динамически

Применяется редко, т.к для реализации нужен связный список*/

class
	Handler
{
	/*Интерфейс обработчика объявляет метод построения цепочки обработчиков. Он
	также объявляет метод для выполнения запроса.*/
public: 
	virtual Handler *SetNext(Handler *handler) = 0;
	virtual string Handle(string request) = 0;
};

class AbstractHandler : public Handler
{
	/*Поведение цепочки по умолчанию может быть реализовано внутри обработчика.*/

private:
	Handler *next_handler_;

public:
	AbstractHandler() : next_handler_(nullptr) {}

	Handler *SetNext(Handler *handler) override
	{
		this->next_handler_ = handler;
		/*Возврат обработчика отсюда позволит связать обработчики
		простям способом вот так:
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
	/*Все конкретные обработчики либо обрабатывают запрос, либо передают его сл.*/
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
		/*Обычно клиентский код приспособлен для работы с единственным в 
		обработчиком. В большинстве случаев клиенту даже неизвестно,
		что этот обработчик является частью цепочки.*/

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
	/*Другая часть климнетского кода создает саму цепочку*/
	MonkeyHandler *monk = new MonkeyHandler;
	SqirrelHandler *sq = new SqirrelHandler;
	DogHandler *dog = new DogHandler;
	monk->SetNext(sq)->SetNext(dog);

	/*Клиент должен иметь возможность отправлять запрос любому обработчику только 
	первому в цепочке*/
	cout << "Chain: Monkey > Squirrel >Dog\n\n";
	ClientCode(*monk);
	cout << "\n";
	cout << "Subchain: Squirrel > Dog\n\n";
	ClientCode(*sq);

	delete monk, sq, dog;

	system("pause");
}