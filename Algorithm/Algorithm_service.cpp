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
	int countNext;			//�����

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
status serviceChoose();		//����ѡ��
status chose(const int i);	//��������ѡ��
int sumUp(SolveQuene[]);	//ֵ�ۼ���

//ʵ����
V record[NODE_MAX];
SolveQuene solveQuene[NODE_MAX];	//������
SolveQuene tempQuene[NODE_MAX];		//�����н�������

int nodeNumber = 0;			//�ڵ�����
int limit = 0;				//ʱ������
bool debug = { true };		//����debug��Ϣ��ӡ���

int main()					//������
{
	initialization();
	for (int i = 0; i < 10; i++)
	{
		firstSolve();
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
			cout << "�޷�������������ǰ�˳���" << endl;
		}
		loop++;
	} while (serviceChoose() != SUCCESS);
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
		cout << "��ֵ" << sumUp(solveQuene) << endl;
	}
	return SUCCESS;
}
//�ֲ��Ż�
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
//����ѡ��
status serviceChoose()
{
	if (chose(1)==SUCCESS)
	{
		return SUCCESS;
	}
	return ERR_NOSOLVE;
}
//����ѡ��ݹ���
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
	return ERR_NOSOLVE;	//����Warning��
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