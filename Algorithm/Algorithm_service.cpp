//Algorithm_service.cpp



//�ļ���д��http://blog.csdn.net/kingstar158/article/details/6859379/

#include<iostream>
#include<fstream>
#include <cassert>
#include <string>
#include"stdafx.h"

#define SUCCESS 0
#define ERR_FILEFILED -1
#define ERR_NOGOODDATA -2

using namespace std;

const int MAX_SIZE = 100;	//��󳤶�

typedef int status;

int E[MAX_SIZE][MAX_SIZE];	//�����߹�ϵ��E��


class SP //����ʵ��
{
public:
	status initialization();	//��ʼ��
	int l = { 0 };	//�������
	int s[MAX_SIZE] = { 0 };	//��������
	int c[MAX_SIZE] = { 0 };	//�������
	int t[MAX_SIZE] = { 0 };	//����ʱ��
};

status SP::initialization()
{
	return SUCCESS;
}

status globalLnitialization();

int main()
{
	SP sp[300];
	string strTemp;	//��ʱ����
	int intTemp;	//��ʱ����
	fstream matIn;
	matIn.open("MatIn.txt");	//��ȡ�ڵ���ϵ��E
	if (!matIn)
		cout << "MatIn open filed." << endl;
	matIn >> intTemp;
	cout << intTemp;
	matIn.close();
	return 0;
}
status initialization()
{
	return SUCCESS;
}
//
//int main() {
//	string buffer;
//	ifstream in("MatIn.txt");
//	if (!in.is_open())
//	{
//		cout << "Error opening file"; exit(1);
//	}
//	while (!in.eof())
//	{
//		in.getline(buffer, 100);
//		cout << buffer << endl;
//	}
//	return 0;
//}