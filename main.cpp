#include<iostream>

using namespace std;

struct Node{
	Node(int c,int e):cof(c),exp(e),next(NULL){};
	Node()=default;
	int cof;
	int exp;
	Node* next;
};

class Link{
private:
    Node* phead;
    Node* pend;
public:
    Link(){
        phead=new Node();
        pend=phead;
    };
    ~Link(){};
    void GetElem(int c,int e);
    void output();
    void multiply(Link a,Link b);
};

void Link::GetElem(int c,int e){
    Node* pnode=new Node(c,e);
    if(phead!=NULL){
        pend->next=pnode;
    }else{
        phead->next=pnode;
        pend=phead;
        pend->next=pnode->next;
    }
        pend=pnode;
}

void Link::output(){
    Node * head = phead;
    cout<<head->next->cof<<"x"<<head->next->exp;
    head=head->next;
    while(head->next!=NULL){
        cout<<"+"<<head->next->cof<<"x"<<head->next->exp;
        head=head->next;
    }
    cout<<endl;
    return ;
}

void Link::multiply(Link a,Link b){
    cout<<a.phead->next->cof<<" dvd";
    while(a.phead->next!=NULL&&b.phead->next!=NULL){
        if(a.phead->next->exp==b.phead->next->exp){
            if(a.phead->next->cof+b.phead->next->cof!=0)
                GetElem(a.phead->next->cof+b.phead->next->cof,a.phead->next->exp);
            a.phead->next=a.phead->next->next;
            b.phead->next=b.phead->next->next;
        }else if(a.phead->next->exp>b.phead->next->exp){
            GetElem(a.phead->next->cof,a.phead->next->exp);
            a.phead->next=a.phead->next->next;
        }else{
            GetElem(b.phead->next->cof,b.phead->next->exp);
            b.phead->next=b.phead->next->next;
        }
    }
    while(a.phead->next!=NULL){
        GetElem(a.phead->next->cof,a.phead->next->exp);
        a.phead->next=a.phead->next->next;
    }
    while(b.phead->next!=NULL){
        GetElem(b.phead->next->cof,b.phead->next->exp);
        b.phead->next=a.phead->next->next;
    }
}
int main(){
	Link P1,P2,result;
	int n;
	cin>>n;
	while(n--){
        int c,e;
        cin>>c>>e;
        P1.GetElem(c,e);
	}
	P1.output();
    cin>>n;
	while(n--){
        int c,e;
        cin>>c>>e;
        P2.GetElem(c,e);
	}
	P2.output();
    result.multiply(P1,P2);
    cout<<"23333"<<endl;
    result.output();
	return 0;
}
