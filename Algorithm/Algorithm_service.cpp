//Algorithm_service.cpp
#include"stdafx.h"
//�ļ���д��http://blog.csdn.net/kingstar158/article/details/6859379/

//#include"Background.h"

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
	//ǰ����
	V * prior[1];	//ǰ�����
	V * next[1];	//��̽ڵ�

					//����
	int s[1];	//����
	int t[1];	//ʱ��
	int c[1];	//��ֵ
};
//���ݽṹ
struct ss
{
	int * a[20];
};

V * v;

status initialization()
{
	//cout << v[0].s[0];
	return SUCCESS;
}

int main()
{
	initialization();
	return 0;
}
