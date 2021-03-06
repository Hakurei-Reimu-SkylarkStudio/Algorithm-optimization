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
#define LOOP_DEPTH 16		//设置优化路径深度
#define FAIL_MAX 3			//局部优化失败退出值
#define Ver "1.5.0"			//版本号
#define GIT_ADDRESS "https://github.com/Hakurei-Reimu-SkylarkStudio/Algorithm-optimization"
							//GitHub地址
#define RESULT_FILE_NAME "result.txt"
							//打印结果文件名


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
status singleLocalOptimization();
//单步局部优化
status serviceChoose(SolveQuene quene[]);
//服务选择
status chose(SolveQuene quene[], const int i);
//单步服务选择
int sumUp(SolveQuene[]);	//值累加器
status directSolve();		//给出解
status debugPrint();		//打印结果
status debugPrintLine();	//打印空行
void commandManager();		//命令行管理器

//实例化
V record[NODE_MAX];
SolveQuene solveQuene[NODE_MAX];	//解队列
SolveQuene downTempQuene[NODE_MAX];	//下方解队列交换储存
SolveQuene upTempQuene[NODE_MAX];	//上方解队列交换储存

int nodeNumber = 0;			//节点总数
int limit = 0;				//时间限制
bool debug = { true };		//设置debug信息打印输出
bool print = { true };		//设置优化结果打印
ofstream printResult;		//打印结果到文件


