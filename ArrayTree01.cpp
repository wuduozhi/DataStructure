#include <iostream>
using namespace std;

/*
基于数组实现二叉树
浪费空间
*/

int main()
{
    int data[] = {0, 1, 11, 12, 7, 8, 19, 2, 10, 4, 5, 9, 30};
    int btree[100] = {-1};
    for (int i = 0; i < 100; i++)
        btree[i] = -1;

    cout << "The origin array: " << endl;
    for (int i = 1; i < 13; i++)
        cout << "[" << data[i] << "] ";
    cout << endl;
    int level;
    for (int i = 1; i < 13; i++)
    {
        level = 1;
        while (btree[level] != -1)
        {
            if (data[i] > btree[level])
            {
                level = level * 2 + 1;
            }
            else
            {
                level = 2 * level;
            }
        }

        btree[level] = data[i];
    }

    cout << "The Tree: " << endl;
    for (int i = 1; i < 100; i++)
    {
        if (btree[i] != -1)
        {
            cout << "index:[" << i << "][" << btree[i] << "]    ";
        }
    }

    cout << endl;

    while (1)
    {
    }
    return 0;
}