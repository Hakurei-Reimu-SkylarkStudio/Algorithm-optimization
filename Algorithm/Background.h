#include"stdafx.h"

using namespace std;

//创建错误代码

typedef int status;
#define SUCCESS 0
#define ERR_FILEFILED -1
#define ERR_NOGOODDATA -2

//错误代码

//函数体
status initialization();	//初始化
//函数体

//创建数据结构
struct V	//V节点
{
public:
	//前后驱
	V * prior[1];	//前驱结点
	V * next[1];	//后继节点

	//服务
	int s[1];	//名称
	int t[1];	//时间
	int c[1];	//价值
};
//数据结构