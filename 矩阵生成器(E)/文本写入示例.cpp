#include <fstream>
#include <iostream>
#incldue <string>
#include"stdafx.h"

int main()
{
	ofstream location_out;
	string ss;
	ss = ��(1, 2)��;
	location_out.open("location_out.txt", std::ios::out | std::ios::app);  //��д������ļ�ĩβ��ӵķ�ʽ��.txt�ļ���û�еĻ��ʹ������ļ���
	if (!location_out.is_open())
		return 0;

	location_out << ss << endl;
	location_out << ��(�� << 5 << ��, �� << 10 << ��) \n��;    ��//����(5,10) �س���д��.txt�ļ���

	location_out.close();