#include <iostream>
#include <map>
using namespace std;
/*
    http://blog.sina.com.cn/s/blog_5ff8e88e01013lot.html
*/
class node
{
  public:
    int number;
    node *next;
    node(int a, node *b)
    {
        number = a;
        next = b;
    }
};

class stacks
{
  public:
    node *top;
    stacks(node *a = NULL)
    {
        top = NULL;
    }
    void push(int a)
    {
        if (top == NULL)
            top = new node(a, NULL);
        else
            top = new node(a, top);
    }
    void pop()
    {
        node *b = top;
        top = top->next;
        delete b;
    }
}; //保存已加入路径结点的栈

int cur_node;           //当前结点，即为栈顶的结点
int next_node = 8;      //当前结点的下一个邻接点，即刚从栈顶弹出的结点，初始化为8
map<int, int> map_next; //每个结点的下一个邻接点，即刚从栈顶弹出的结点
int start = 3;
int end = 6; //起点为3，终点为6
stacks aray[8] = {stacks(NULL), stacks(NULL), stacks(NULL), stacks(NULL), stacks(NULL), stacks(NULL), stacks(NULL), stacks(NULL)};
stacks stack(NULL);
int states[8]; //保存结点状态的数组
int main()
{
    //初始化map_next
    for (int i = 0; i <= 7; i++)
    {
        map_next[i] = -1;
    }
    aray[0].push(2);
    aray[0].push(1);
    aray[1].push(4);
    aray[1].push(3);
    aray[1].push(0);
    aray[2].push(6);
    aray[2].push(5);
    aray[2].push(0);
    aray[3].push(7);
    aray[3].push(1);
    aray[4].push(7);
    aray[4].push(1);
    aray[5].push(6);
    aray[5].push(2);
    aray[6].push(5);
    aray[6].push(2);
    aray[7].push(4);
    aray[7].push(3);
    node *neighbour(int a);   // ,int b
    stack.push(start);        //将起点入栈
    states[start] = 1;        //将起点标记为入栈状态
    while (NULL != stack.top) //栈不为空
    {
        if (stack.top->number == end)
        {
            cout << "end";
            node *abc = stack.top;
            while (abc->number != start)
            {
                cout << abc->number << ",";
                abc = abc->next;
            }
            cout << "start" << endl; //输出已找到的路径
            stack.pop();             //将栈顶结点弹出
            states[end] = 0;         //清除终点的状态
            map_next[end] = -1;
        }
        else
        {
            cur_node = stack.top->number;
            if (neighbour(cur_node) != NULL) //邻居不为空
            {
                node *d = neighbour(cur_node);
                map_next[cur_node] = d->number;
                cur_node = d->number;
                stack.push(cur_node);
                states[cur_node] = 1;
            }
            else
            {
                stack.pop();
                states[cur_node] = 0;
                map_next[cur_node] = -1;
            }
        }
    }

    while (1)
    {
    }
    return 0;
}

node *neighbour(int a) //,int b
{
    node *abc = aray[a].top;
    while ((NULL != abc)) //结点abc不空
    {
        if (states[abc->number] == 1) //已经在栈stack里了
        {
            abc = abc->next;
        }
        else //不在栈stack里
        {
            if (-1 == map_next[a]) //就要abc作为返回值
            {
                while (NULL != abc && states[abc->number] == 1)
                {
                    abc = abc->next;
                }
                return abc;
            }
            else if (abc->number == map_next[a])
            {
                abc = abc->next;
                while (NULL != abc && states[abc->number] == 1)
                {
                    abc = abc->next;
                }
                return abc; //将abc的下一个结点返回
            }
            else
            {
                abc = abc->next;
            }
        }
    }
    return NULL;
}