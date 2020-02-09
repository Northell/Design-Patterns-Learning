#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

class Singleton
{
private:
	static Singleton *_pinstance;
	static mutex _mutex;				//mutex - �������� �������������, ������� ������������ ��� ������ ����������� ������ 
										//�� �������������� ������� � ���������� �������

protected:
	string value;
	Singleton(const string value) { this->value = value; }	//����������� ������ ���� �������, ����� ������������� �������� ������� ����� new
	~Singleton() {}
	//static Singleton* _singleton;


	

public:
	Singleton(Singleton &other) = delete;			//�������� �� ������ ���� ������������
	void operator = (const Singleton &) = delete;	//�������� �� ������ ���� ������������

	static Singleton *GetInstance(const string &value);		//����������� �����, ����������� �������� � ���������� ��������
	
		int SomeBuisnessLogic(int a, int b){			//����� �������� ������ ��������� ����� �� ������������
		
			return a + b;
		}

	

		string _value() const {
		return value;
	
	}

		

};

//Singleton *Singleton::_singleton = nullptr;		//����������� ������ ��������� ������ ���� ���������� ��� ������
Singleton* Singleton::_pinstance{ nullptr };
mutex Singleton::_mutex;


/*Singleton * Singleton::GetInstance(const string & value)/* ��� ����� ���������� ������ ������� ���������.��������� = ����� ��������* ,
															������, ���� ��� ������ ����������� ����� �������� ������ ������������
{
	if (_singleton == nullptr)
	{
		_singleton = new Singleton(value);
	}

	
	return _singleton;
}*/
Singleton * Singleton::GetInstance(const string & value)/* ��� ����� ���������� ������ ������� ���������.��������� = ����� ��������* ,
															������, ���� ��� ������ ����������� ����� �������� ������ ������������*/
{
	if (_pinstance == nullptr)
	{
		lock_guard<mutex> lock(_mutex);
		_pinstance = new Singleton(value);
	}


	return _pinstance;
}

/*�����-������ ������ ��� ������������� ��������*/
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