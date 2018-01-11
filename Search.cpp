#include<iostream>  
#include<ctime>  
#include"ListADT.h"  
using namespace std;  
  
template<typename E>  
void FreqCount(E& value, Frelist<E>& list)  
{  
    if(list.indexOf(value)<0)  
    {  
        list.append(value);  
        return;  
    }  
    list.renovate();  
}  
  
template<typename E>  
void MoveToFront(E& value, MTFlist<E>& list)  
{  
    if(list.indexOf(value)<0)  
    {  
        list.append(value);  
        return;  
    }  
    list.renovate();  
}  
  
template<typename E>  
void Transpose(E& value, Tlist<E>& list)  
{  
    if(list.indexOf(value)<0)  
    {  
        list.append(value);  
        return ;  
    }  
    list.renovate();  
}  
  
int input(int*& p)  
{  
    p = new int[50];  
    int n = 0;  
    do  
    {  
        cin>>p[n++];  
    }while(cin.get()!='\n');  
    return n;  
}  
  
int main()  
{  
    Frelist<int> frelist;  
    MTFlist<int> mtflist;  
    Tlist<int> tlist;  
  
    cout<<"请输入要检索的数字序列,空格隔开，以换行结束"<<endl;  
    int* p;  
    int n = input(p);  
    for(int i=1;i<=n;i++)  
    {  
        FreqCount<int>(p[i-1],frelist);  
        MoveToFront<int>(p[i-1],mtflist);  
        Transpose<int>(p[i-1], tlist);  
    }  
    cout<<"按以上"<<n<<"个数的顺序进行检索\n"<<endl;  
  
    cout<<"采用频率计数自组织线性表启发式规则的检索结果"<<endl;  
    frelist.display();  
  
    cout<<"\n采用移至前端自组织线性表启发式规则的检索结果"<<endl;  
    mtflist.display();  
  
    cout<<"\n采用转置自组织线性表启发式规则的检索结果"<<endl;  
    tlist.display();  
    delete[] p;  
    p = NULL;  

    return 0;
    // system("PAUSE");  
}