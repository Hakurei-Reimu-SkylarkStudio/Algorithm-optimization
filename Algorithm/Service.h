#pragma once

#define Success 0;
#define OverFlew -1;
#define Empty -2;


typedef int state;

//V表示节点集合
struct V
{
	unsigned cost;
};
//E表示有向边集合
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
