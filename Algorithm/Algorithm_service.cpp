//Algorithm_service.cpp
#include"stdafx.h"

using namespace std;
//�����������
typedef int status;
#define SUCCESS 0			//�����ɹ�	
#define ERR_FAILED -1		//���󣺲���ʧ��
#define ERR_BADDATA -2		//���󣺻�����

//������
#define NODE_MAX 512		//���ýڵ������
#define CONNECT_MAX 8		//����ǰ��/������������
#define SERVICE_MAX 16		//���÷��������

//������
status initialization();	//��ʼ��
status firstSolve();		//Ѱ�ҳ�ʼ��
status localOptimization();	//�ֲ��Ż�
status serviceChoose();		//����ѡ��

//���ݽṹ
struct V					//V�ڵ�
{
	//����
	//V* prior[CONNECT_MAX];//ǰ�����
	int next[CONNECT_MAX];	//��̽ڵ�

	//����
	//int s[SERVICE_MAX];	//����
	int t[SERVICE_MAX];		//ʱ��
	int c[SERVICE_MAX];		//��ֵ
};

//ʵ����
V record[NODE_MAX];
int nodeNumber = 0;			//�ڵ�����
int limit = 0;				//ʱ������

int main()
{
	initialization();
	system("pause");
	return 0;
}

//��ʼ��
status initialization()
{
	ifstream leadIn;
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
	ifstream infile;
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
	cout << "�ļ�ͷ����.�ڵ����� = " << nodeNumber << endl;
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
		cout << "���������޷��򿪣����������ļ����ԡ�" << endl;
		return ERR_FAILED;
	}
	cout << "�������ݴ򿪳ɹ�" << endl;
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
		cout << "��ֹ�������޷��򿪣����������ļ����ԡ�" << endl;
		return ERR_FAILED;
	}
	cout << "��ֹ�����ݴ򿪳ɹ�" << endl;
	timeLimit >> limit;
	timeLimit.close();
	if (!limit>0)
	{
		cout << "��ֹ��������Ч����֤ʧ�ܣ����������ļ����ԡ�" << endl;
		return ERR_BADDATA;
	}
	cout << "��ֹ��Ϊ" << limit << "��" << endl << "End." << endl;
	cout << "���ݵ�����ɡ�" << endl;
	leadIn.close();
	return SUCCESS;
}
//Ѱ�ҳ�ʼ��
status firstSolve()
{
	do 
	{

	} while (!serviceChoose());
	return SUCCESS;
}
//�ֲ��Ż�
status localOptimization()
{
	return SUCCESS;
}
//����ѡ��
status serviceChoose()
{
	return SUCCESS;
}