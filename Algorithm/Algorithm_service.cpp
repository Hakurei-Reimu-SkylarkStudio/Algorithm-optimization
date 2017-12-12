//Algorithm_service.cpp
#include<iostream>
#include"stdafx.h"

#define SUCCESS 0
#define ERR_FILEFILED -1
#define ERR_NOGOODDATA -2

const int MAX_SIZE = 100;	//最大长度


class SP //服务实例
{
public:
	int initialization();

private:
	int l = { 0 };	//服务个数
	int s[MAX_SIZE] = { 0 };	//服务名称
	int c[MAX_SIZE] = { 0 };	//服务费用
	int t[MAX_SIZE] = { 0 };	//服务时间
};
int main()
{
	return 0;
}