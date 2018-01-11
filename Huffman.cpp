#include<iostream>
#include <deque>
#include<algorithm>
using namespace std;

/*哈夫曼树的节点定义*/
template <typename T>
struct HuffmanNode
{
    HuffmanNode(T k,HuffmanNode<T>*l=NULL,HuffmanNode<T>* r=NULL)
        :key(k),lchild(l), rchild(r){}
    ~HuffmanNode(){};
 
    T key;                                     //节点的权值
    HuffmanNode<T>* lchild;        //节点左孩
    HuffmanNode<T>* rchild;        //节点右孩
};

template <typename T>
class Huffman
{
public:
    void preOrder();              //前序遍历哈夫曼树
    void inOrder();                  //中序遍历哈夫曼树
    void postOrder();              //后序遍历哈夫曼树
 
    void creat(T a[], int size);  //创建哈夫曼树
    void destory();                  //销毁哈夫曼树
    void print();                  //打印哈夫曼树

    Huffman();
    ~Huffman();
 
private:
    void preOrder(HuffmanNode<T>* pnode);
    void inOrder(HuffmanNode<T>* pnode);
    void postOrder(HuffmanNode<T>*pnode);
    void print(HuffmanNode<T>*pnode);
    void destroy(HuffmanNode<T>*pnode);
 
private:
    HuffmanNode<T>* root;     //哈夫曼树根节点
    deque<HuffmanNode<T>*> forest;//森林
};

/*默认构造函数*/
template<typename T>
Huffman<T>::Huffman():root(NULL){
    forest = deque<HuffmanNode<T>*>();
};
/*析构函数*/
template<typename T>
Huffman<T>::~Huffman()
{
    destroy(root);
};
/*创建哈夫曼树*/
template<typename T>
void Huffman<T>::creat(T a[],int size)
{
	for (int i = 0; i < size; i++) //每个节点都作为一个森林
	{
		HuffmanNode<T>* ptr = new HuffmanNode<T>(a[i],NULL,NULL);
		forest.push_back(ptr);
	}
	for (int i = 0; i < size - 1; i++)
	{
		sort(forest.begin(), forest.end(), [](HuffmanNode<T>* a, HuffmanNode<T>*b){return a->key< b->key; });
		HuffmanNode<T>*node = new HuffmanNode<T>(forest[0]->key + forest[1]->key, forest[0], forest[1]);
		forest.push_back(node);
		forest.pop_front();
		forest.pop_front();
	}
	root = forest.front();
	forest.clear();
};


/*前序遍历哈夫曼树*/
template <typename T>
void Huffman<T>::preOrder(HuffmanNode<T>* pnode){
    if (pnode != NULL){
        cout << pnode->key;
        preOrder(pnode->lchild);
        preOrder(pnode->rchild);
    }
};

template <typename T>
void Huffman<T>::preOrder(){
    preOrder(root);
};

/*中序遍历哈夫曼树*/
template <typename T>
void Huffman<T>::inOrder(HuffmanNode<T>* pnode){
    if (pnode != NULL){
        inOrder(pnode->lchild);
        cout << pnode->key;
        inOrder(pnode->rchild);
    }
};
template <typename T>
void Huffman<T>::inOrder(){
    inOrder(root);
};

/*后序遍历哈夫曼树*/
template <typename T>
void Huffman<T>::postOrder(HuffmanNode<T>* pnode){
    if (pnode != NULL){
        postOrder(pnode->lchild);
        postOrder(pnode->rchild);
        cout << pnode->key;
    }
};
template <typename T>
void Huffman<T>::postOrder(){
    postOrder(root);
};

/*打印哈夫曼树*/
template<typename T>
void Huffman<T>::print(HuffmanNode<T>* pnode)
{
    if (pnode != NULL){
        cout << "当前结点：" << pnode->key<<".";
        if (pnode->lchild != NULL)
           cout << "它的左孩子节点为：" << pnode->lchild->key << ".";
        else 
           cout << "它没有左孩子.";
        if (pnode->rchild != NULL)
            cout << "它的右孩子节点为：" << pnode->rchild->key << ".";
        else 
            cout << "它没有右孩子.";
        
        cout << endl;
        print(pnode->lchild);
        print(pnode->rchild);
    }
};

template <typename T>
void Huffman<T>::print()
{
    print(root);
};
/*销毁哈夫曼树*/
template <typename T>
void Huffman<T>::destory(){
    destroy(root);
};
template<typename T>
void Huffman<T>::destroy(HuffmanNode<T>* pnode){
    if (pnode != NULL){
        destroy(pnode->lchild);
        destroy(pnode->rchild);
        delete pnode;
        pnode = NULL;
    }
};

int main(){
    Huffman<int> huff= Huffman<int>();
    int a[] = { 10,20,30,40 };
    huff.creat(a, 4);    //构建一棵哈夫曼树
    huff.print();        //打印节点间关系
    while(1){}
    return 0;
}