//Algorithm_service.cpp
#include"stdafx.h"

using namespace std;
//创建错误代码
typedef int status;
#define SUCCESS 0			//操作成功	
#define ERR_FAILED -1		//错误：操作失败
#define ERR_BADDATA -2		//错误：坏数据

//参数体
#define NODE_MAX 512		//设置节点最大数
#define CONNECT_MAX 8		//设置前驱/后继最大连接数
#define SERVICE_MAX 16		//设置服务最大数

//函数体
status initialization();	//初始化
status firstSolve();		//寻找初始解
status localOptimization();	//局部优化
status serviceChoose();		//服务选择

//数据结构
struct V					//V节点
{
	//后驱
	//V* prior[CONNECT_MAX];//前驱结点
	int next[CONNECT_MAX];	//后继节点

	//服务
	//int s[SERVICE_MAX];	//名称
	int t[SERVICE_MAX];		//时间
	int c[SERVICE_MAX];		//价值
};

//实例化
V record[NODE_MAX];
int nodeNumber = 0;			//节点总数
int limit = 0;				//时间限制

int main()
{
	initialization();
	system("pause");
	return 0;
}

//初始化
status initialization()
{
	ifstream leadIn;
	string chrLeadIn;
	cout << "指定配置文件:";
	do
	{
		cin >> chrLeadIn;
		leadIn.open(chrLeadIn);
		if (leadIn)
			break;
		cout << "文件无法打开,请检查输入再试。";
	} while (!leadIn);
	for (int i = 0; i < NODE_MAX; i++)
	{
		for (int j = 0; j < CONNECT_MAX; j++)
		{
			record[i].next[j] = 0;	//置空
		}
	}
	ifstream infile;
	string strInfile;
	leadIn >> strInfile;
	infile.open(strInfile);
	if (!infile)
	{
		cout << "节点数据文件无法打开,请检查配置文件再试。";
		return ERR_FAILED;
	}
	cout << "节点数据文件打开成功" << endl;
	infile >> nodeNumber;		//第一个数据为节点总数
	cout << "文件头记载.节点总数 = " << nodeNumber << endl;
	if (nodeNumber>NODE_MAX)
	{
		cout << "节点数过多，请调整设置后重试。" << endl;
		return ERR_FAILED;
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
	infile.close();
	for (int i = 1; i <= nodeNumber; i++)
	{
		cout << "Node " << setw(2) << i << " has following next node(s): " << endl;
		for (int j = 0; j < CONNECT_MAX; j++)
		{
			if (record[i].next[j] != 0)
			{
				cout << j << '\t' << record[i].next[j] << endl;
			}
			else
			{
				break;
			}
		}
	}
	cout << "End." << endl;
	ifstream SP;
	string strSP;
	leadIn >> strSP;
	SP.open(strSP);
	if (!SP)
	{
		cout << "服务数据无法打开，请检查配置文件再试。" << endl;
		return ERR_FAILED;
	}
	cout << "服务数据打开成功" << endl;
	for (int i = 1; i <= nodeNumber; i++)
	{
		int count;
		SP >> count;
		for (int j = 0; j < count; j++)
		{
			int data;
			SP >> data;
			record[i].t[j] = data;
			SP >> data;
			record[i].c[j] = data;
		}
	}
	SP.close();
	for (int i = 1; i <= nodeNumber; i++)
	{
		cout << "Node " << setw(2) << i << " has following service(s): " << endl;
		if (record[i].t[0] != 0)
		{
			for (int j = 0; j < CONNECT_MAX; j++)
			{
				if (record[i].t[j] != 0)
				{
					cout << "SP[" << j << "]" << endl;
					cout << 't' << '\t' << record[i].t[j] << endl;
					cout << 'c' << '\t' << record[i].c[j] << endl;
				}
				else
				{
					break;
				}
			}
		}
	}
	cout << "End." << endl;
	ifstream timeLimit;
	string chrTimeLimit{ 0 };
	leadIn >> chrTimeLimit;
	timeLimit.open(chrTimeLimit);
	if (!timeLimit)
	{
		cout << "截止期数据无法打开，请检查配置文件再试。" << endl;
		return ERR_FAILED;
	}
	cout << "截止期数据打开成功" << endl;
	timeLimit >> limit;
	timeLimit.close();
	if (!limit>0)
	{
		cout << "截止期数据有效性验证失败，请检查数据文件再试。" << endl;
		return ERR_BADDATA;
	}
	cout << "截止期为" << limit << "。" << endl << "End." << endl;
	cout << "数据导入完成。" << endl;
	leadIn.close();
	return SUCCESS;
}
//寻找初始解
status firstSolve()
{
	do 
	{

	} while (!serviceChoose());
	return SUCCESS;
}
//局部优化
status localOptimization()
{
	return SUCCESS;
}
//服务选择
status serviceChoose()
{
	return SUCCESS;
}