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
	cout << "输入配置文件名：";
	cin >> input;
	output.open(input);
	if (!output.is_open())
	{
		cout << "建立文件失败，请检查冲突再试。" << endl;
		return 0;
	}
	cout << "输入节点配置文件名：";
	cin >> input;
	string node = input;
	output << input << ' ';
	cout << "输入服务数据文件名：";
	cin >> input;
	string service = input;
	output << input << ' ';
	cout << "输入截止期配置文件名：";
	cin >> input;
	string time = input;
	output << input << ' ';
	output.close();
	output.open(node);
	if (!output.is_open())
	{
		cout << "建立文件失败，请检查冲突再试。" << endl;
		return 0;
	}
	cout << "输入节点总数：";
	cin >> nodeNumber;
	output << nodeNumber << ' ';
	for (int i = 1; i <= nodeNumber; i++)
	{
		cout << "节点[" << i << "]的后继域总数：" << endl;
		int nodeCount;
		cin >> nodeCount;
		output << nodeCount << ' ';
		cout << "节点[" << i << "]的后继域（以空格或回车间隔）：" << endl;
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
		cout << "建立文件失败，请检查冲突再试。" << endl;
		return 0;
	}
	for (int i = 1; i <= nodeNumber; i++)
	{
		int spcount{ 0 };
		cout << "输入节点[" << i << "]的服务总数：";
		cin >> spcount;
		output << spcount << ' ';
		int temp;
		for (int j = 0; j < spcount; j++)
		{
			cout << "输入服务[" << j << "]的时间：";
			cin >> temp;
			output << temp << ' ';
			cout << "输入服务[" << j << "]的费用：";
			cin >> temp;
			output << temp << ' ';
		}
	}
	output.close();
	output.open(time);
	if (!output.is_open())
	{
		cout << "建立文件失败，请检查冲突再试。" << endl;
		return 0;
	}
	cout << "输入截止期：";
	int timeLimit{ 0 };
	cin >> timeLimit;
	output << timeLimit;
	cout << "数据导入完成！" << endl;
	system("pause");
}