#include<iostream>
#include <stdlib.h>
using namespace std;

/*
E data:节点元素的值
Node<E> pre :前驱指针
Node<E> next：后继指针
*/
template <typename E>
class Node{
    public:
        E data;
        Node<E>* pre;
        Node<E>* next;
        Node(){}
        Node(E e,Node<E>* p=NULL,Node<E>* n=NULL){
            data = e;
            pre = p;
            next = n;
        }
};



template <typename E>
class MyDoubleLink{
    private:
        Node<E>* head;
        Node<E>* end;
        int count;
        Node<E>* getNode(int index);
    public:
        MyDoubleLink(){
            head = NULL;
            end = NULL;
            count = 0;
        };
        ~MyDoubleLink(){};
        void add(E e);
        void insert(int index,E value);
        E del(int index);
        E get(int index);
        Node<E>* getHead(){
            return head;
        }
        int getLength();
};

template <typename E>
E MyDoubleLink<E>::del(int index){
    if(index<0 || index>=count){
        cout<<"Index Error.\n";
        exit;
    }else{
        if(index==0){
            E value = head->data;
            Node<E>* d = head;
            end->next = head->next;
            head->next->pre = head->pre;
            head = head->next;
            delete d;
            count--;
            return value;
        }else if(index==count-1){
            // Node<E>* n = getNode(index-1);
            Node<E>* d = end;
            end->next->pre = end->pre;
            end->pre->next = end->next;
            end = end->pre;
            E value = d->data;
            delete d;
            count--;
            return value;
        }else{
            // Node<E>* n = getNode(index-1);
            Node<E>* d = getNode(index);
            d->pre->next = d->next;
            d->next->pre = d->pre;
            E value = d->data;
            delete d;
            count--;
            return value;
        }
    }
}

template <typename E>
void MyDoubleLink<E>::insert(int index,E value){
    if(index<0 || index>count){
        cout<<"Index Error.\n";
        exit;
    }else{
        //在头结点处插入
        if(index == 0){
            Node<E>* n = new Node<E>(value);
            n->next = head;
            n->pre = end;
            head->pre = n;
            end->next = n;
            head = n;
            count++;
        }else if(index==count){
            Node<E>* n = new Node<E>(value);
            n->next = head;
            n->pre = end;
            head->pre = n;
            end->next = n;
            end = n;
            count++;
        }else{
            Node<E>* n = new Node<E>(value);
            Node<E>* temp = getNode(index-1);
            n->next = temp->next;
            n->pre = temp;
            temp->next->pre = n;
            temp->next = n;
            count++;
        }
    }
}

template <typename E>
Node<E>* MyDoubleLink<E>::getNode(int index){
    if(index>=count){
        cout<<"Index Error.\n";
        exit;
    }else{
        Node<E>* temp = head;
        while(index){
            temp = temp->next;
            index--;
        }

        return temp;
    }
}

//尾部插入
template <typename E>
void MyDoubleLink<E>::add(E value){
    if(head == NULL){
        head = new Node<E>(value);
        end = head;
        count++;
    }else{
        Node<E>* n = new Node<E>(value);
        end->next = n;
        n->pre = end;
        n->next = head;
        end = n;
        head->pre = end;
        count++;
    }
}

//去数据
template <typename E>
E MyDoubleLink<E>::get(int index){
    if(index<0 ||index>=count){
        cout<<"Index Error.\n";
        exit;
    }else{
        Node<E>* temp = getNode(index);
        E value = temp->data;
        return value;
    }
}

template <typename E>
int MyDoubleLink<E>::getLength(){
    return count;
}


int main(){
    MyDoubleLink<int> link;
    for(int i=0;i<10;i++){
        link.add(i);
    } 

    for(int i=0;i<link.getLength();i++){
        int a = link.get(i);
        cout<<a<<" ";
    }

    link.insert(0,100);
    link.insert(3,1111);
    link.insert(link.getLength(),1010010);

    cout<<"\nTest Insert.\n";
    for(int i=0;i<link.getLength();i++){
        int a = link.get(i);
        cout<<a<<" ";
    }

    cout<<"\nTest del.\n";
    cout<<link.del(0)<<" ";
    cout<<link.del(4)<<" ";
    cout<<link.del(link.getLength()-1)<<endl;
    for(int i=0;i<link.getLength();i++){
        int a = link.get(i);
        cout<<a<<" ";
    }

    cout<<"\nTest Rectangle:\n";
    Node<int>* h =link.getHead();
   
    for(int i=0;i<30;i++){
        int a = h->data;
        cout<<a<<" ";
        h = h->next;
    }


    while(1){}
    return 0;
}