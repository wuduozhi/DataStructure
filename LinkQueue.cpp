#include<iostream>
#include <stdlib.h>
using namespace std;

/*
链队列是基于链表实现的队列，它不存在数组的O（n）的元素移动问题或空间浪费问题。我们所要确定的就是链表哪头做队首，哪头做队尾。
显然我们应该以链表头部为队首，链表尾部为队尾。存储一个指向队尾的指针，方便从链表尾插入元素；使用带头节点的链表，方便从链表头删除元素。
*/

template<typename T>
struct Node
{
    Node(T t) :value(t), next(NULL){}
    Node(){}
 
    T value;
    Node<T> * next;
};

template <typename T>
class LinkQueue{
    private:
        Node<T>* phead;
        Node<T>* pend;
        int count;
    public:
        LinkQueue();
        ~LinkQueue();
     
        bool isEmpty();
        int size();
        bool pop();
        void push(T t);
        T front();
};

template <typename T>
LinkQueue<T>::LinkQueue(){
    phead = new Node<T>();
    pend = phead;
    count = 0;
};

template <typename T>
LinkQueue<T>::~LinkQueue()
{
    while (phead->next != NULL)
    {
        Node<T> * pnode = phead;
        phead = phead->next;
        delete pnode;
    }
};

template <typename T>
bool LinkQueue<T>:: isEmpty()
{
    return count==0;
};

template <typename T>
int LinkQueue<T>::size()
{
    return count;
};

//在队尾插入
template <typename T>
void LinkQueue<T>::push(T t){
    Node<T> * pnode = new Node<T>(t);
    pend->next = pnode;
    pend = pnode;
    count++;
};

//在队首弹出
template <typename T>
bool LinkQueue<T>::pop(){
    if(count == 0){
        return false;
    }
    Node<T>* pnode = phead->next;
    phead->next = phead->next->next;
    delete pnode;
    count--;
    return true;
};

//获取队首元素
template<typename T>
T LinkQueue<T>::front()
{
    if(isEmpty()){
        cout<<"Queue is empty.\n";
        exit;
    }

    return phead->next->value;
};

int main(){
    LinkQueue<string> lqueue;
    lqueue.push("one");
    lqueue.push("two");
    lqueue.push("three");
    lqueue.push("four");
    lqueue.push("five");
    cout << "Queue Size: "<< lqueue.size() << endl;
    while (!lqueue.isEmpty())
    {
        cout << lqueue.front() << endl;
        lqueue.pop();
    }
    while(1){}
    return 0;
}