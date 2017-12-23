//Algorithm_service.cpp
#include"stdafx.h"
#include<fstream>
#include<string>
#include<iomanip>
//文件读写：http://blog.csdn.net/kingstar158/article/details/6859379/
#include"stdafx.h"

using namespace std;
//创建错误代码
typedef int status;
#define SUCCESS 0
#define ERR_FILEFILED -1
#define ERR_NOGOODDATA -2
//参数体
#define NODE_MAX 512	//设置节点最大数
#define CONNECT_MAX 8	//设置前驱/后继最大连接数
#define SERVICE_MAX 16	//设置服务最大数
//函数体
status initialization();	//初始化
//数据结构
struct V	//V节点
{
	//前后驱
	//V * prior[CONNECT_MAX];	//前驱结点
	int next[CONNECT_MAX];	//后继节点

	//服务
	int s[SERVICE_MAX];	//名称
	int t[SERVICE_MAX];	//时间
	int c[SERVICE_MAX];	//价值
};
//数据结构

V record[NODE_MAX];
int nodeNumber = 0;	//节点总数

status initialization()
{
	for (int i = 0; i < NODE_MAX; i++)
	{
		for (int j = 0; j < CONNECT_MAX; j++)
		{
			record[i].next[j] = 0;	//置空
		}
	}
	cout << "指定数据文件：";
	ifstream infile;
	string data;
	do
	{
		cin >> data;
		infile.open(data);
		if (infile)
			break;
		cout << "文件无法打开,请检查输入再试:";
	} while (!infile);
	cout << "数据文件打开成功" << endl;
	infile >> nodeNumber;	//第一个数据为节点总数
	cout << "文件头记载.节点总数 = "<<nodeNumber<<endl;
	if (nodeNumber>NODE_MAX)
	{
		cout << "节点数过多，请调整设置后重试" << endl;
		return ERR_FILEFILED;
	}
	for (int i = 1; i <= nodeNumber; i++)
	{
		int line;
		//infile.ignore(1);
		infile >> line;
		for (int j = 0; j < line; j++)
		{
			int addnext;
			infile >> addnext;
			record[i].next[j] = addnext;
		}
	}
	for (int i = 1; i <= nodeNumber; i++)
	{
		cout << "Node " << setw(2) << i << " has follow next node(s): " << endl;
		if (record[i].next[0]!=0)
		{
			for (int j = 0; j < CONNECT_MAX; j++)
			{
				if (record[i].next[j]!=0)
				{
					cout << j << '\t' << record[i].next[j] << endl;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			cout<<"End."<<endl;
		}

	}
	return SUCCESS;
}

int main()
{
	initialization();
	system("pause");
	return 0;
}
