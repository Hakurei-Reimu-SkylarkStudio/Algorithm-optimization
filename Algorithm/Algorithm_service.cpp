//Algorithm_service.cpp
#include<iostream>
#include"stdafx.h"

#define SUCCESS 0
#define ERR_FILEFILED -1
#define ERR_NOGOODDATA -2

const int MAX_SIZE = 100;	//��󳤶�


class SP //����ʵ��
{
public:
	int initialization();

private:
	int l = { 0 };	//�������
	int s[MAX_SIZE] = { 0 };	//��������
	int c[MAX_SIZE] = { 0 };	//�������
	int t[MAX_SIZE] = { 0 };	//����ʱ��
};
int main()
{
	return 0;
}