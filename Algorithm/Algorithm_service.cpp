//Algorithm_service.cpp
#include"stdafx.h"

using namespace std;
//创建错误代码
typedef int status;
#define SUCCESS 0			//操作成功	
#define ERR_FAILED -1		//错误：操作失败
#define ERR_BADDATA -2		//错误：坏数据
#define ERR_NOSOLVE -3		//错误：无解

//常参体
#define NODE_MAX 512		//设置节点最大数
#define CONNECT_MAX 8		//设置前驱/后继最大连接数
#define SERVICE_MAX 16		//设置服务最大数
#define SEARCH_DEEPTH 1024	//设置循环搜索次数

//数据结构
struct V					//V节点
{
	//后驱
	//V* prior[CONNECT_MAX];//前驱结点
	int next[CONNECT_MAX];	//后继节点
	int countNext;			//后继数

	//服务
	//int s[SERVICE_MAX];	//名称
	int t[SERVICE_MAX];		//时间
	int c[SERVICE_MAX];		//价值
	int serviceCount;		//服务数
};
struct SolveQuene			//解存放区
{
	int quene = 0;			//选中序号
	int service = 0;		//选中服务
};

//函数体
status initialization();	//初始化
status firstSolve();		//寻找初始解
status localOptimization();	//局部优化
status serviceChoose();		//服务选择
status chose(const int i);	//单步服务选择
int sumUp(SolveQuene[]);	//值累加器

//实例化
V record[NODE_MAX];
SolveQuene solveQuene[NODE_MAX];	//解数列
SolveQuene tempQuene[NODE_MAX];		//解数列交换储存

int nodeNumber = 0;			//节点总数
int limit = 0;				//时间限制
bool debug = { true };		//设置debug信息打印输出

int main()					//主函数
{
	initialization();
	for (int i = 0; i < 10; i++)
	{
		firstSolve();
	}
	system("pause");
	return 0;
}

//初始化
status initialization()
{
	srand(static_cast<unsigned>(time(0)));			//初始化随机数
	ifstream leadIn;		//主配置导入器
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
	ifstream infile;		//节点配置导入器
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
	if (debug)
	{
		cout << "文件头记载.节点总数 = " << nodeNumber << endl;
	}
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
		record[i].countNext = line;
		for (int j = 0; j < line; j++)
		{
			int addnext;
			infile >> addnext;
			record[i].next[j] = addnext;
		}
	}
	infile.close();
	if (debug)
	{
		for (int i = 1; i <= nodeNumber; i++)
		{
			cout << "Node " << setw(2) << i << " has following " << record[i].countNext << " next node(s): " << endl;
			for (int j = 0; j < record[i].countNext; j++)
			{
				cout << j << '\t' << record[i].next[j] << endl;
			}
		}
	}
	cout << "End." << endl;
	ifstream SP;				//服务数据导入器
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
		record[i].serviceCount = count;
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
	if (debug)
	{
		for (int i = 1; i <= nodeNumber; i++)
		{
			cout << "Node " << setw(2) << i << " has " << record[i].serviceCount << " following service(s): " << endl;
			for (int j = 0; j < record[i].serviceCount; j++)
			{
				cout << "SP[" << j << "]" << endl;
				cout << 't' << '\t' << record[i].t[j] << endl;
				cout << 'c' << '\t' << record[i].c[j] << endl;
			}
		}
	}
	cout << "End." << endl;
	ifstream timeLimit;			//截止期数据导入器
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
	if (!(limit>0))
	{
		cout << "截止期数据有效性验证失败，请检查数据文件再试。" << endl;
		return ERR_BADDATA;
	}
	if (debug)
	{
		cout << "截止期为" << limit << "。" << endl ;
	}
	cout << "End." << endl;
	cout << "数据导入完成。" << endl;
	cout << "End." << endl;
	leadIn.close();
	return SUCCESS;			//操作成功返回
}
//寻找初始解
status firstSolve()
{
	solveQuene[1].quene = 1;
	int locate = 1;
	int loop{ 0 };
	do
	{
		int i = 2;
		for (int x = 0; x < NODE_MAX; x++)
		{
			solveQuene[i].quene = 0;
		}
		while (solveQuene[i - 1].quene != nodeNumber)
		{
			solveQuene[i].quene = record[solveQuene[i - 1].quene].next[rand() % record[solveQuene[i - 1].quene].countNext];
			solveQuene[0].quene = i;
			i++;
		}
		if (loop>SEARCH_DEEPTH)
		{
			break;
			cout << "无法满足条件，提前退出。" << endl;
		}
		loop++;
	} while (serviceChoose() != SUCCESS);
	if (debug)
	{
		int i = 1;
		cout << "初始解";
		for(int i=1;i<= solveQuene[0].quene;i++)
		{
			cout << "->" << solveQuene[i].quene;
		}
		cout << endl;
		cout << "路径长度" << solveQuene[0].quene;
		cout << endl;
		cout << "价值" << sumUp(solveQuene) << endl;
	}
	return SUCCESS;
}
//局部优化
status localOptimization()
{
	for (int  i = 0; i <= solveQuene[0].quene; i++)
	{
		tempQuene[i].quene = solveQuene[i].quene;
		tempQuene[i].quene = solveQuene[i].quene;
	}
	for (int i = solveQuene[0].quene; i > 0; i--)
	{
		if (record[tempQuene[i].quene].serviceCount > 1)
		{
			for (int j = 0; j < record[tempQuene[i].quene].serviceCount; j++)
			{
				tempQuene[i].quene = record[tempQuene[i].quene].next[j];
				//TODO.. 
			}
		}
	}
	return SUCCESS;
}
//服务选择
status serviceChoose()
{
	if (chose(1)==SUCCESS)
	{
		return SUCCESS;
	}
	return ERR_NOSOLVE;
}
//服务选择递归体
status chose(const int i)
{
	if (i == solveQuene[0].quene + 1)
	{
		if (sumUp(solveQuene)==-1)
		{
			return ERR_NOSOLVE;
		}
		return SUCCESS;
	}
	else
	{
		for (int j = 0; j < record[solveQuene[i].quene].serviceCount; j++)
		{
			tempQuene[i].service = j;
			chose(i + 1);
			if (sumUp(tempQuene) != -1 && sumUp(tempQuene)<sumUp(solveQuene))	//TODO.
			{
				for (int k = 1; k <= solveQuene[0].quene; k++)
				{
					solveQuene[k].service = tempQuene[k].service;
				}
			}
		}
	}
	return ERR_NOSOLVE;	//消除Warning用
}
//值累加器
int sumUp(SolveQuene input[])
{
	int sumc{ 0 };
	int sumt{ 0 };
	for (int i = 1; i <= input[0].quene; i++)
	{
		sumc += record[input[i].quene].c[input[i].service];
		sumt += record[input[i].quene].t[input[i].service];
	}
	if (sumt>limit)
	{
		return -1;
	}
	else
	{
		return sumc;
	}
}