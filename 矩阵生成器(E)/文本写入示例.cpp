#include <fstream>
#include <iostream>
#incldue <string>
#include"stdafx.h"

int main()
{
	ofstream location_out;
	string ss;
	ss = “(1, 2)”;
	location_out.open("location_out.txt", std::ios::out | std::ios::app);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
	if (!location_out.is_open())
		return 0;

	location_out << ss << endl;
	location_out << “(” << 5 << “, ” << 10 << “) \n”;    　//将”(5,10) 回车”写入.txt文件中

	location_out.close();