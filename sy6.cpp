/**
 * C++: 邻接表表示的"无向图(List Undirected Graph)"
 *
 * @author 小智e
 * @date 2014/04/19
 */

#include <iomanip>
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
using namespace std;

#define MAX 100
// 邻接表
class ListUDG
{
    private: // 内部类
        // 邻接表中表对应的链表的顶点
        class ENode
        {
            public:
                int ivex;           // 该边所指向的顶点的位置
                int use;
                ENode *nextEdge;    // 指向下一条弧的指针
        };

        // 邻接表中表的顶点
        class VNode
        {
            public:
                string data;          // 顶点信息
                ENode *firstEdge;   // 指向第一条依附该顶点的弧
        };

	private: // 私有成员
        int mVexNum;             // 图的顶点的数目
        int mEdgNum;             // 图的边的数目
        VNode mVexs[MAX];
        ofstream outfile;

    public:
        // 创建邻接表对应的图(自己输入)
		ListUDG();
        // // 创建邻接表对应的图(用已提供的数据)
        // ListUDG(char vexs[], int vlen, char edges[][2], int elen);
		~ListUDG();

        // 深度优先搜索遍历图
        void DFS();
        // 广度优先搜索（类似于树的层次遍历）
        void BFS();
        // 打印邻接表图
        void print();
        //获取所有简单路径
        void getAll();

	private:
        // 读取一个输入字符
        string readString();
        // 返回ch的位置
        int getPosition(string ch);
        // 深度优先搜索遍历图的递归实现
        void DFS(int i, int *visited);
        // 深度优先搜索遍历简单路径的递归实现
        void DFS(int i,int end, int *visited,vector<int> v);
        // 将node节点链接到list的最后
        void linkLast(ENode *list, ENode *node);

        void write(vector<int> v);

        int find(int value,vector<int> v){
            for(int i=0;i<v.size();i++){
                if(value == v[i])
                    return i;
            }

            return -1;
        }
};

/*
 * 创建邻接表对应的图(自己输入)
 */
ListUDG::ListUDG(){
    // outfile = o;
    // outfile.open("record.txt");
    string c1,c2;
    int v,e;
    int i,p1,p2;
    ENode *node1,*node2;

    //输入"顶点数" 和 "边数"
    cout<<"Input vertex number: ";
    cin>>mVexNum;
    cout<<"Input edge number: ";
    cin>>mEdgNum;

    if ( mVexNum < 1 || mEdgNum < 1 || (mEdgNum > (mVexNum * (mVexNum-1)))){
        cout << "Input error: invalid parameters!" << endl;
        return ;
    } 

    //初始化"邻接表"的顶点
    for(i=0;i<mVexNum;i++){
        cout<<"Vertex("<<i<<"):";
        mVexs[i].data = readString();
        mVexs[i].firstEdge = NULL;
    }

    //初始化邻接表的边
    for(i=0;i<mEdgNum;i++){
        // 读取边的起始顶点和结束顶点
        cout << "edge(" << i << "): ";
        c1 = readString();
        c2 = readString();
        p1 = getPosition(c1);
        p2 = getPosition(c2);
        //初始化node1
        node1 = new ENode();
        node1->ivex = p2;
        node1->use = 0;
        if(mVexs[p1].firstEdge == NULL){
            mVexs[p1].firstEdge = node1;
        }else{
            linkLast(mVexs[p1].firstEdge, node1);   //添加到末尾
        }

        //初始化node2
        node2 = new ENode();
        node2->ivex = p1;
        node2->use = 0;
         // 将node2链接到"p2所在链表的末尾"
        if(mVexs[p2].firstEdge == NULL){
            mVexs[p2].firstEdge = node2;
        }else{
            linkLast(mVexs[p2].firstEdge, node2);
        }
    }

}

/*
 * 返回ch的位置
 */
int ListUDG::getPosition(string ch){
    int i;
    for(i=0; i<mVexNum; i++)
        if(mVexs[i].data == ch)
            return i;
    return -1;
}


/*
 * 读取一个输入字符
 */
string ListUDG::readString(){
    string str;
    cin>>str;
    return str;
}

/*
 * 将node节点链接到list的最后
 */
