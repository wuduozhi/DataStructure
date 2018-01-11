#include<iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/*
 * 希尔排序      要点：先将待排序列分组排序，变成基本有序的数组，最后用插入排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void shell_sort(int a[], int n){
    int i,j,gap;
    //gap为步长，每次减为原来的一半
    for(gap = n/2;gap>0;gap/=2){
        // 共gap个组，对每一组都执行直接插入排序
        for(i = 0;i<gap;i++){
            for(j = i+gap;j<n;j+=gap){
                // 如果a[j] < a[j-gap]，则寻找a[j]位置，并将后面数据的位置都后移。
                if (a[j] < a[j - gap])
                {
                    int tmp = a[j];
                    int k = j - gap;
                    while (k >= 0 && a[k] > tmp)
                    {
                        a[k + gap] = a[k];
                        k -= gap;
                    }
                    a[k + gap] = tmp;
                }
            }
        }
        for(int m=0;m<n;m++)
            cout<<a[m]<<" ";
        cout<<endl;
    }
}

int main()
{
    int i;
    int a[] = {80,30,60,40,20,10,50,70};
    int ilen = (sizeof(a)) / (sizeof(a[0]));

    cout << "Before sort:";
    for (i=0; i<ilen; i++)
        cout << a[i] << " ";
    cout << endl;

    shell_sort(a, ilen);     
    cout << "After  sort:";
    for (i=0; i<ilen; i++)
        cout << a[i] << " ";
    cout << endl;

    while(1){}
    return 0;
}