int main()					//主函数
{
	cout << "Ver:" << Ver << endl;
	cout << "GitHub addresss:" << endl << GIT_ADDRESS << endl;
	commandManager();		//通过命令行管理器管理用户输入并操作
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
	if (nodeNumber > NODE_MAX)
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
	if (!(limit > 0))
	{
		cout << "截止期数据有效性验证失败，请检查数据文件再试。" << endl;
		return ERR_BADDATA;
	}
	if (debug)
	{
		cout << "截止期为" << limit << "。" << endl;
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
		if (loop > SEARCH_DEEPTH)
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
		for (int i = 1; i <= solveQuene[0].quene; i++)
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
	debugPrint();	//打印初始解结果
	for (int loop = 0; loop < LOOP_DEPTH; loop++)
	{
		singleLocalOptimization();
		if (upTempQuene[0].service > downTempQuene[0].service)
		{
			if (downTempQuene[0].service < solveQuene[0].service)
			{
				//上端演进
				for (int i = 0; i <= solveQuene[0].quene; i++)
				{
					solveQuene[i].quene = downTempQuene[i].quene;
					solveQuene[i].service = downTempQuene[i].service;
				}
				debugPrint();
				if (debug)
				{
					cout << "选择上端" << endl;
				}
			}
			else
			{
				if (debug)
				{
					cout << "局部最优" << endl;
				}
				int i = 1;
				cout << "最优化路径：";
				for (int i = 1; i <= solveQuene[0].quene; i++)
				{
					cout << "->" << solveQuene[i].quene;
				}
				cout << endl;
				cout << "路径长度" << solveQuene[0].quene;
				cout << endl;
				cout << "价值" << solveQuene[0].service << endl;
				break;
			}
		}
		else if (upTempQuene[0].service < downTempQuene[0].service)
		{
			if (upTempQuene[0].service < solveQuene[0].service)
			{
				//下端演进
				for (int i = 0; i <= solveQuene[0].quene; i++)
				{
					solveQuene[i].quene = upTempQuene[i].quene;
					solveQuene[i].service = upTempQuene[i].service;
				}
				debugPrint();
				if (debug)
				{
					cout << "选择下端" << endl;
				}
			}
			else
			{
				if (debug)
				{
					cout << "局部最优" << endl;
				}
				int i = 1;
				cout << "最优化路径：";
				for (int i = 1; i <= solveQuene[0].quene; i++)
				{
					cout << "->" << solveQuene[i].quene;
				}
				cout << endl;
				cout << "路径长度" << solveQuene[0].quene;
				cout << endl;
				cout << "价值" << solveQuene[0].service << endl;
				break;
			}
		}
		else
		{
			if (debug)
			{
				cout << "局部最优" << endl;
			}
			int i = 1;
			cout << "最优化路径：";
			for (int i = 1; i <= solveQuene[0].quene; i++)
			{
				cout << "->" << solveQuene[i].quene;
			}
			cout << endl;
			cout << "路径长度" << solveQuene[0].quene;
			cout << endl;
			cout << "价值" << solveQuene[0].service << endl;

			break;
		}
	}
	debugPrintLine();	//打印空行
	return SUCCESS;
}
//单步局部优化
status singleLocalOptimization()
{
	//拷贝一份当前状态
	for (int i = 0; i <= solveQuene[0].quene; i++)
	{
		downTempQuene[i].quene = solveQuene[i].quene;
		downTempQuene[i].service = solveQuene[i].service;
		upTempQuene[i].quene = solveQuene[i].quene;
		upTempQuene[i].service = solveQuene[i].service;
	}
	//使用副本寻找上端邻域路径并估值
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
			if (loadNode > 0)
			{
				//将上部相邻节点挂载到解队列
				downTempQuene[i + 1].quene = record[downTempQuene[i].quene].next[loadNode - 1];		//切换节点到上端邻域路径
				if (downTempQuene[i + 1].quene == nodeNumber)	//不写大于以便发生异常时能溢出报错及时发现并解决错误
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
						loop++;
					} while (downTempQuene[loop - 1].quene != nodeNumber);
					downTempQuene[0].quene = loop - 1;	//记录路径长度
				}
				//上邻域可行
				if (serviceChoose(downTempQuene) == SUCCESS)
				{
					downTempQuene[0].service = sumUp(downTempQuene);
					if (debug)
					{
						int i = 1;
						cout << "上邻域路径：";
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
	//使用副本寻找下端邻域路径并估值
	for (int i = solveQuene[0].quene; i > 0; i--)
	{

		//寻找分支点
		if (record[upTempQuene[i].quene].nextCount > 1)
		{
			int loadNode{ 0 };	//记录当前节点到下一节点的next序号
			for (int j = 0; j < record[upTempQuene[i].quene].serviceCount; j++)
			{
				if (record[upTempQuene[i].quene].next[j] == upTempQuene[i + 1].quene)
				{
					loadNode = j;
					break;
				}
			}
			//向下（大端）寻找邻域路径
			if (loadNode < record[upTempQuene[i].quene].nextCount - 1)
			{
				//将下部相邻节点挂载到解队列
				upTempQuene[i + 1].quene = record[upTempQuene[i].quene].next[loadNode + 1];		//切换节点到上端邻域路径
				if (upTempQuene[i + 1].quene == nodeNumber)	//不写大于以便发生异常时能溢出报错及时发现并解决错误
				{
					upTempQuene[0].quene = i + 1;	//记录路径长度
				}
				else
				{
					int loop{ i + 2 };
					do
					{
						//下端路径的最上路径（邻域）
						upTempQuene[loop].quene = record[upTempQuene[loop - 1].quene].next[0];
						loop++;
					} while (upTempQuene[loop - 1].quene != nodeNumber);
					upTempQuene[0].quene = loop - 1;	//记录路径长度
				}
				//下邻域可行
				if (serviceChoose(upTempQuene) == SUCCESS)
				{
					upTempQuene[0].service = sumUp(upTempQuene);
					if (debug)
					{
						int i = 1;
						cout << "下邻域路径：";
						for (int i = 1; i <= upTempQuene[0].quene; i++)
						{
							cout << "->" << upTempQuene[i].quene;
						}
						cout << endl;
						cout << "路径长度" << upTempQuene[0].quene;
						cout << endl;
						cout << "价值" << upTempQuene[0].service << endl;
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
	if (chose(quene, 1) != SUCCESS)
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
		if (sumUp(quene) == -1)
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
			chose(quene, i + 1);
			if (sumUp(quene) != -1 && sumUp(quene) < sumUp(quene))
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
	if (sumt > limit)
	{
		return -1;
	}
	else
	{
		return sumc;
	}
}
//给出解
status directSolve()
{
	int loop{ 0 };
	int failTime{ 0 };
	int min{ 0 };					//最终结果筛选
	loop = LOOP_DEPTH;
	int* ptrAns = new int[loop];	//答案值储存队列
	for (int i = 0; i < loop; i++)
	{
		firstSolve();
		localOptimization();
		ptrAns[i] = solveQuene[0].service;
		//指定次数无法优化则提前退出
		if (i > 0 && ptrAns[i] > ptrAns[i - 1])
		{
			failTime++;
			if (failTime >= FAIL_MAX)
			{
				break;
			}
		}
		else
		{
			failTime = 0;
		}
	}
	min = ptrAns[0];
	for (int i = 0; i < loop; i++)
	{
		if (ptrAns[i] == 0)
		{
			break;
		}
		else
		{
			if (ptrAns[i] < min)
			{
				min = ptrAns[i];
			}
		}
	}
	cout << endl << "查找结果：" << min << endl << endl;
	return SUCCESS;
}
//打印结果
status debugPrint()
{
	if (print)
	{
		printResult.open(RESULT_FILE_NAME, ios::app);
		if (!printResult.is_open())
		{
			cout << "结果打印失败，请检查文件占用。" << endl;
			return ERR_FAILED;
		}
		printResult << solveQuene[0].service << ' ';
		printResult.close();
	}
	return SUCCESS;
}
//打印空行
status debugPrintLine()
{
	if (print)
	{
		printResult.open(RESULT_FILE_NAME, ios::app);
		if (!printResult.is_open())
		{
			cout << "结果打印失败，请检查文件占用。" << endl;
			return ERR_FAILED;
		}
		printResult << endl;
		printResult.close();
	}
	return SUCCESS;
}
//命令行管理器
void commandManager()
{
	string userInput;
	while (true)
	{
		system("color 0a");
		cout << endl;
		cout << ">";
		cin >> userInput;
		system("color 0e");
		if (userInput == "loopSolve" || userInput == "ls")
		{
			cout << "重复次数：";
			int loop{ 0 };
			cin >> loop;
			for (int i = 0; i < loop; i++)
			{
				directSolve();
			}
		}
		else if (userInput == "directSolve" || userInput == "ds")
		{
			directSolve();
		}
		else if (userInput == "initialization" || userInput == "in")
		{
			initialization();
		}
		else if (userInput == "firstSolve" || userInput == "fs")
		{
			firstSolve();
		}
		else if (userInput == "localOptimization" || userInput == "lo")
		{
			localOptimization();
		}
		else if (userInput == "solve" || userInput == "sl")
		{
			firstSolve();
			localOptimization();
		}
		else if (userInput == "debugOn" || userInput == "don")
		{
			debug = true;
		}
		else if (userInput == "debugOff" || userInput == "doff")
		{
			debug = false;
		}
		else if (userInput == "printOn" || userInput == "pon")
		{
			print = true;
		}
		else if (userInput == "printOff" || userInput == "poff")
		{
			print = false;
		}
		else if (userInput == "cls")
		{
			system("cls");
		}
		else if (userInput == "help")
		{
			cout << "输入\"initialization\"或\"in\"\n\t从文件读入数据并初始化。" << endl;
			cout << "输入\"firstSolve\"或\"fs\"\n\t寻找初始解。" << endl;
			cout << "输入\"localOptimization\"或\"lo\"\n\t在初始解的基础上寻找局部最优解。" << endl;
			cout << "输入\"solve\"或\"sl\"\n\t生成一个局部优化解。" << endl;
			cout << "输入\"directSolve\"或\"ds\"\n\t寻找解。" << endl;
			cout << "输入\"loopSolve\"或\"ls\"\n\t重复寻找解。" << endl;
			cout << "输入\"debug[On\\Off]\"或\"d[on\\off]\"\n\t打开\\关闭具体信息（默认开启）。" << endl;
			cout << "输入\"print[On\\Off]\"或\"p[on\\off]\"\n\t打开\\关闭打印信息（默认开启）。" << endl;
			cout << "输入\"quit\"或\"exit\"\n\t退出。" << endl;
			cout << "输入\"cls\"\n\t清屏。" << endl;
			cout << "输入\"help\"\n\t查看帮助。" << endl;
		}
		else if (userInput == "exit" || userInput == "quit")
		{
			return;
		}
		else
		{
			cout << "无效输入。请重新输入（输入\"help\"查看帮助）" << endl;
		}
		cin.ignore();
	}

}