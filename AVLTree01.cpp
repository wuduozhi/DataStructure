#include<iostream>
using namespace std;

template <typename T>
struct AVLTreeNode
{
	AVLTreeNode(T value, AVLTreeNode<T>*l, AVLTreeNode<T>*r)
	:key(value), lchild(l), rchild(r){}

	T key;
	int height; 
	AVLTreeNode<T>* lchild;
	AVLTreeNode<T>* rchild;
};

template<typename T>
class AVLTree
{
public:
	AVLTree();			//构造函数
	~AVLTree();			//析构函数

	void preOrder();	//前序遍历AVL树
	void InOrder();		//中序遍历AVL树	
	void postOrder();	//后序遍历AVL树

	void print();		//打印AVL树
	void destory();		//销毁AVL树

	void insert(T key);	//插入指定值的节点
	void remove(T key);	//移除指定值的节点

	AVLTreeNode<T>* search_recurse(T key);	//利用递归算法进行指定值的查找
	AVLTreeNode<T>* search_iterator(T key);	//利用迭代算法进行指定值的查找
	T minimum();		//返回AVL中的最小值
	T maximum();		//返回AVL中的最大值

	int height();		//返回树的高度

private:
	AVLTreeNode<T>* root;	//AVL树的根节点

private:
	void preOrder(AVLTreeNode<T>* pnode) const;
	void inOrder(AVLTreeNode<T>* pnode) const;
	void postOrder(AVLTreeNode<T>* pnode) const;

	void print(AVLTreeNode<T>* pnode,T key, int direction) const;
	void destory(AVLTreeNode<T>* & pnode);

	int height(AVLTreeNode<T>* pnode) ;
	int max(int a, int b);

	AVLTreeNode<T>* insert(AVLTreeNode<T>* &pnode, T key);		
	AVLTreeNode<T>* remove(AVLTreeNode<T>* & pnode, T key); //删除AVL树中节点pdel，并返回被删除的节点

	AVLTreeNode<T>* minimum(AVLTreeNode<T>*pnode)const;
	AVLTreeNode<T>* maximum(AVLTreeNode<T>*pnode)const;

	AVLTreeNode<T>* search_recurse(AVLTreeNode<T>* pnode, T key) const;
	AVLTreeNode<T>* search_iterator(AVLTreeNode<T>* pnode, T key) const;

	AVLTreeNode<T>* leftRotation(AVLTreeNode<T>* pnode);		//单旋:左旋操作
	AVLTreeNode<T>* rightRotation(AVLTreeNode<T>* pnode);		//单旋:右旋操作
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* pnode);	//双旋:先左旋后右旋操作
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* pnode);	//双旋:先右旋后左旋操作

};

/*构造函数*/
template <typename T>
AVLTree<T>::AVLTree()
:root(NULL){};

/*析构函数*/
template <typename T>
AVLTree<T>::~AVLTree()
{
	destory(root);
}

/*返回两者中的较大者*/
template<typename T>
int AVLTree<T>::max(int a, int b)
{
	return a > b ? a : b;
};

/*返回树中最大节点值*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* pnode)const
{
	if (pnode != NULL)
	{
		while (pnode->rchild != NULL)
			pnode = pnode->rchild;
		return pnode;
	}
	return NULL;
};

template<typename T>
T AVLTree<T>::maximum()
{
	AVLTreeNode<T>* presult = maximum(root);
	if (presult != NULL)
		return presult->key;
};

/*返回树中最小节点值*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* pnode)const
{
	if (pnode != NULL)
	{
		while (pnode->lchild != NULL)
			pnode = pnode->lchild;
		return pnode;
	}
	return NULL;
};

template<typename T>
T AVLTree<T>::minimum()
{
	AVLTreeNode<T>* presult = minimum(root);
	if (presult != NULL)
		return presult->key;
};

/*返回一棵树的高度*/
template <typename T>
int AVLTree<T>::height(AVLTreeNode<T>* pnode) 
{
	if (pnode != NULL)
	{
		return pnode->height;
	}
	return 0;																//如果是空树，高度为0
};

template <typename T>
int AVLTree<T>::height()
{
	return height(root);
};

/*左旋转操作*/
/*pnode为最小失衡子树的根节点*/
/*返回旋转后的根节点*/

