// 矩阵生成器(E).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include<time.h>

#define NODE_MAX 10 //节点最大数目

using namespace std;

int main()
{
	srand(time(0));
	ofstream matOut;
	int length;
	length = rand()%NODE_MAX+NODE_MAX;
	cout << length;
	int node[NODE_MAX][NODE_MAX];
	for (int i = 0; i < NODE_MAX; i++)
	{
		for (int j = 0; j < i; j++)
		{
			node[i][j] = rand()% RAND_MAX;
		}

	}
	for (int i = 0; i < NODE_MAX; i++)
	{
		for (int j = 0; j < i; j++)
		{
			cout<<node[i][j]<<' ';
		}
		cout << endl;

	}
    return 0;
}
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//#define random(x) (rand()%x)
//
//void main()
//{
//
//	srand((int)time(0));
//	for (int x = 0; x<10; x++)
//		printf("%d/n", random(100));
//}