void ListUDG::linkLast(ENode *list, ENode *node){
    ENode *p = list;
    while(p->nextEdge)
        p = p->nextEdge;
    p->nextEdge = node;
}

/*
 * 深度优先搜索遍历图的递归实现
 */
void ListUDG::DFS(int i, int *visited){
    ENode * node;
    visited[i] = 1;
    cout<<mVexs[i].data<<" ";
    node = mVexs[i].firstEdge;
    while(node!=NULL){
        if(!visited[node->ivex]){
            DFS(node->ivex,visited);   //递归
        }

        node = node->nextEdge;
    }
}


/*
 * 深度优先搜索遍历图
 */
void ListUDG::DFS(){
    int i;
    int visited[MAX];       // 顶点访问标记

    // 初始化所有顶点都没有被访问
    for (i = 0; i < mVexNum; i++)
        visited[i] = 0;

    cout << "DFS: ";
    for (i = 0; i < mVexNum; i++){
        if (!visited[i])
            DFS(i, visited);
    }
    cout << endl;
}

/*
 * 打印邻接表图
 */
void ListUDG::print(){
    int i,j;
    ENode *node;

    cout << "List Graph:" << endl;
    for (i = 0; i < mVexNum; i++){
        cout << i << "(" << mVexs[i].data << "): ";
        node = mVexs[i].firstEdge;
        while (node != NULL){
            cout << node->ivex << "(" << mVexs[node->ivex].data << ") ";
            node = node->nextEdge;
        }
        cout << endl;
    }
}


/*
 * 深度优先搜索遍历图的递归实现
 */
void ListUDG::DFS(int i,int end, int *visited,vector<int> v){
    ENode * node;
    visited[i] = 1;
    v.push_back(i);
    // cout<<mVexs[i].data<<" ";
    node = mVexs[i].firstEdge;
    while(node!=NULL){
        if(!visited[node->ivex]){
            if(node->ivex == end){
                for(int k=0;k<v.size();k++){
                    cout<<v[k]<<" ";
                }
                cout<<endl;
                return;
            }
            DFS(node->ivex,end,visited,v);   //递归
            visited[node->ivex] = 0;
            node = node->nextEdge;
        }
    }

    return;
}

/*
    输入起点与终点  找出所有简单路径
*/

void ListUDG::getAll(){
    string start,end;
    cout<<"Please input start point: ";
    cin>>start;
    cout<<"Please input end point: ";
    cin>>end;

    int s = getPosition(start);
    int e = getPosition(end);
    

    vector<int> v;
    int visited[MAX];       // 顶点访问标记
    // 初始化所有顶点都没有被访问
    for (int i = 0; i < mVexNum; i++)
        visited[i] = 0;

    v.push_back(s);
    visited[s] = 1;
    while(!v.empty()){
        if(v[v.size()-1] == e){
            write(v);
            for(int i=0;i<v.size();i++){
                cout<<v[i]<<" ";
            }
            cout<<endl;
            visited[e] = 0;
            v.pop_back();
        }else{
            int n = v[v.size()-1];
            ENode * node = mVexs[n].firstEdge;
            while(node!=NULL){
                if(visited[node->ivex] == 0 && find(node->ivex,v)==-1 && node->use == 0){
                    v.push_back(node->ivex);
                    node->use = 1;
                    visited[node->ivex] = 1;
                    break;
                }
                node = node->nextEdge;
            }
            if(node == NULL){
                visited[n] = 0;
                ENode * node = mVexs[n].firstEdge;
                while(node!=NULL){
                    if(find(node->ivex,v)==-1 ){   //恢复顶点状态
                        node->use = 0;
                        visited[node->ivex] == 0; 
                    }
                    node = node->nextEdge;
                }
                v.pop_back();
            }
        }
    }

}

void ListUDG::write(vector<int> v){
    ofstream outfile;
    outfile.open("record.txt",ios::app);
    for(int i=0;i<v.size();i++){
        if(i==0)
           outfile << mVexs[v[i]].data;
        else
            outfile <<"->"<< mVexs[v[i]].data;
    }

    outfile << endl;
}

int main(){
    ListUDG* pG;
    ofstream o;
    pG = new ListUDG();

    pG->print();   // 打印图
    pG->DFS();     // 深度优先遍历
    pG->getAll();
    while(1){}
    return 0;
}