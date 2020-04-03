#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;
/*Снимок - поведенческий паттерн, позволяющий делать снимки внутреннего состояния
объектов, а затем восстанавливать их. При этом снимок не раскрывает 
подробностей реализации объектов, и клиент не имеет доступа к защищенной информации
объекта.*/

/*Реализуют чаще всего с помощью сериализации. Но это не единственный, да и не 
самый эффективный метод сохранения объектов во время выполнения программы.*/
class Memento
{
	/*Интерфейс Снимка предоставляет способ извлечения метаданных снимка, таких как
	дата создания или название. Однакоо он не раскрывает состояние Создателя*/
public:
	virtual string GetName() const = 0;
	virtual string date() const = 0;
	virtual string state() const = 0;
};

class ConcreteMemento : public Memento {
	/*Конкретный снимок содержит инфраструктуру для хранения состояния Создателя*/
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
	/*Создатель испольлзует этот метод, когда восстанавливает свое состояние.*/
	string state() const override
	{
		return this->state_;
	}
	/*Остальные методы используются опекуном для отображения метаданных*/

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
	/*Создатель содержит некоторое важное состояние, которое может со временем 
	меняться. Он также объявляет метод сохранения состояния внутри снимка и метод
	восстановления состояния из него.*/
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
		/*Бизнес-лошика Создателя может повлиять на его внутреннее состояние.
		Поэтому клиент должен выполнить резервное копирование состояния с помощью
		метода save перед запуском методов бизнес-логики.*/

		void DoSomething()
		{
			cout << "Originator: I'm doing something important.\n";
			this->state_ = this->GenerateRandomString(30);
			cout << "Originator: and my state has changed to: " << this->state_ << "\n";
		}

		/*Сохраняет текущее состояние внутри снимка
		*/
		Memento *Save()
		{
			return new ConcreteMemento(this->state_);
		}
		/*Восстанавливает состояние создателя из объекта снимка
	*/
	
		void Restore(Memento *memento) {
			this->state_ = memento->state();
			cout << "Originator: My state has changed to: " << this->state_ << "\n";
		}

};
class Caretaker
{		/*Опекун не зависит от класса конкретного снимка. Таким образом,
		он не имеет доступа к состоянию создателя, хранящемуся внутри снимка.
		Он работает со всеми снимками через базовый интерфейс Снимка.*/

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