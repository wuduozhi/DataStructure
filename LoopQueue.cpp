#include<iostream>
#include <stdlib.h>
using namespace std;


/*
栈空： 队首标志=队尾标志时，表示栈空，即红绿两个标志在图中重叠时为栈空。
栈满 : 队尾+1 = 队首时，表示栈满。
*/

template <typename T>
class LoopQueue{
    private:
        int capacity;
        int begin;
        int end;
        T * queue;
    public:
        LoopQueue(int c=10);
        ~LoopQueue();
        bool isEmpty();        //队列的判空
        int size();            //队列的大小
        bool push(T t);        //入队列
        bool pop();            //出队列
        T front();            //队首元素          
};

template<typename T>
LoopQueue<T>::LoopQueue(int c){
    capacity = c;
    begin = 0;
    end = 0;
    queue = new T[capacity];
};

template<typename T>
LoopQueue<T>::~LoopQueue(){
    delete [] queue;
};

template<typename T>
bool LoopQueue<T>::isEmpty(){
    if(begin == end){
        return true;
    }else{
        return false;
    }
};

template<typename T>
int LoopQueue<T>::size(){
    int sum = (end - begin + capacity)%capacity;  //计算队列长度
    return sum;
};

template<typename T>
bool LoopQueue<T>::push(T t){
    if((end+1)%capacity == begin){
        return false;
    }
    queue[end] = t;
    end = (end+1)%capacity;

    return true;
};

template<typename T>
bool LoopQueue<T>::pop(){
    if(isEmpty()){
        return false;
    }else{
        T t = queue[begin];
        begin = (begin+1)%capacity;
        return true;
    }
};

template<typename T>
T LoopQueue<T>::front(){
    if(isEmpty()){
        cout<<"Queue is empty.\n";
        exit;
    }

    return queue[begin];
}

int main(){
    LoopQueue<string> queue(10);
    queue.push("one");
    queue.push("two");
    queue.push("three");
    queue.push("four");
    queue.push("five");
    cout << "Size" << queue.size() << endl;
    while (!queue.isEmpty())
    {
        cout << queue.front() << endl;
        queue.pop();
    }
    
    while(1){}
    return 0;
}