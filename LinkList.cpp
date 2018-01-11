#include <stdlib.h>  
#include<iostream>
using namespace std;  
  
/*
    基于链表实现线性表

*/


//结点类  
class Node {  
public:  
    int data;  
    Node *pNext;  
};  
  
//单向链表类  
class LinkList {  
public:  
    LinkList() {  
        //头结点不参与计数  
        head = new Node;  
        head->data = 0;  
        head->pNext = NULL;  
        size = 0;
    }  
    ~LinkList() { delete head; }  
    void CreateLinkList(int n);             //创建链表  
    void InsertNode(int position, int d);   //在指定位置插入结点  
    void TraverseLinkList();                //遍历链表  
    bool IsEmpty();                         //判断链表是否为空  
    int GetLength();                        //链表长度  
    int DeleteNode(int position);          //删除指定位置结点  
    void DeleteLinkList();                  //删除整个链表  
private:  
    Node *head;
    int size;  
};  

//创建n个节点的链表
void LinkList::CreateLinkList(int n) {  
    if (n < 0) {  
        cout << "输入结点个数错误！" << endl;  
        exit(EXIT_FAILURE);  
    }  
    else {  
        Node *pnew, *ptemp;  
        ptemp = head;  
        int i = n;    
        while (n-- > 0) {  
            pnew = new Node;  
            cout << "输入第" << i - n << "个结点值：";  
            cin >> pnew->data;  
            pnew->pNext = NULL;  
            ptemp->pNext = pnew;  
            ptemp = pnew;     
        }  
    }  
}  
//postion从1开始计数，到链表长度加1结束，头结点后的结点称为第一个结点  
void LinkList::InsertNode(int position, int d) {  
    if (position < 0 || position > GetLength() + 1) {  
        cout << "输入位置错误！" << endl;  
        exit(EXIT_FAILURE);  
    }  
    else {  
        Node *pnew, *ptemp;  
        ptemp = head;  
        pnew = new Node;  
        pnew->data = d;  
        pnew->pNext = NULL;  
  
        while (position-- > 1)  
            ptemp = ptemp->pNext;  
        pnew->pNext = ptemp->pNext;  
        ptemp->pNext = pnew;  
    }  
}  
  
void LinkList::TraverseLinkList() {  
    Node *p = head->pNext;   
    while (p != NULL) {  
        cout << p->data << " ";  
        p = p->pNext;  
    }  
    cout << endl;  
}  
  
bool LinkList::IsEmpty() {  
    if (head->pNext == NULL)  
        return true;  
    else  
        return false;  
}  
  
int LinkList::GetLength() {  
    Node *p = head->pNext;  
    int n = 0;  
    while (p != NULL) {  
        n++;  
        p = p->pNext;  
    }  
    return n;  
}  
//position只能从1开始到链表长度结束  
int LinkList::DeleteNode(int position) {  
    if (position < 0 || position > GetLength()) {  
        cout << "输入位置错误！" << endl;  
        exit(EXIT_FAILURE);  
    }  
    else {        
        Node *ptemp = head, *pdelete;  
        while (position-- > 1)  
            ptemp = ptemp->pNext;  
        pdelete = ptemp->pNext;  
        ptemp->pNext = pdelete->pNext; 
        int value = pdelete->data; 
        delete pdelete;  
        pdelete = NULL;  

        return value;
    }  
}  
  
//删除整个链表  注意释放空间
void LinkList::DeleteLinkList() {  
    Node *pdelete = head->pNext, *ptemp;  
    while(pdelete != NULL) {  
        ptemp = pdelete->pNext;  
        head->pNext = ptemp;  
        delete pdelete;  
        pdelete = ptemp;  
    }  
}  
  
//测试函数  
int main() {  
    LinkList l;  
    int position = 0, value = 0, n = 0;  
    bool flag = false;  
  
    cout << "请输入需要创建单向链表的结点个数：";  
    cin >> n;  
    l.CreateLinkList(n);  
  
    cout << "打印链表值如下：";  
    l.TraverseLinkList();  
  
    cout << "请输入插入结点的位置和值：";  
    cin >> position >> value;  
    l.InsertNode(position, value);  
      
    cout << "打印链表值如下：";  
    l.TraverseLinkList();  
  
    cout << "请输入要删除结点的位置：";  
    cin >> position;  
    l.DeleteNode(position);  
  
    cout << "打印链表值如下：";  
    l.TraverseLinkList();  
  
    l.DeleteLinkList();  
    flag = l.IsEmpty();  
    if (flag)  
        cout << "删除链表成功！" << endl;  
    else  
        cout << "删除链表失败！" << endl;  
  
    return 0;  
}