template<typename T>
AVLTreeNode<T>* AVLTree<T>::leftRotation(AVLTreeNode<T>* proot){
    AVLTreeNode<T>* root = proot->rchild;
    proot->rchild = root->lchild;
    root->lchild = proot;

    proot->height = max(height(proot->lchild),height(proot->rchild))+1;
    root->height = max(height(root->lchild), height(root->rchild)) + 1; //更新节点的高度值
    return root;
}

/*右旋转操作*/
/*pnode为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template <typename  T>
AVLTreeNode<T>* AVLTree<T>::rightRotation(AVLTreeNode<T>*proot){
    AVLTreeNode<T>* root = proot->lchild;
    proot->lchild = root->rchild;
    root->rchild = proot;

    proot->height = max(height(proot->lchild),height(proot->rchild))+1;
    root->height = max(height(root->lchild), height(root->rchild)) + 1; //更新节点的高度值
    return root;
}


/*先左后右做旋转*/
/*参数proot为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* proot){
    proot->lchild = leftRotation(proot->lchild);
    return rightRotation(proot);
}

/*先右旋再左旋*/
/*参数proot为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template<typename T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* proot)
{
	proot->rchild = rightRotation(proot->rchild);
	return leftRotation(proot);
};

/*插入操作*/
/*递归地进行插入*/
/*返回插入后的根节点*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &pnode, T key){
    if(pnode == NULL){  //寻找到插入的位置
        pnode = new AVLTreeNode<T>(key,NULL,NULL);
    }else if(key > pnode->key){
        pnode->rchild = insert(pnode->rchild,key);   //插入值比当前结点值大，插入到当前结点的右子树上
        if(height(pnode->rchild) - height(pnode->lchild)==2){   //插入后出现失衡
            if(key > pnode->rchild->key){                     //情况一：插入右子树的右节点，进行左旋
                pnode = leftRotation(pnode); 
            }else if(key<pnode->rchild->key){               //情况三：插入右子树的左节点,进行先右再左旋转
                pnode = rightLeftRotation(pnode);
            }
        }
    }else if(key < pnode->key){
        pnode->lchild = insert(pnode->lchild,key);
        if (height(pnode->lchild) - height(pnode->rchild) == 2) { //如果插入导致失衡
			if (key < pnode->lchild->key)		//情况二：插入到左子树的左孩子节点上，进行右旋
				pnode = rightRotation(pnode);
			else if (key>pnode->lchild->key)
				pnode = leftRightRotation(pnode);//情况四：插入到左子树的右孩子节点上，进行先左后右旋转
		}
    }

    pnode->height = max(height(pnode->lchild), height(pnode->rchild)) + 1;
	return pnode;
}

template <typename T>
void AVLTree<T>::insert(T key){
	insert(root, key);
};

/*递归查找指定元素*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_recurse(T key)
{
	return search_recurse(root,key);
};
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_recurse(AVLTreeNode<T>* pnode, T key) const
{
	if (pnode != NULL)
	{
		if (key == pnode->key)
			return pnode;
		if (key > pnode->key)
			return search_recurse(pnode->rchild,key);
		else
			return search_recurse(pnode->lchild,key);
	}
	return NULL;
};

/*非递归查找指定元素*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_iterator(T key)
{
	return search_iterator(root, key);
};
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_iterator(AVLTreeNode<T>* pnode, T key) const
{
	while (pnode != NULL)
	{
		if (pnode->key == key)
			return pnode;
		else if (key > pnode->key)
			pnode = pnode->rchild;
		else
			pnode = pnode->lchild;
	}
	return NULL;
};

/*中序遍历*/
template<typename T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* pnode) const
{
	if (pnode != NULL)
	{
		inOrder(pnode->lchild);
		cout << pnode->key<<" ";
		inOrder(pnode->rchild);
	}
};

template<typename T>
void AVLTree<T>::InOrder()
{
	inOrder(root);
};

/*前序遍历*/
template<typename T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* pnode) const
{
	if (pnode != NULL)
	{
		cout << pnode->key <<" ";
		preOrder(pnode->lchild);
		preOrder(pnode->rchild);
	}
};
template<typename T>
void AVLTree<T>::preOrder()
{
	preOrder(root);
};

/*后列遍历*/
template<typename T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* pnode) const
{
	if (pnode != NULL)
	{
		postOrder(pnode->lchild);
		postOrder(pnode->rchild);
		cout << pnode->key <<" ";
	}
}
template<typename T>
void AVLTree<T>::postOrder()
{
	postOrder(root);
};

