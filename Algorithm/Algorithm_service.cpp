//Algorithm_service.cpp
#include"stdafx.h"
#include<fstream>
#include<string>
#include<iomanip>
//�ļ���д��http://blog.csdn.net/kingstar158/article/details/6859379/
#include"stdafx.h"

using namespace std;
//�����������
typedef int status;
#define SUCCESS 0
#define ERR_FILEFILED -1
#define ERR_NOGOODDATA -2
//������
#define NODE_MAX 512	//���ýڵ������
#define CONNECT_MAX 8	//����ǰ��/������������
#define SERVICE_MAX 16	//���÷��������
//������
status initialization();	//��ʼ��
//���ݽṹ
struct V	//V�ڵ�
{
	//ǰ����
	//V * prior[CONNECT_MAX];	//ǰ�����
	int next[CONNECT_MAX];	//��̽ڵ�

	//����
	int s[SERVICE_MAX];	//����
	int t[SERVICE_MAX];	//ʱ��
	int c[SERVICE_MAX];	//��ֵ
};
//���ݽṹ

V record[NODE_MAX];
int nodeNumber = 0;	//�ڵ�����

status initialization()
{
	for (int i = 0; i < NODE_MAX; i++)
	{
		for (int j = 0; j < CONNECT_MAX; j++)
		{
			record[i].next[j] = 0;	//�ÿ�
		}
	}
	cout << "ָ�������ļ���";
	ifstream infile;
	string data;
	do
	{
		cin >> data;
		infile.open(data);
		if (infile)
			break;
		cout << "�ļ��޷���,������������:";
	} while (!infile);
	cout << "�����ļ��򿪳ɹ�" << endl;
	infile >> nodeNumber;	//��һ������Ϊ�ڵ�����
	cout << "�ļ�ͷ����.�ڵ����� = "<<nodeNumber<<endl;
	if (nodeNumber>NODE_MAX)
	{
		cout << "�ڵ������࣬��������ú�����" << endl;
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
