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
	int nextCount;			//后继数

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
status serviceChoose(SolveQuene quene[]);
							//服务选择
status chose(SolveQuene quene[], const int i);
							//单步服务选择
int sumUp(SolveQuene[]);	//值累加器

//实例化
V record[NODE_MAX];
SolveQuene solveQuene[NODE_MAX];	//解队列
SolveQuene downTempQuene[NODE_MAX];	//下方解队列交换储存
SolveQuene upTempQuene[NODE_MAX];	//上方解队列交换储存

int nodeNumber = 0;			//节点总数
int limit = 0;				//时间限制
bool debug = { true };		//设置debug信息打印输出

int main()					//主函数
{
	initialization();		//初始化
	for (int i = 0; i < 10000; i++)
	{
		firstSolve();			//寻找初始解
		localOptimization();	//局部优化
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
		record[i].nextCount = line;
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
			cout << "Node " << setw(2) << i << " has following " << record[i].nextCount << " next node(s): " << endl;
			for (int j = 0; j < record[i].nextCount; j++)
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
	//int locate = 1;
	int loop{ 0 };
	//寻找一个合理的初始解队列
	do
	{
		int i = 2;
		//清空解队列
		for (int x = 0; x < NODE_MAX; x++)
		{
			solveQuene[i].quene = 0;
		}
		//首解随机寻路
		while (solveQuene[i - 1].quene != nodeNumber)
		{
			solveQuene[i].quene = record[solveQuene[i - 1].quene].next[rand() % record[solveQuene[i - 1].quene].nextCount];
			solveQuene[0].quene = i;
			i++;
		}
		if (loop>SEARCH_DEEPTH)
		{
			cout << "预留计算资源耗尽，提前退出。" << endl;
			break;
		}
		loop++;
	} while (serviceChoose(solveQuene) != SUCCESS);
	solveQuene[0].service = sumUp(solveQuene);	//存放价值
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
		cout << "价值" << solveQuene[0].service;
		cout << endl;
	}
	return SUCCESS;
}
//局部优化
status localOptimization()
{
	//拷贝一份当前状态
	for (int  i = 0; i <= solveQuene[0].quene; i++)
	{
		downTempQuene[i].quene = solveQuene[i].quene;
		downTempQuene[i].service = solveQuene[i].service;
	}
	//使用副本寻找路径并估值
	for (int i = solveQuene[0].quene; i > 0; i--)
	{

		//寻找分支点
		if (record[downTempQuene[i].quene].nextCount > 1)
		{
			int loadNode{ 0 };	//记录当前节点到下一节点的next序号
			for (int j = 0; j < record[downTempQuene[i].quene].serviceCount; j++)
			{
				if (record[downTempQuene[i].quene].next[j] == downTempQuene[i + 1].quene)
				{
					loadNode = j;
					break;
				}
			}
			//向上（小端）寻找邻域路径
			if (loadNode>0)
			{
				//将上部相邻节点挂载到解队列
				downTempQuene[i+1].quene =record[downTempQuene[i].quene].next[loadNode-1];		//切换节点到上端邻域路径
				if (downTempQuene[i + 1].quene == 17)
				{
					downTempQuene[0].quene = i + 1;	//记录路径长度
				}
				else
				{
					int loop{ i + 2 };
					do
					{
						//上端路径的最下路径（邻域）
						downTempQuene[loop].quene = record[downTempQuene[loop - 1].quene].next[record[downTempQuene[loop - 1].quene].nextCount - 1];
						//downTempQuene[0].quene = loop;	//下方统一赋值减小开销
						loop++;
					} while (downTempQuene[loop].quene != 17);
					downTempQuene[0].quene = loop - 1;	//记录路径长度
				}
				//上邻域可行
				if (serviceChoose(downTempQuene) == SUCCESS)
				{
					downTempQuene[0].service = sumUp(downTempQuene);
					if (debug)
					{
						int i = 1;
						cout << "上邻域可行，路径：";
						for (int i = 1; i <= downTempQuene[0].quene; i++)
						{
							cout << "->" << downTempQuene[i].quene;
						}
						cout << endl;
						cout << "路径长度" << downTempQuene[0].quene;
						cout << endl;
						cout << "价值" << downTempQuene[0].service << endl;
					}
					break;
				}
			}
		}
	}
	return SUCCESS;
}
//服务选择
status serviceChoose(SolveQuene quene[])
{
	if (chose(quene,1)!=SUCCESS)
	{
		return ERR_NOSOLVE;
	}
	return SUCCESS;
}
//服务选择递归体
status chose(SolveQuene quene[], const int i)
{
	if (i == quene[0].quene + 1)
	{
		if (sumUp(quene)==-1)
		{

			return ERR_NOSOLVE;
		}
		return SUCCESS;
	}
	else
	{
		for (int j = 0; j < record[quene[i].quene].serviceCount; j++)
		{
			quene[i].service = j;
			chose(quene,i + 1);
			if (sumUp(quene) != -1 && sumUp(quene)<sumUp(quene))
			{
				for (int k = 1; k <= quene[0].quene; k++)
				{
					quene[k].service = quene[k].service;
				}
			}
		}
	}
	return SUCCESS;
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