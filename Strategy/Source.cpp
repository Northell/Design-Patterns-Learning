#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


/*��������� - ��� ������������� �������, ������� ����� ���������� � �����������
������ � ������ �� ����������������. ����� ������� �������� ������ �� ������-
��������� � ���������� �� ������. ��������� ����� ��������� ���� ������ ������,
���� ��������� ���� ������ ������� ������.

����������� ���, ��� ����� ��������� �������� �� ����� ���������� ���������.������
������� ��������� ����� �������� �������� ������-�����������.*/

class Strategy
{
	/*��������� ��������� ��������� ��������, ����� ��� ���� ��������������
	������ ���������� ���������.
	
	�������� ���������� ���� ��������� ��� ������ ���������, ������������� �����������
	�����������*/
public:
	virtual ~Strategy() {}
	virtual string DoAlgorithm(const vector<string> &data) const = 0;
};

class Context
{
	/*�������� ���������� ���������, ��������������� ������� ��� ��������.

	�������� ������ ������ �� ���� �� �������� ���������. �������� �� �����
	����������� ������ ���������. �� ������ ��������
	�� ����� ����������� ����� ��������� ���������.*/
private:
	Strategy *strategy_;
	/*������ �������� ��������� ��������� ����� �����������, � �����
	������������� ������ ��� �� ��������� �� ����� ����������.*/
public:
	Context(Strategy *strategy = nullptr) : strategy_(strategy)
	{

	}
	~Context()
	{
		delete this->strategy_;
	}

	/*������ �������� ��������� �������� ������ ��������� �� ����� ����������.*/
	void set_strategy(Strategy *strategy)
	{
		delete this->strategy_;
		this->strategy_ = strategy;
	}
	/*������ ����, ����� �������������� ������������� ������������� ������
	���������, �������� ���������� ��������� ������ ������� ���������.*/
	void DoSomeBusinessLogic() const
	{
		cout << "Context: Sorting data using this stratgy (not sure how it'lldo it)\n";
		string result = this->strategy_->DoAlgorithm(vector<string>{"a", "e", "c", "b", "d"});
		cout << result << "\n";
	}
};

class ConcreteStrategyA :public Strategy
{
	/*��������� ��������� ��������� ��������, ������ �������� ���������� ���������.
	���� ��������� ������ �� ���������������� � ���������.*/
public:
	string DoAlgorithm(const vector<string> &data) const override
	{
		string result;
		for_each(begin(data), end(data), [&result](const string &letter){
		
			result += letter;
		}); //������
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
		}); //������
		sort(begin(result), end(result));

		for (int i = 0; i < result.size() / 2; i++)
			swap(result[i], result[result.size() - i - 1]);
		return result;
	
	}
};
void ClientCode()
{
	/*���������� ��� �������� ���������� ��������� � �������� �� � ��������. ������
	������ ����� � �������� ����� �����������, ����� ������� ���������� �����.*/
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