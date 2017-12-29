//Algorithm_service.cpp
#include"stdafx.h"

using namespace std;
//�����������
typedef int status;
#define SUCCESS 0			//�����ɹ�	
#define ERR_FAILED -1		//���󣺲���ʧ��
#define ERR_BADDATA -2		//���󣺻�����
#define ERR_NOSOLVE -3		//�����޽�

//������
#define NODE_MAX 512		//���ýڵ������
#define CONNECT_MAX 8		//����ǰ��/������������
#define SERVICE_MAX 16		//���÷��������
#define SEARCH_DEEPTH 1024	//����ѭ����������

//���ݽṹ
struct V					//V�ڵ�
{
	//����
	//V* prior[CONNECT_MAX];//ǰ�����
	int next[CONNECT_MAX];	//��̽ڵ�
	int nextCount;			//�����

	//����
	//int s[SERVICE_MAX];	//����
	int t[SERVICE_MAX];		//ʱ��
	int c[SERVICE_MAX];		//��ֵ
	int serviceCount;		//������
};
struct SolveQuene			//������
{
	int quene = 0;			//ѡ�����
	int service = 0;		//ѡ�з���
};

//������
status initialization();	//��ʼ��
status firstSolve();		//Ѱ�ҳ�ʼ��
status localOptimization();	//�ֲ��Ż�
status serviceChoose(SolveQuene quene[]);
							//����ѡ��
status chose(SolveQuene quene[], const int i);
							//��������ѡ��
int sumUp(SolveQuene[]);	//ֵ�ۼ���

//ʵ����
V record[NODE_MAX];
SolveQuene solveQuene[NODE_MAX];	//�����
SolveQuene downTempQuene[NODE_MAX];	//�·�����н�������
SolveQuene upTempQuene[NODE_MAX];	//�Ϸ�����н�������

int nodeNumber = 0;			//�ڵ�����
int limit = 0;				//ʱ������
bool debug = { true };		//����debug��Ϣ��ӡ���

int main()					//������
{
	initialization();		//��ʼ��
	for (int i = 0; i < 10000; i++)
	{
		firstSolve();			//Ѱ�ҳ�ʼ��
		localOptimization();	//�ֲ��Ż�
	}
	
	system("pause");
	return 0;
}

