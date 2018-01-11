#include<iostream>
#include <stdlib.h>
using namespace std;

template<typename T>
class ArrayStack{
    private:
        int count;
        int capacity;
        T * array;
    public:
        ArrayStack(int s = 10){
            count = 0;
            capacity = s;
            array = new T[capacity];
        };
        ~ArrayStack(){
            if (array)
            {
                delete[]array;
               
            }
        };
        T top();
        void push(T e);
        T pop();
        bool isEmpty();
        int size();
};

 /*栈的判空操作*/
 template <typename T>
 bool ArrayStack<T>::isEmpty()
 {
      return count == 0; //栈元素为0时为栈空
 };

 /*返回栈的大小*/
 template <typename  T>
 int ArrayStack<T>::size()
 {
      return count;
 };

 /*插入元素*/
template <typename T>
void ArrayStack<T>::push(T t){
    if(count != capacity){
        array[count++] = t;
    }
}

/*谭栈*/
template <typename T>
T ArrayStack<T>::pop(){
    if(count != 0){
        return array[--count];
    }
}

/*获取栈顶元素*/
template <typename T>
T ArrayStack<T>::top(){
    if(count!=0){
        return array[count-1];
    }
}

int main(){
    ArrayStack<int> p = ArrayStack<int>();
    for(int i=0;i<10;i++){
        p.push(i);
    } 

    cout << "Size:"<<p.size() << endl;
    cout << "Is Empty:"<<p.isEmpty() << endl;
    cout << "Top :"<<p.top() << endl;
    cout << "Out in Order:" << endl;
    while (!p.isEmpty())
    {
        cout << p.pop() << endl;
    }
    
    while(1){}

    return 0;
}