/*删除指定元素*/
template<typename T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* & pnode, T key){
	if(pnode != NULL){
		if(key == pnode->key){ 
			if(pnode->lchild != NULL && pnode->rchild != NULL){
				//左子树比右子树高,在左子树上选择节点进行删除
				if(height(pnode->lchild) > height(pnode->rchild)){
					//使用左子树最大节点来代替被删节点，而删除该最大节点
					AVLTreeNode<T>* ppre = maximum(pnode->lchild);
					pnode->key = ppre->key;
					pnode->lchild = remove(pnode->lchild,ppre->key);
				}else{
					//在右子树上选择最小节点进行删除
					AVLTreeNode<T>* psuc = minimum(pnode->rchild);
					pnode->key = psuc->key;
					pnode->rchild = remove(pnode->rchild,psuc->key);
				}
			}else{
				AVLTreeNode<T>* ptemp = pnode;
				if(pnode->lchild != NULL){
					pnode = pnode->lchild;
					delete ptemp;
					return pnode;
				}else if(pnode->rchild != NULL){
					pnode = pnode->rchild;
					delete ptemp;
					return pnode;
				}else{
					delete ptemp;
					return NULL;
				}
			}
		}else if(key > pnode->key){  //要删除的节点比当前节点大，则在右子树进行删除
			pnode->rchild = remove(pnode->rchild,key);
			 //删除右子树节点导致不平衡:相当于情况二或情况四
			 if(height(pnode->lchild) - height(pnode->rchild) == 2){
				 //相当于在左子树上插入右节点造成的失衡（情况四）
				if(height(pnode->lchild->rchild)>height(pnode->lchild->lchild)){
					pnode = leftRightRotation(pnode);
				}else{ //相当于在左子树上插入左节点造成的失衡（情况二）
					pnode = rightRotation(pnode);
				}
			 }
		}else if(key < pnode->key){
			pnode->lchild = remove(pnode->lchild,key);
			//删除左子树节点导致不平衡：相当于情况三或情况一
            if (height(pnode->rchild) - height(pnode->lchild) == 2){
                //相当于在右子树上插入左节点造成的失衡（情况三）
                if (height(pnode->rchild->lchild)>height(pnode->rchild->rchild))
                    pnode = rightLeftRotation(pnode);
                else//相当于在右子树上插入右节点造成的失衡（情况一）
                    pnode = leftRotation(pnode); 
			}
		}

		return pnode;
	}

	return NULL;
}

template<typename T>
void AVLTree<T>::remove(T key)
{
	root =remove(root, key);
};


/*销毁AVL树*/
template<typename T>
void AVLTree<T>::destory(AVLTreeNode<T>* & pnode)
{
	if (pnode != NULL)
	{
		destory(pnode->lchild);
		destory(pnode->rchild);
		delete pnode;
		pnode = NULL;
	}
};
template<typename T>
void AVLTree<T>::destory()
{
	destory(root);
}

int main(){
    AVLTree<int> a = AVLTree<int>();
    for (int i = 0; i < 10; i++){
        a.insert(i);
        
    // //    cout << "Height:" << a.height() << endl;
        
    //     cout << "\nMidle:" << endl;
    //     a.InOrder();
        
    //     cout << "\nFront:" << endl;
    //     a.preOrder();
    
    //     cout << "\nBehind:";
    //     a.postOrder();
    //     cout<< endl<<endl;
	}

	cout << "Height:" << a.height() << endl;
        
	cout << "\nMidle:";
	a.InOrder();
	
	cout << "\nFront:";
	a.preOrder();

	cout << "\nBehind:";
	a.postOrder();
	cout<< endl<<endl;
    
	cout<<"delete 7";
    a.remove(7);
	cout << "\nMidle:";
	a.InOrder();
	
	cout << "\nFront:";
	a.preOrder();

	cout << "\nBehind:";
	a.postOrder();
	cout<< endl<<endl;

	cout<<"delete 3";
    a.remove(3);
	cout << "\nMidle:";
	a.InOrder();
	
	cout << "\nFront:";
	a.preOrder();

	cout << "\nBehind:";
	a.postOrder();
	cout<< endl<<endl;

	cout<<"delete 4";
    a.remove(4);
	cout << "\nMidle:";
	a.InOrder();
	
	cout << "\nFront:";
	a.preOrder();

	cout << "\nBehind:";
	a.postOrder();
	cout<< endl<<endl;

	
   
    AVLTreeNode<int>* b = a.search_iterator(10);
 
    if (b != NULL)
        cout << b->key;
    else
        cout << "Not exixt." << endl;
 
 
    while(1){}
    return 0;
}