//��ʼ��
status initialization()
{
	srand(static_cast<unsigned>(time(0)));			//��ʼ�������
	ifstream leadIn;		//�����õ�����
	string chrLeadIn;
	cout << "ָ�������ļ�:";
	do
	{
		cin >> chrLeadIn;
		leadIn.open(chrLeadIn);
		if (leadIn)
			break;
		cout << "�ļ��޷���,�����������ԡ�";
	} while (!leadIn);
	for (int i = 0; i < NODE_MAX; i++)
	{
		for (int j = 0; j < CONNECT_MAX; j++)
		{
			record[i].next[j] = 0;	//�ÿ�
		}
	}
	ifstream infile;		//�ڵ����õ�����
	string strInfile;
	leadIn >> strInfile;
	infile.open(strInfile);
	if (!infile)
	{
		cout << "�ڵ������ļ��޷���,���������ļ����ԡ�";
		return ERR_FAILED;
	}
	cout << "�ڵ������ļ��򿪳ɹ�" << endl;
	infile >> nodeNumber;		//��һ������Ϊ�ڵ�����
	if (debug)
	{
		cout << "�ļ�ͷ����.�ڵ����� = " << nodeNumber << endl;
	}
	if (nodeNumber>NODE_MAX)
	{
		cout << "�ڵ������࣬��������ú����ԡ�" << endl;
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
	ifstream SP;				//�������ݵ�����
	string strSP;
	leadIn >> strSP;
	SP.open(strSP);
	if (!SP)
	{
		cout << "���������޷��򿪣����������ļ����ԡ�" << endl;
		return ERR_FAILED;
	}
	cout << "�������ݴ򿪳ɹ�" << endl;
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
	ifstream timeLimit;			//��ֹ�����ݵ�����
	string chrTimeLimit{ 0 };
	leadIn >> chrTimeLimit;
	timeLimit.open(chrTimeLimit);
	if (!timeLimit)
	{
		cout << "��ֹ�������޷��򿪣����������ļ����ԡ�" << endl;
		return ERR_FAILED;
	}
	cout << "��ֹ�����ݴ򿪳ɹ�" << endl;
	timeLimit >> limit;
	timeLimit.close();
	if (!(limit>0))
	{
		cout << "��ֹ��������Ч����֤ʧ�ܣ����������ļ����ԡ�" << endl;
		return ERR_BADDATA;
	}
	if (debug)
	{
		cout << "��ֹ��Ϊ" << limit << "��" << endl ;
	}
	cout << "End." << endl;
	cout << "���ݵ�����ɡ�" << endl;
	cout << "End." << endl;
	leadIn.close();
	return SUCCESS;			//�����ɹ�����
}
//Ѱ�ҳ�ʼ��
status firstSolve()
{
	solveQuene[1].quene = 1;
	//int locate = 1;
	int loop{ 0 };
	//Ѱ��һ������ĳ�ʼ�����
	do
	{
		int i = 2;
		//��ս����
		for (int x = 0; x < NODE_MAX; x++)
		{
			solveQuene[i].quene = 0;
		}
		//�׽����Ѱ·
		while (solveQuene[i - 1].quene != nodeNumber)
		{
			solveQuene[i].quene = record[solveQuene[i - 1].quene].next[rand() % record[solveQuene[i - 1].quene].nextCount];
			solveQuene[0].quene = i;
			i++;
		}
		if (loop>SEARCH_DEEPTH)
		{
			cout << "Ԥ��������Դ�ľ�����ǰ�˳���" << endl;
			break;
		}
		loop++;
	} while (serviceChoose(solveQuene) != SUCCESS);
	solveQuene[0].service = sumUp(solveQuene);	//��ż�ֵ
	if (debug)
	{
		int i = 1;
		cout << "��ʼ��";
		for(int i=1;i<= solveQuene[0].quene;i++)
		{
			cout << "->" << solveQuene[i].quene;
		}
		cout << endl;
		cout << "·������" << solveQuene[0].quene;
		cout << endl;
		cout << "��ֵ" << solveQuene[0].service;
		cout << endl;
	}
	return SUCCESS;
}
//�ֲ��Ż�
status localOptimization()
{
	//����һ�ݵ�ǰ״̬
	for (int  i = 0; i <= solveQuene[0].quene; i++)
	{
		downTempQuene[i].quene = solveQuene[i].quene;
		downTempQuene[i].service = solveQuene[i].service;
	}
	//ʹ�ø���Ѱ��·������ֵ
	for (int i = solveQuene[0].quene; i > 0; i--)
	{

		//Ѱ�ҷ�֧��
		if (record[downTempQuene[i].quene].nextCount > 1)
		{
			int loadNode{ 0 };	//��¼��ǰ�ڵ㵽��һ�ڵ��next���
			for (int j = 0; j < record[downTempQuene[i].quene].serviceCount; j++)
			{
				if (record[downTempQuene[i].quene].next[j] == downTempQuene[i + 1].quene)
				{
					loadNode = j;
					break;
				}
			}
			//���ϣ�С�ˣ�Ѱ������·��
			if (loadNode>0)
			{
				//���ϲ����ڽڵ���ص������
				downTempQuene[i+1].quene =record[downTempQuene[i].quene].next[loadNode-1];		//�л��ڵ㵽�϶�����·��
				if (downTempQuene[i + 1].quene == 17)
				{
					downTempQuene[0].quene = i + 1;	//��¼·������
				}
				else
				{
					int loop{ i + 2 };
					do
					{
						//�϶�·��������·��������
						downTempQuene[loop].quene = record[downTempQuene[loop - 1].quene].next[record[downTempQuene[loop - 1].quene].nextCount - 1];
						//downTempQuene[0].quene = loop;	//�·�ͳһ��ֵ��С����
						loop++;
					} while (downTempQuene[loop].quene != 17);
					downTempQuene[0].quene = loop - 1;	//��¼·������
				}
				//���������
				if (serviceChoose(downTempQuene) == SUCCESS)
				{
					downTempQuene[0].service = sumUp(downTempQuene);
					if (debug)
					{
						int i = 1;
						cout << "��������У�·����";
						for (int i = 1; i <= downTempQuene[0].quene; i++)
						{
							cout << "->" << downTempQuene[i].quene;
						}
						cout << endl;
						cout << "·������" << downTempQuene[0].quene;
						cout << endl;
						cout << "��ֵ" << downTempQuene[0].service << endl;
					}
					break;
				}
			}
		}
	}
	return SUCCESS;
}
//����ѡ��
status serviceChoose(SolveQuene quene[])
{
	if (chose(quene,1)!=SUCCESS)
	{
		return ERR_NOSOLVE;
	}
	return SUCCESS;
}
//����ѡ��ݹ���
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
//ֵ�ۼ���
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