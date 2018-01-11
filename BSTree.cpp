#include<iostream>
using namespace std;

//二叉查找树的节点结构
template <typename T>
struct BSNode
{
    BSNode(T t)
    : value(t), lchild(NULL), rchild(NULL){}
 
    BSNode() {};
 
    T value;
    BSNode<T>* lchild;
    BSNode<T>* rchild;
};

template <typename T>
class BSTree{
    public:
        BSTree();
        ~BSTree(){};

        void preOrder();
        void inOrder();
        void postOrder();
        void layerOrder();

        void insert(T key);    //插入指定值节点
        void remove(T key);    //删除指定值节点
        bool find(T key);
        //BSNode<T>* find(T key);
        void destory();        //销毁二叉树
        void print();        //打印二叉树
    private:
        BSNode<T>* root; //根节点 
        void add(T t);
        void preOrder(BSNode<T>* p);
        void inOrder(BSNode<T>* p);
        void postOrder(BSNode<T>* p);
};

template <typename T>
void BSTree<T>::remove(T t){
    if(find(t)){
        BSNode<T>* cur = root;
        BSNode<T>* parent = NULL; 
        BSNode<T>* del = NULL;

        while(cur && cur->value!=t){
            parent = cur;
            if(cur->value >t ){
                cur = cur->lchild;
            }else{
                cur = cur->rchild;
            }
        }

        del = cur;

        if(cur == root){
            if(cur->lchild == NULL){
                root = cur->rchild;
            }else if(cur->rchild == NULL){
                root = cur->lchild;
            }else{
                BSNode<T>* precursor = cur->lchild;
                BSNode<T>* par = cur;
                while(precursor->rchild){
                    par = precursor;
                    precursor = precursor->rchild; 
                }
                cur->value = precursor->value;
                if(par != cur){
                    par->rchild = precursor->lchild;
                }else{
                    par->lchild = precursor->lchild;
                }
                del = precursor;
            }

        }else{
            if(cur->lchild == NULL){
                if(cur == parent->lchild){
                    parent->lchild = cur->rchild;
                }else{
                    parent->rchild = cur->rchild;
                }
            }else if(cur->rchild == NULL){
                if(cur == parent->lchild){
                    parent->lchild = cur->lchild;
                }else{
                    parent->rchild = cur->lchild;
                }
            }else{
                BSNode<T>* precursor = cur->lchild;
                BSNode<T>* par = cur;
                while(precursor->rchild){
                    par = precursor;
                    precursor = precursor->rchild; 
                }
                cur->value = precursor->value;
                if(par != cur){
                    par->rchild = precursor->lchild;
                }else{
                    par->lchild = precursor->lchild;
                }
                del = precursor;
            }
        }

        delete del;
    }else{
        cout<<"The element is not exixt.\n";
    }
}


// template <typename  T>
// BSNode<T>* BSTree<T>::find(T key){
//     BSNode<T>* cur = root;
//     while(cur!=NULL){
//         if(cur->value == key){
//             return cur;
//         }
//         if(cur->value > key){
//             cur = cur->lchild;
//         }else{
//             cur = cur->lchild;
//         }
//     }

//     return NULL;
// }

template <typename  T>
bool BSTree<T>::find(T key){
    BSNode<T>* cur = root;
    while(cur!=NULL){
        if(cur->value == key){
            return true;
        }
        if(cur->value > key){
            cur = cur->lchild;
        }else{
            cur = cur->rchild;
        }
    }

    return false;
}

template <typename  T>
void BSTree<T>::add(T t){
    BSNode<T>* n = new BSNode<T>(t);
    BSNode<T>* cur = root;
    BSNode<T>* head;
    while(cur!=NULL){
        head = cur;
        if(cur->value < t){
            cur = cur->rchild;
        }else{
            cur = cur->lchild;
        }
    }

    if(head->value < t){
        head->rchild = n;
    }else{
        head->lchild = n;
    }
}

template <typename T>
BSTree<T>::BSTree(){
    root = NULL;
}

template <typename T>
void BSTree<T>::insert(T t){
    if(root == NULL){
        root = new BSNode<T>(t);
    }else{
        if(find(t)){
            cout<<"The element is exixt\n";
            return;
        }
        add(t);
    }
}

template <typename T>
void BSTree<T>::preOrder(BSNode<T>* p){
    if(p == NULL)
        return;
    
    cout<<"["<<p->value<<"] ";
    preOrder(p->lchild);
    preOrder(p->rchild);
}

template <typename T>
void BSTree<T>::inOrder(BSNode<T>* p){
    if(p == NULL)
        return;
    
    inOrder(p->lchild);
    cout<<"["<<p->value<<"] ";
    inOrder(p->rchild);
}

template <typename T>
void BSTree<T>::postOrder(BSNode<T>* p){
    if(p == NULL)
        return;
    
    postOrder(p->lchild);
    postOrder(p->rchild);
    cout<<"["<<p->value<<"] ";
}



template <typename T>
void BSTree<T>::preOrder(){
    preOrder(root);
}

template <typename T>
void BSTree<T>::inOrder(){
    inOrder(root);
}

template <typename T>
void BSTree<T>::postOrder(){
    postOrder(root);
}



int main(){
    int arr[]={8,9,11,3,12,5,6};
    BSTree<int> tree = BSTree<int>();
    
    for(int i=0;i<7;i++){
        tree.insert(arr[i]);
    }

    tree.preOrder();  cout<<endl;
    tree.inOrder();     cout<<endl;
    tree.postOrder();   cout<<" remove 12\n";
  
    tree.remove(12);

    tree.preOrder();  cout<<endl;
    tree.inOrder();     cout<<endl;  cout<<"remove 3 .root\n";
    tree.remove(3);
    
        tree.preOrder();  cout<<endl;
        tree.inOrder();     cout<<endl;

        cout<<"remove 8 .root\n";
        tree.remove(8);
        
            tree.preOrder();  cout<<endl;
            tree.inOrder();     cout<<endl;

    int a[] = {7,19,1};
    for(int i=0;i<3;i++){
        tree.insert(a[i]);
    }

    tree.preOrder();  cout<<endl;
    tree.inOrder();     cout<<endl;
    tree.postOrder();

    while(1){}
    return 0;
}