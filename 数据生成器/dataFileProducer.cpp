//dataFileProducer.cpp
#include<iostream>
#include<fstream>
#include<string>
int main()
{
	using namespace std;
	int nodeNumber;
	ofstream output;
	char input[1024];
	cout << "���������ļ�����";
	cin >> input;
	output.open(input);
	if (!output.is_open())
	{
		cout << "�����ļ�ʧ�ܣ������ͻ���ԡ�" << endl;
		return 0;
	}
	cout << "����ڵ������ļ�����";
	cin >> input;
	string node = input;
	output << input << ' ';
	cout << "������������ļ�����";
	cin >> input;
	string service = input;
	output << input << ' ';
	cout << "�����ֹ�������ļ�����";
	cin >> input;
	string time = input;
	output << input << ' ';
	output.close();
	output.open(node);
	if (!output.is_open())
	{
		cout << "�����ļ�ʧ�ܣ������ͻ���ԡ�" << endl;
		return 0;
	}
	cout << "����ڵ�������";
	cin >> nodeNumber;
	output << nodeNumber << ' ';
	for (int i = 1; i <= nodeNumber; i++)
	{
		cout << "�ڵ�[" << i << "]�ĺ����������" << endl;
		int nodeCount;
		cin >> nodeCount;
		output << nodeCount << ' ';
		cout << "�ڵ�[" << i << "]�ĺ�����Կո��س��������" << endl;
		int next;
		for (int i = 0; i < nodeCount; i++)
		{
			cin >> next;
			output << next << ' ';
		}
	}
	output.close();
	output.open(service);
	if (!output.is_open())
	{
		cout << "�����ļ�ʧ�ܣ������ͻ���ԡ�" << endl;
		return 0;
	}
	for (int i = 1; i <= nodeNumber; i++)
	{
		int spcount{ 0 };
		cout << "����ڵ�[" << i << "]�ķ���������";
		cin >> spcount;
		output << spcount << ' ';
		int temp;
		for (int j = 0; j < spcount; j++)
		{
			cout << "�������[" << j << "]��ʱ�䣺";
			cin >> temp;
			output << temp << ' ';
			cout << "�������[" << j << "]�ķ��ã�";
			cin >> temp;
			output << temp << ' ';
		}
	}
	output.close();
	output.open(time);
	if (!output.is_open())
	{
		cout << "�����ļ�ʧ�ܣ������ͻ���ԡ�" << endl;
		return 0;
	}
	cout << "�����ֹ�ڣ�";
	int timeLimit{ 0 };
	cin >> timeLimit;
	output << timeLimit;
	cout << "���ݵ�����ɣ�" << endl;
	system("pause");
}