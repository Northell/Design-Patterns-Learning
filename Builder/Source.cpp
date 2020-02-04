#include <iostream>
#include <vector>
#include <string>

using namespace std;

	
class Product
	{
	private:
		string Walls;
		string Roof;
		string Doors;
		string Windows;
		string Type;
	public:
		void InsertWalls(string walls) { Walls = walls; }
		void InsertRoof(string roof) { Roof = roof; }
		void InsertDoors(string doors) { Doors = doors; }
		void InsertWindows(string windows) { Windows = windows;}
		void TypeHouse(string type) { Type = type; }
		void Show()
		{
			cout << "���������:" << endl;
			cout << "����� ����: " << Type<<endl;
			cout << "�����: " << Walls<< endl;
			cout << "�����: " << Roof << endl;
			cout << "�����: " << Doors << endl;
			cout << "����: " << Windows << endl;
		}
		void ResultHouse()
		{
			Show();
		}
	};
	

	


class BuilderHouse
{
public:

	virtual ~BuilderHouse() {};
	virtual void getWalls() const = 0;				//�����
	virtual void getRoof() const = 0;				//�����
	virtual void getDoors() const = 0;
	virtual void getWindows() const = 0;
	virtual void getTypeHouse() const = 0;
};


class IronHouse : public BuilderHouse
{
private:
	Product* _ironhouse;
public:
	IronHouse()
	{
		this->Reset();
	}
	~IronHouse()
	{
		delete _ironhouse;
	}
	
	void Reset()
	{
		this->_ironhouse = new Product();
	}

	void getWalls() const override 
	{
		_ironhouse->InsertWalls("Yellow");
	}
	void getRoof() const override
	{
		_ironhouse->InsertRoof("Iron");
	}
	void getDoors() const override
	{
		_ironhouse->InsertDoors("Wood");
	}
	void getWindows() const override
	{
		_ironhouse->InsertWindows("Very Big");
	}
	void getTypeHouse() const override
	{
		_ironhouse->TypeHouse("Modern");
	}

	Product* GetProduct() {
		Product* result = this->_ironhouse;
		this->Reset();
		return result;
	}
};

class WoodHouse : public BuilderHouse
{
private:
	Product* _woodhouse;
public:
	WoodHouse()
	{
		this->Reset();
	}
	~WoodHouse()
	{
		delete _woodhouse;
	}

	void Reset()
	{
		this->_woodhouse = new Product();
	}

	void getWalls() const override
	{
		_woodhouse->InsertWalls("Yellow");
	}
	void getRoof() const override
	{
		_woodhouse->InsertRoof("Iron");
	}
	void getDoors() const override
	{
		_woodhouse->InsertDoors("Wood");
	}
	void getWindows() const override
	{
		_woodhouse->InsertWindows("Very Big");
	}
	void getTypeHouse() const override
	{
		_woodhouse->TypeHouse("Modern");
	}
	Product* GetProduct() {
		Product* result = this->_woodhouse;
		this->Reset();
		return result;
	}
};
class Direct
{
private:
	BuilderHouse* builder;

	
public:
	void set_builder(BuilderHouse* builder)
	{
		this->builder = builder;
	}
	void FullBuild()
	{
		this->builder->getDoors();
		this->builder->getRoof();
		this->builder->getTypeHouse();
		this->builder->getWalls();
		this->builder->getWindows();
	}
	
};

void ClientCode(Direct& director)
{
	WoodHouse* builder = new WoodHouse();
	director.set_builder(builder);
	director.FullBuild();
	cout << "Standart House:\n";
	
	Product* p = builder->GetProduct();		//�������� ������ �� ���������
	p->Show();								//���������� ���������

	delete builder;
}
int main()
{
	setlocale(LC_ALL, "ru");
	Direct* direct = new Direct();
	ClientCode(*direct);

	delete direct;

	return 0;
}