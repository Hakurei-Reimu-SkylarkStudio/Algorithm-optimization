// Algorithm.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#define MAXSIZE 1000


int A[MAXSIZE + 1][MAXSIZE + 1], B[MAXSIZE + 1][MAXSIZE + 1];
int c[MAXSIZE + 1], w[MAXSIZE + 1];
int F(int n, int v)		//n为物品数量，v是剩余体积
{
	if (n == 0)return 0;		//如果数量不为0
	if (!A[n][v] && v >= c[n])	//如果A[N][V]等于0且剩余空间足够
		A[n][v] = F(n - 1, v - c[n]) + w[n];	//A[N][V]等于F(n-1,v-c[N])加上n包裹的价值
	if (!B[n][v])
		B[n][v] = F(n - 1, v);	//如果B[N][V]等于0，B[N][V]等于F(n-1,v)
	return A[n][v]>B[n][v] ? A[n][v] : B[n][v];//比较返回最大值
}


int main(int argc, char*argv[])
{

	int n, v;
	//memset(A, 0, sizeof(A));
	//memset(B, 0, sizeof(B));
	//ifstreamin("in.txt");
	//ofstreamout("out.txt");
	using std::cin;
	using std::cout;
	using std::endl;
		cin >> n >> v;
	for (int i = 1; i <= n; i++)
		cin >> c[i] >> w[i];
	cout << F(n, v);
	return 0;
}