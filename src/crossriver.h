#ifndef CROSSRIVER_H
#define CROSSRIVER_H

#include<vector>
#include<QString>
struct Bank     //河岸
{
    int goodman;
    int wild;
    Bank(int g,int w): goodman(g), wild(w){}
    bool operator==(Bank &b){
        if (goodman==b.goodman&&wild==b.wild)
            return true;
        else
            return false;
    }
};

struct Cross        //每次过河的情形
{
    int goodman;
    int wild;
    int boat_direction;     //0表示从左往右，1表示从右往左
    Cross(int g=0,int w=0,int d=0): goodman(g), wild(w), boat_direction(d){}
};

struct Time     //某一个时刻河两岸的人数以及船的位置
{
    Bank bank_left,bank_right;
    int boat;       //0表示船在左边，1表示船在右边
    std::vector<Cross> history;
    Time(int g, int w,int g2,int w2,int b):bank_left(g,w),bank_right(g2,w2),boat(b){}
    bool operator==(Time &t){
        if (bank_right==t.bank_right&&bank_left==t.bank_left&&boat==t.boat)
        return true;
        else
        return false;
    }
};
void solution(std::vector<std::vector<Cross> > &answer);
void aboard(Bank &bank,int direction,std::vector<Cross> &list);
QString about();
#endif // CROSSRIVER_H
