//Algorithm_service.cpp



//文件读写：http://blog.csdn.net/kingstar158/article/details/6859379/

#include<iostream>
#include<fstream>
#include <cassert>
#include <string>
#include"stdafx.h"

#define SUCCESS 0
#define ERR_FILEFILED -1
#define ERR_NOGOODDATA -2

using namespace std;

const int MAX_SIZE = 100;	//最大长度

typedef int status;

int E[MAX_SIZE][MAX_SIZE];	//构建边关系（E）


class SP //服务实例
{
public:
	status initialization();	//初始化
	int l = { 0 };	//服务个数
	int s[MAX_SIZE] = { 0 };	//服务名称
	int c[MAX_SIZE] = { 0 };	//服务费用
	int t[MAX_SIZE] = { 0 };	//服务时间
};

status SP::initialization()
{
	return SUCCESS;
}

status globalLnitialization();

int main()
{
	SP sp[300];
	string strTemp;	//临时储存
	int intTemp;	//临时储存
	fstream matIn;
	matIn.open("MatIn.txt");	//读取节点间关系表E
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