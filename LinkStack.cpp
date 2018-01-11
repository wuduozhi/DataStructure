#include<iostream>
using namespace std;

/*链表节点结构*/
template <typename T>
struct Node
{
    Node(T t) :value(t), next(NULL){};
    Node() :next(NULL){};
public:
    T value;
    Node<T>* next;
};

template <typename T>
class LinkStack{
    private:
        Node<T>* head;
        int count;
    public:
        LinkStack();
        ~LinkStack();
        bool isEmpty();
        int size();
        void push(T t);
        T pop();
        T top();
};

template <typename T>
LinkStack<T>::LinkStack(){
    count = 0;
    head = new Node<T>();
};

template <typename T>
LinkStack<T>::~LinkStack(){
    Node<T> *del,*temp;
    del = head;
    while(del!=NULL){
        temp = del->next;
        delete del;
        del = temp;
    }
};

/*返回栈的大小*/
template <typename T>
int LinkStack<T>::size()
{
     return count;
};
/*栈的判空操作*/
template <typename T>
bool LinkStack<T>::isEmpty()
{
     return count == 0;
};

/*插入元素*/
template <typename T>
void LinkStack<T>::push(T t){
    Node<T>* n = new Node<T>(t);
    n->next = head->next;
    head->next = n;
    count++;
};

/*弹栈*/
template <typename T>
T LinkStack<T>::pop(){
    if(head->next !=NULL){
        Node<T>* del = head->next;
        head->next = del->next;
        T v = del->value;
        delete del;
        count--;
        return v;
    }
};

/*获取栈顶元素*/
template <typename T>
T LinkStack<T>::top()
{
    if (head->next!=NULL)
        return head->next->value;
};

int main(){
    LinkStack <string> lstack;
    lstack.push("hello");
    lstack.push("to");
    lstack.push("you!");
 
    cout << "Size:" << lstack.size() << endl;
    cout <<"Top:"<< lstack.top() << endl;
 
    while (!lstack.isEmpty())
    {
        cout<<lstack.pop()<<" ";
    }
 
    cout << "Size:" << lstack.size() << endl;

    while(1){}
    return 0;
}