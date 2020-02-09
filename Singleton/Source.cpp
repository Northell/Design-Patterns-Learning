#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

class Singleton
{
private:
	static Singleton *_pinstance;
	static mutex _mutex;				//mutex - примитив синхронизации, который используетс€ дл€ защиты раздел€емых данных 
										//от одновременного доступа к нескольким потокам

protected:
	string value;
	Singleton(const string value) { this->value = value; }	//конструктор должен быть скрытым, чтобы предотвратить создание объекта через new
	~Singleton() {}
	//static Singleton* _singleton;


	

public:
	Singleton(Singleton &other) = delete;			//ќдиночки не должны быть клонируемыми
	void operator = (const Singleton &) = delete;	//ќдиночки не должны быть назначаемыми

	static Singleton *GetInstance(const string &value);		//статический метод, управл€ющий доступом к экзмепл€ру одиночки
	
		int SomeBuisnessLogic(int a, int b){			// ласс одиночка должен содержать какую то бизнеслогику
		
			return a + b;
		}

	

		string _value() const {
		return value;
	
	}

		

};

//Singleton *Singleton::_singleton = nullptr;		//—татические методы одлиночки должны быть определены вне класса
Singleton* Singleton::_pinstance{ nullptr };
mutex Singleton::_mutex;


/*Singleton * Singleton::GetInstance(const string & value)/* Ёто более безопасный способ создать экземпл€р.экземпл€р = новый синглтон* ,
															опасно, если два потока экземпл€ров хот€т получить доступ одновременно
{
	if (_singleton == nullptr)
	{
		_singleton = new Singleton(value);
	}

	
	return _singleton;
}*/
Singleton * Singleton::GetInstance(const string & value)/* Ёто более безопасный способ создать экземпл€р.экземпл€р = новый синглтон* ,
															опасно, если два потока экземпл€ров хот€т получить доступ одновременно*/
{
	if (_pinstance == nullptr)
	{
		lock_guard<mutex> lock(_mutex);
		_pinstance = new Singleton(value);
	}


	return _pinstance;
}

/* акие-нибудь методы дл€ использовани€ одиночки*/
void FirstMethod()
{
	this_thread::sleep_for(std::chrono::milliseconds(1000));
	Singleton *singleton = Singleton::GetInstance("Foo\n");
	cout << singleton->_value() << endl;
	cout << singleton->SomeBuisnessLogic(0, 1) <<endl;
}
void TwoMehod()
{
	this_thread::sleep_for(std::chrono::milliseconds(1000));
	Singleton *singleton = Singleton::GetInstance("Boo\n");
	cout << singleton->_value() << endl;
	cout << singleton->SomeBuisnessLogic(1, 1) << endl;
}


int main()
{
	cout << "If you see the same value, then singleton was reused (yay!)\n" <<
		"If you see different values, then 2 singletons were created (booo!!)\n\n";

	thread t1(FirstMethod);
	thread t2(TwoMehod);
	t1.join();
	t2.join();

	system("pause");
	return 0;
}