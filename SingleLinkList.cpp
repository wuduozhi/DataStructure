#include<iostream>
#include <stdlib.h>
using namespace std;

template <typename E> class Node{
public:
    E data;
    Node<E> * next;
    Node(){
        next = NULL;
    }
    Node(E e){
        data = e;
        next = NULL;
    }
};

template <typename E> class MySingleLink{
    private:
        Node<E>* head;
        Node<E>* end;
        int size;
        Node<E>* getNode(int index);
    public:
        MyLinkList(){
            head = NULL;
            end = head;
            size = 0;
        }   
        void add(E e);
        void insert(E e,int position);
        E get(int position);
        E del(int position);
        void clear();
        void reverse();
        bool IsEmpty() {return head->next == NULL ? true : false;}; 
        int getLength(){return size;}

        void print(){
            for(int i=0;i<size;i++){
                cout<<get(i)<<" ";
            }
        }
};

template <typename E>
void MySingleLink<E>::reverse(){
    Node<E> *p,*q,*r;
    p = head;
    r = NULL;
    while(p!=NULL){
        q = p;
        p = p->next;
        q->next = r;
        r = q;
    }
    head = q;
    end = getNode(size-1);
}


template <typename E>
void MySingleLink<E>::clear(){
    Node<E>* d = head;
    Node<E>* temp;
    while(d!=NULL){
        temp = d->next;
        delete d;
        d = temp;
    }
    head = NULL;
    end = head;
    size = 0;
}

template <typename E>
E MySingleLink<E>::del(int index){
    if(index<0 || index>=size){
        cout<<" Index error.\n";
        exit;
    }

    if(index == 0){
        Node<E>* d = head;
        head = head->next;
        E value = d->data;
        delete d;
        size--;
        return value;
    }else if(index==size-1){
        Node<E>* d = end;
        Node<E>* temp = getNode(index-1);
        end = temp;
        end->next = NULL;     //要记得讲为节点的指针变为NULL
        E value = d->data;
        delete d;
        size--;
        return value;
    }else{
        Node<E>* temp = getNode(index-1);
        Node<E>* d = temp->next;
        temp->next = d->next;
        E value = d->data;
        delete d;
        size--;
        return value;
    }
}

template <typename E>
void MySingleLink<E>::insert(E e,int position){
    if(position==0){
        Node<E>* n = new Node<E>(e);
        n->next = head;
        head = n;
        size++;
    }else if(position==size){
        add(e);
    }else{
        Node<E>* n = new Node<E>(e);
        Node<E>* temp = getNode(position-1);
        n->next = temp->next;
        temp->next = n;
        size++;
    }
}

template <typename E>
Node<E>* MySingleLink<E>::getNode(int index){
    if(index<0 || index>=size){
        cout<<"Position Error.\n";
        exit;
    }else{
        Node<E>* temp = head;
        while(index!=0){
            temp = temp->next;
            index--;
        }
        return temp;
    }
}

template <typename E>
void MySingleLink<E>::add(E e){
    if(head == NULL){
        head = new Node<E>(e);
        end = head;
        size++;
    }else{
        Node<E>* n = new Node<E>(e);
        end->next = n;
        end = n;
        size++;
    }
}

template <typename E>
E MySingleLink<E>::get(int index){
    if(index<0 || index>=size){
        cout<<"Position Error.\n";
        exit;
    }else{
        Node<E>* temp = getNode(index);
        return temp->data;
    }
}

int main(){
    MySingleLink<int> link =MySingleLink<int>();

    cout<<"本例是用链表实现的线性表.\n";
    cout<<"测试添加功能：请输入添加数据的总数与要添加的数据，以空格隔开。如 4 1 2 3 4 \n";
    int n;
    cin>>n;
    while(n){
        int v ;
        cin>>v;
        link.add(v);
        n--;
    }
    cout<<"Size :"<<link.getLength()<<endl;
    cout<<"元素为：";
    link.print();
    cout<<endl;

    cout<<"测试插入功能：请输入需要插入的数据。前一个为位置，后一个为数据，以空格隔开。如 1 3 \n";
    int s,v;
    cin>>s>>v;
    link.insert(s,v);
    cout<<"Size :"<<link.getLength()<<endl;
    cout<<"元素为：";
    link.print();
    cout<<endl;

    cout<<"测试删除功能：请输入需要删除的下标。如 1  \n";
    cin>>s;
    link.del(s);
    cout<<"Size :"<<link.getLength()<<endl;
    cout<<"元素为：";
    link.print();
    cout<<endl;

    cout<<"反转功能\n";
    cout<<"反转后: ";
    cout<<"元素为：";
    link.print();
    cout<<endl;

    while(1){}
    return 0;
}