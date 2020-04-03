#include <iostream>
#include <string>

using namespace std;
/* Заместитель - это объект, который выступпает прослойкой между клиентом 
и реальным сервисным объектом. Он получает вызовы от клиента, выполняет свою
функцию (контроль доступа, кеширование и прочее), а затем передает вызов 
сервисному объекту. Имеет тот же интерфейс что и реальный объект, поэтому для 
клиента нет разницы - работать через заместителя или напрямую.

Применяется тогда, когда надо заменить незаметно для клиентов настоящий объект. 
Это позволит выполнить какие-либо добавочные поведения до и после основного повндения
настоящего объекта. Чаще всего деленирует всю настоящую работу своему реальному объекту.
Заметители часто сами следят за жизненным циклом своего объекта.*/


class Subject
{
	/*Интерфейс субъекта содержит общие опреации как для реального субъекта,
	так и для заместителя. */
public: 
	virtual void Request() const = 0;
};


class RealSubject : public Subject
{
	/*Реальный субьект содержит некоторую базовую бизнес логику.*/
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
		//Некоторые реальные проверки должны проходить здесь.

		cout << "Proxy: Checking access prior to firing a real request.\n";
		return true;
	}
	void LogAccess() const
	{
		cout <<" Proxy: Logging the time of request.\n";

	}
public:
	/*Заместитель хранит ссылку на объект класса РеалСубъект. Клиент может 
	либо лениво загрузить его, либо передать Заметителю.*/
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

/*Клиентский код должен работыть со всеми объектами через интерфейс субьекта*/

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