#include<iostream>
using namespace std;

class Node{
    public:
        int  s;
        int  u;
        Node* next;
        Node(int a,int b){
            s = a;
            u = b;
            next = NULL;
        }
        Node(){
            next = NULL;
        }
};

class Link{
    private:
        Node* head;
        int size;
    public:
        Link(){
            head = NULL;
            size = 0;
        }
        Link add(Link l);
        // void add(Link l);  //传入一个多项式，实现相加，结果存在当前链表

        void add(int s,int u);
        void insert(Node* n);
        void print();
        int length(){return size;};
        const Node* Head(){return head;};   //保证返回值不被修改
};

Link Link::add(Link l){
    Link r = Link();
    const Node* t = l.Head();
    Node* n = head;
    // if(t==NULL){
    //     return this;
    // }
    while(t->next!=NULL && n->next!=NULL){
        if(t->u == n->u){
            int s = t->s+n->s;
            if(s==0){
                t = t->next;
                n = n->next;
                continue;
            }
            
            r.add(s,t->u);
            t = t->next;
            n = n->next;
        }else if(t->u > n->u){
            r.add(t->s,t->u);
            t = t->next;
        }else{
            r.add(n->s,n->u);
            n = n->next;
        }
    }

    while(t!=NULL){
        r.add(t->s,t->u);
        t = t->next;
    }

    while(n!=NULL){
        r.add(n->s,n->u);
        n = n->next;
    }

    return r;
}

// void Link::add(Link l){
//     const Node* t = l.Head();
//     while(t!=NULL){
//         add(t->s,t->u);
//         t = t->next;
//     }
// }

void Link::print(){
    Node* cur = head;
    int flag=0;
    while(cur != NULL){
        if(flag == 0){
            cout<<cur->s<<"x^"<<cur->u;
            flag=1;
        }else{
            if(cur->s > 0){
                cout<<"+"<<cur->s<<"x^"<<cur->u;
            }else{
                cout<<cur->s<<"x^"<<cur->u;
            }
        }
        cur = cur->next;
    }
}

void Link::add(int s,int u){
    if(head == NULL){
        head = new Node(s,u);
    }else{
        Node* n = new Node(s,u);
        insert(n);   
    }

    size++;
}

void Link::insert(Node* n){
    Node * cur = head;
    Node* par = head;
    while(cur!=NULL){
        if(n->u >= cur->u){
            break;
        }
        par = cur;
        cur = cur->next;
    }

    if(cur == head){   //头部插入
        if(cur->u == n->u){
            head->s +=n->s;    //当系数为0时
            if(head->s == 0){
                if(head->next == NULL){
                    head = NULL;
                }else{
                    Node* t = head;
                    head = head->next;
                    delete t;
                }
            }
        }else{
            n->next = head;
            head = n;
        }
    }else if(cur == NULL){  //尾部插入
        par->next = n;
    }else{
        if(cur->u == n->u){
            cur->s +=n->s;
            if(cur->s == 0){   //当系数相等时
                Node* t = cur;
                par->next = cur->next;
                delete t;
            }
        }else{
            n->next = cur;
            par->next = n;
        }
    }
}

int main(){
    int n=0;
    cout<<"请输入第一个多项式:\n";
    cin>>n;
    Link l = Link();
    for(int i=0;i<n;i++){
        int s,u;
        cin>>s>>u;
        l.add(s,u);
    }
    cout<<"您输入的第一个多项式:  ";
    l.print();
    cout<<endl;
    
    cout<<"请输入第二个多项式:\n";
    cin>>n;
    Link ll = Link();
    for(int i=0;i<n;i++){
        int s,u;
        cin>>s>>u;
        ll.add(s,u);
    }
    cout<<"您输入的第二个多项式:  ";
    ll.print();
    cout<<endl;
    
    cout<<"求和结果:  ";
    Link r = l.add(ll);
    r.print();
    

    while(1){}
    return 0;
}
