#include<iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/*
 * 快速排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     l -- 数组的左边界(例如，从起始位置开始排序，则l=0)
 *     r -- 数组的右边界(例如，排序截至到数组末尾，则r=a.length-1)
 */

void quickSort(int *a ,int l,int r){ 
    if(l<r){
        int i,j,x;
        i=l;
        j=r;
        x = a[i];
        while(i<j){
            while(i<j && a[j]>x){
                j--; // 从右向左找第一个小于x的数
            }

            if(i<j){
                a[i] = a[j];
                i++;
            }

            while(i<j && a[i]<x){
                i++;   // 从左向右找第一个大于x的数
            }

            if(i<j){
                a[j] = a[i];
                j--;
            }
        }
        a[i] = x;
        quickSort(a,l,i-1);
        quickSort(a,i+1,r);
    }
}

/*
 * 直接插入排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void insertSort(int* a, int n)
{
    int i, j, k;

    for (i = 1; i < n; i++)
    {
        //为a[i]在前面的a[0...i-1]有序区间中找一个合适的位置
        for (j = i - 1; j >= 0; j--)
            if (a[j] < a[i])
                break;

        //如找到了一个合适的位置
        if (j != i - 1)
        {
            //将比a[i]大的数据向后移
            int temp = a[i];
            for (k = i - 1; k > j; k--)
                a[k + 1] = a[k];
            //将a[i]放到正确位置上
            a[k + 1] = temp;
        }
    }
}



int main()
{
    int i;
    int a[] = {80,30,60,40,20,10,50,70};
    int ilen = (sizeof(a)) / (sizeof(a[0]));

    cout << "before sort:";
    for (i=0; i<ilen; i++)
        cout << a[i] << " ";
    cout << endl;

    quickSort(a, 0, ilen-1);        // 归并排序(从上往下)
    //mergeSortDown2Up(a, ilen);            // 归并排序(从下往上)

    cout << "after  sort:";
    for (i=0; i<ilen; i++)
        cout << a[i] << " ";
    cout << endl;

    while(1){}
    return 0;
}


