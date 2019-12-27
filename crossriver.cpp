#include <vector>
#include<QString>
#include"crossriver.h"

void aboard(Bank &bank,int direction,std::vector<Cross> &list)       //生成上船的人员列表
{
    if (bank.goodman>=2)
    {
        Cross temp(2,0,direction);
        list.push_back(temp);
    }
    if (bank.wild >= 2)
    {
        Cross temp(0,2,direction);
        list.push_back(temp);
    }
    if (bank.goodman>=1)
    {
        Cross temp(1,0,direction);
        list.push_back(temp);
    }
    if (bank.wild >= 1)
    {
        Cross temp(0,1,direction);
        list.push_back(temp);
    }
    if ((bank.goodman>=1)&&(bank.wild >= 1))
    {
        Cross temp(1,1,direction);
        list.push_back(temp);
    }
}

bool visited_check(std::vector<Time*> &visited, Time &t)     //检查这种情况是否已经在这条路径中出现过
{
    std::vector<Time*>::iterator itr1,itr2;
    itr1=visited.begin();
    itr2=visited.end();
    for (; itr1 !=itr2 ; itr1++)
    {
        if (*(*itr1)==t)
        {
            return true;
        }
    }
    return false;
}

void start_cross(Time &t,std::vector<std::vector<Cross> > &answer,std::vector<Time*> visited)       //树的深度优先遍历的改版
{
    //answer用于储存成功过河的方案
    if (t.bank_left.wild == 0 && t.bank_left.goodman == 0)      //判断是否成功过河
    {
        answer.push_back(t.history);
        delete &t;
        return;
    }
    if (visited_check(visited,t)== false)
    {
        visited.push_back(&t);
    }
    else
    {
        delete &t;
        return;
    }
    std::vector<Cross> list;        //储存上船人员的数组
    std::vector<Cross>::iterator itr1,itr2;
    if (t.boat==0)
    {
        aboard(t.bank_left,0,list);
        itr1=list.begin();
        itr2=list.end();
        for (; itr1 != itr2; itr1++)
        {
            int g=t.bank_left.goodman-itr1->goodman;
            int w= t.bank_left.wild - itr1->wild;
            int g2=t.bank_right.goodman+itr1->goodman;
            int w2= t.bank_right.wild + itr1->wild;
            if ((g>=w||g==0)&&(g2>=w2||g2==0))
            {
                Time *t2=new Time(g, w, g2, w2, 1);
                t2->history=t.history;
                t2->history.push_back(*itr1);
                start_cross(*t2, answer, visited);
            }
        }
    }
    else if (t.boat==1)
    {
        aboard(t.bank_right,1,list);
        itr1=list.begin();
        itr2=list.end();
        for (; itr1 != itr2; itr1++)
        {
            int g=t.bank_left.goodman+itr1->goodman;
            int w= t.bank_left.wild + itr1->wild;
            int g2=t.bank_right.goodman-itr1->goodman;
            int w2= t.bank_right.wild - itr1->wild;
            if ((g>=w||g==0)&&(g2>=w2||g2==0))      //判断是否有传教士被吃
            {
                Time *t3=new Time(g,w,g2,w2,0);
                t3->history=t.history;
                t3->history.push_back(*itr1);
                start_cross(*t3,answer,visited);
            }
        }
    }
    delete visited.back();      //返回上一步的路径状态
}

void solution(std::vector<std::vector<Cross> > &answer)
{
    std::vector<Time*>  visited;     //存储已访问过的节点,使用指针节省空间
    Time *t=new Time(3,3,0,0,0);      //初始状态
    start_cross(*t,answer,visited);
}

QString about()
{
    QString a="在河的左岸有三个传教士和三个野人，传教士们想用这条船将所有的成员运到河的右岸，但是受到以下条件的限制：\n1.一条船最多只能装下两个人\n2.传教士和野人都会划船\n3.在河的任何一方或者船上，如果野人的人数大于传教士的人数，那么传教士就会被野人吃掉";
    return a;
}


