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

struct SP
{
	int t[1];
	int s[1];
	int c[1];
};
struct V
{
	SP sp[1];
};
struct G
{
	V v[1];
};

status globalLnitialization();

int main()
{
	G g;
	

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