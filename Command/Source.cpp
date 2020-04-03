#include <iostream>
#include <string>

/*Команда - поведенческий паттерн, позволяющий заворачивать
простые операции в отдельные объекты*/

/*Это позволяет откладывать выполнение команд, выстраивать их в
очереди, а также хранить историю и делать отмену.*/



using namespace std;

class Command
{
	/*Интерфейс Команды объявляет метод для выполнения команд*/
public:
	virtual ~Command()
	{

	}
	virtual void Execute() const = 0;
	/*Некоторые команды способны выполлнять простые операции самстоятельно*/

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
	/*Классы получаетелй содержат некую важную бизнес-логику. Они умеют выполнять
	все виды операций, связанных с выполнением запроса. Фактически любой класс 
	может выступать получателем.*/

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
	/*Но есть и команды, которые делегируют более сложные операции,
	так называемым получателям.*/
private:
	Receiver *rec_;
	string a_, b_; // Данные о контексте, необходимые для запуска методов получателя
public:
	/*Сложные команды могут принимать один или несколько объектов-получателей
	вместе с любыми данными о контексте через конструктор*/
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
		/*Отправитель связан с одной или несколькими командами. Он отправляет запрос команде.*/
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
			/*Отправитель не зависит от классов конкретных комманд и получателей.
			Отправитель передает запрос получателю косвенно, выполняя команду.*/
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
{/*Клиентский код может параметризовать отправителя любыми командами.*/
	Invoker *invoker = new Invoker;
	invoker->SetOnStart(new SimpleCommand("say Hi"));
	Receiver *rec = new Receiver;
	invoker->SetOnFinish(new ComplexCommand(rec, "Send email", "Save report"));
	invoker->DoSomethingImportant();

	delete invoker;
	delete rec;

	system("pause");
}