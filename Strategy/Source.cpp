#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


/*Стратегия - это поведенческий паттерн, выносит набор алгоритмов в собственные
классы и делает их взаимосвязанными. Дргие объекты содержат ссылку на объект-
стратегию и делегируют ей работу. Программа может подменить этот объект другим,
если требуется иной способ решения задачи.

Применяется там, где нужно подменять алгоритм во время выполнения программы.Многие
примеры стратегии можно заменить простыми лямбда-выражениями.*/

class Strategy
{
	/*интерфейс стратегии объявляет операции, общие для всех поддерживаемых
	версий некоторого алгоритма.
	
	Контекст использует этот интерфейс для вызова алгоритма, определенного Конкретными
	Стратегиями*/
public:
	virtual ~Strategy() {}
	virtual string DoAlgorithm(const vector<string> &data) const = 0;
};

class Context
{
	/*Контекст определяет интерфейс, предоставляющий интерес для клиентов.

	Контекст хранит ссылку на один из объектов Стратегии. Контекст не знает
	конкретного класса стратегии. Он должен работать
	со всеми стратегиями через интерфейс Стратегии.*/
private:
	Strategy *strategy_;
	/*Обычно контекст принимает стратегию через конструктор, а также
	предоставляет сеттер для ее изменения во время выполнения.*/
public:
	Context(Strategy *strategy = nullptr) : strategy_(strategy)
	{

	}
	~Context()
	{
		delete this->strategy_;
	}

	/*Обычно Контекст позволяет заменить объект Стратегии во время выполнения.*/
	void set_strategy(Strategy *strategy)
	{
		delete this->strategy_;
		this->strategy_ = strategy;
	}
	/*Вместо того, чтобы самостоятельно реализовывать множетсвенные версии
	алгоритма, Контекст делегирует некоторую работу объекту Стратегии.*/
	void DoSomeBusinessLogic() const
	{
		cout << "Context: Sorting data using this stratgy (not sure how it'lldo it)\n";
		string result = this->strategy_->DoAlgorithm(vector<string>{"a", "e", "c", "b", "d"});
		cout << result << "\n";
	}
};

class ConcreteStrategyA :public Strategy
{
	/*Конкретые Стратегии реализуют алгоритм, следуя базовому интерфейсу Стратегии.
	Этот интерфейс делает их взаимосвязанными в контексте.*/
public:
	string DoAlgorithm(const vector<string> &data) const override
	{
		string result;
		for_each(begin(data), end(data), [&result](const string &letter){
		
			result += letter;
		}); //Лямбда
		sort(begin(result), end(result));

		return result;
	}
};
class ConcreteStrategyB : public Strategy
{
	string DoAlgorithm(const vector<string> &data)const override
	{
		string result;
		for_each(begin(data), end(data), [&result](const string &letter) {

			result += letter;
		}); //Лямбда
		sort(begin(result), end(result));

		for (int i = 0; i < result.size() / 2; i++)
			swap(result[i], result[result.size() - i - 1]);
		return result;
	
	}
};
void ClientCode()
{
	/*Клиентский код выбирает конкретную стратегию и передает ее в контекст. Клиент
	должен знать о различях между стратегиями, чтобы сделать правильный выбор.*/
	Context *cont = new Context(new ConcreteStrategyA);
	cout << "Client: Strategy is set to reverse sorting.\n";
	cont->DoSomeBusinessLogic();
	cout << "\n";
	cout << "Client: Strategy is set to reverse sorting.\n";
	cont->set_strategy(new ConcreteStrategyB);
	cont->DoSomeBusinessLogic();
	delete cont;
}


int main()
{
	ClientCode();
	system("pause");
	return 0;
}