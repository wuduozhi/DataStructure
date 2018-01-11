/**
 * C++: 邻接矩阵表示的"无向图(List Undirected Graph)"
 *
 */

#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

#define MAX 100
class MatrixUDG{
    private:
        char mVexs[MAX];
        int  mVexNum;
        int mEdgNum;
        int mMatrix[MAX][MAX];
    public:
        // 创建图(自己输入数据)
		MatrixUDG();
        // 创建图(用已提供的矩阵)
        MatrixUDG(char vexs[], int vlen, char edges[][2], int elen);
		~MatrixUDG();

        // 打印矩阵队列图
        void print();

	private:
        // 读取一个输入字符
        char readChar();
        // 返回ch在mMatrix矩阵中的位置
        int getPosition(char ch);
        //初始化矩阵
        void init(){
            for(int i=0;i<MAX;i++){
                for(int j=0;j<MAX;j++)
                    mMatrix[i][j] = 0;
            }
        }
};

MatrixUDG::MatrixUDG(){
    init();
    char c1,c2;
    int i,p1,p2;
    //输入顶点数、边树
    cout<<"Please input vertex number: ";
    cin>>mVexNum;
    cout<<"Please input edge number: ";
    cin>>mEdgNum;

    if ( mVexNum < 1 || mEdgNum < 1 || (mEdgNum > (mVexNum * (mVexNum-1)))){
        cout << "input error: invalid parameters!" << endl;
        return ;
    }

    // 初始化"顶点"
    for (i = 0; i < mVexNum; i++){
        cout << "vertex(" << i << "): ";
        mVexs[i] = readChar();
    }

    // 初始化"边"
    for (i = 0; i < mEdgNum; i++){
        // 读取边的起始顶点和结束顶点
        cout << "edge(" << i << "): ";
        c1 = readChar();
        c2 = readChar();

        p1 = getPosition(c1);
        p2 = getPosition(c2);
        if (p1==-1 || p2==-1)
        {
            cout << "input error: invalid edge!" << endl;
            return ;
        }

        mMatrix[p1][p2] = 1;
        mMatrix[p2][p1] = 1;
    }
}

/*
 * 创建图(用已提供的矩阵)
 *
 * 参数说明：
 *     vexs  -- 顶点数组
 *     vlen  -- 顶点数组的长度
 *     edges -- 边数组
 *     elen  -- 边数组的长度
 */
MatrixUDG::MatrixUDG(char vexs[], int vlen, char edges[][2], int elen){
    init();
    int i, p1, p2;
    
    // 初始化"顶点数"和"边数"
    mVexNum = vlen;
    mEdgNum = elen;
    // 初始化"顶点"
    for (i = 0; i < mVexNum; i++)
        mVexs[i] = vexs[i];

    // 初始化"边"
    for (i = 0; i < mEdgNum; i++){
        // 读取边的起始顶点和结束顶点
        p1 = getPosition(edges[i][0]);
        p2 = getPosition(edges[i][1]);

        mMatrix[p1][p2] = 1;
        mMatrix[p2][p1] = 1;
    }
}

/* 
 * 析构函数
 */
MatrixUDG::~MatrixUDG() {}

/*
 * 返回ch在mMatrix矩阵中的位置
 */
int MatrixUDG::getPosition(char ch){
    int i;
    for(i=0; i<mVexNum; i++)
        if(mVexs[i]==ch)
            return i;
    return -1;
}

/*
 * 读取一个输入字符
 */
char MatrixUDG::readChar(){
    char ch;

    do {
        cin >> ch;
    } while(!((ch>='a'&&ch<='z') || (ch>='A'&&ch<='Z')));

    return ch;
}

/*
 * 打印矩阵队列图
 */
void MatrixUDG::print(){
    int i,j;

    cout << "Martix Graph:" << endl<<" ";
    for (i = 0; i < mVexNum; i++)
        cout<<" "<<(char)mVexs[i];
    cout<<endl;

    for (i = 0; i < mVexNum; i++){
        cout<<(char)mVexs[i]<<" ";
        for (j = 0; j < mVexNum; j++){
            if(mMatrix[i][j]>=0){
                cout << mMatrix[i][j] << " ";
            }
        }
            
        cout << endl;
    }
}

int main(){
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'C'}, 
        {'A', 'D'}, 
        {'A', 'F'}, 
        {'B', 'C'}, 
        {'C', 'D'}, 
        {'E', 'G'}, 
        {'F', 'G'}};
    int vlen = sizeof(vexs)/sizeof(vexs[0]);
    int elen = sizeof(edges)/sizeof(edges[0]);
    MatrixUDG* pG;

    // 自定义"图"(输入矩阵队列)
    //pG = new MatrixUDG();
    // 采用已有的"图"
    pG = new MatrixUDG(vexs, vlen, edges, elen);

    pG->print();   // 打印图

    while(1){}
    return 0;
}