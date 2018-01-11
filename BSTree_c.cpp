#include<iostream>
#include<iomanip>
using namespace std;

/*
   基于C语言实现二叉查找树

*/

class tree //节点链表结构的声明
{  
	public :
	int data; //节点数据
	class tree *left,*right; //节点左指针和右指针 
};

typedef class tree node;
typedef node* btree;

btree creat_tree(btree,int);
void pre(btree);
void in(btree);
void post(btree);

int main(){
    int arr[]={7,4,1,5,16,8,11,12,15,9,2};//原始数组内容 
    btree ptr=NULL; //声明树根 
	cout<<"[原始数组内容]"<<endl;
	for (int i=0;i<11;i++)//建立二叉树，并将二叉树内容打印出来 
	{  
		ptr=creat_tree(ptr,arr[i]);
		cout<<"["<<setw(2)<<arr[i]<<"] ";
	}
	cout<<endl;
	cout<<"[二叉树的内容]"<<endl;
	cout<<"前序遍历结果："<<endl;//打印前、中、后序遍历结果 
	pre(ptr);
	cout<<endl;
	cout<<"中序遍历结果："<<endl;
	in(ptr);
	cout<<endl;
	cout<<"后序遍历结果："<<endl;
	post(ptr);
    cout<<endl;
    
    while(1){}
	// system("pause");
	return 0;
}

btree creat_tree(btree root,int val){//建立二叉树的子程序 
    btree newnode,current,backup;
    newnode = new node();
    newnode->data = val;
    newnode->left = NULL;
    newnode->right = NULL;
    if(root == NULL){
        root = newnode;
        return root;
    }else{
        for(current=root;current!=NULL;) //current复制root，以保留当前的树根值 
		{  
			backup=current; //保留父节点 
			if(current->data > val)//比较树根节点和新节点数据 
				current=current->left;
			else
				current=current->right;
		}
		if(backup->data >val)//把新节点和树根连接起来 
			backup->left=newnode;
		else
			backup->right=newnode;

        return root;
    }
}

void pre(btree ptr){ //前序遍历 
    if(ptr==NULL)
        return;
    
    cout<<"["<<setw(2)<<ptr->data<<"] ";
    pre(ptr->left);
    pre(ptr->right);
}

void in(btree ptr){ //中序遍历 
    if(ptr==NULL)
        return;

    in(ptr->left);
    cout<<"["<<setw(2)<<ptr->data<<"] ";
    in(ptr->right);
}

void post(btree ptr){//后序遍历
    if(ptr == NULL){
        return;
    }

    post(ptr->left);
    post(ptr->left);
    cout<<"["<<setw(2)<<ptr->data<<"] ";
}