#include"stdafx.h"

using namespace std;

//�����������

typedef int status;
#define SUCCESS 0
#define ERR_FILEFILED -1
#define ERR_NOGOODDATA -2

//�������

//������
status initialization();	//��ʼ��
//������

//�������ݽṹ
struct V	//V�ڵ�
{
public:
	//ǰ����
	V * prior[1];	//ǰ�����
	V * next[1];	//��̽ڵ�

	//����
	int s[1];	//����
	int t[1];	//ʱ��
	int c[1];	//��ֵ
};
//���ݽṹ