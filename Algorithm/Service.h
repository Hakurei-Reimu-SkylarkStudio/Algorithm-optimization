#pragma once

#define Success 0;
#define OverFlew -1;
#define Empty -2;


typedef int state;

//V��ʾ�ڵ㼯��
struct V
{
	unsigned cost;
};
//E��ʾ����߼���
struct E
{
	unsigned value;
};
class Single
{
public:
	void reset();
	state 
	~Single();

private:

};

Single::Single()
{
}

Single::~Single()
{
}
