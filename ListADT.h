#ifndef LIST
#define LIST
#include <iostream>
using namespace std;
template <typename E>
class List
{
  protected:
    int listSize;
    int maxSize;
    int curr;
    E *listArray;

  public:
    List(int size = 50)
    {
        maxSize = size;
        listSize = curr = 0;
        listArray = new E[maxSize];
    }

    virtual ~List()
    {
        delete[] listArray;
        listArray = NULL;
    }

    void moveToStart()
    {
        curr = 0;
    }

    void moveToEnd()
    {
        curr = listSize - 1;
    }

    void prev()
    {
        if (curr == 0)
            return;
        curr--;
    }

    void next()
    {
        if (curr == listSize - 1)
            return;
        curr++;
    }

    int length() const
    {
        return listSize;
    }

    int currPos() const
    {
        return curr;
    }

    void moveToPos(int pos)
    {
        if (pos >= listSize)
            return;
        curr = pos;
    }

    const E &getValue() const
    {
        return listArray[curr];
    }

    int indexOf(const E &it)
    {
        for (curr = 0; curr < listSize; curr++)
        {
            if (it == getValue())
            {
                return curr;
            }
        }
        return -1;
    }

    void display()
    {
        for (int i = 1; i <= listSize; i++)
        {
            cout << listArray[i - 1] << "  ";
            if (i % 10 == 0)
                cout << endl;
        }
        cout << endl;
    }

    void append(const E &item)
    {
        if (listSize >= maxSize)
        {
            listArray[listSize - 1] = item;
            return;
        } //如果线性表已经满了的话，就把检索的值放在最后一个位置

        listArray[listSize++] = item;
    }

    virtual void renovate() = 0;
};

//使用频率自组织启发式规则的类
template <typename E>
class Frelist : public List<E>
{
    int *fre;

  public:
    Frelist(int size = 50) : List(size)
    {
        fre = new int[maxSize];
    }
    ~Frelist()
    {
        delete[] fre;
    }

    void append(const E &item)
    {
        List::append(item);
        fre[listSize - 1] = 1;
    }

    int indexOf(const E &it)
    {
        if (List::indexOf(it) >= 0)
        {
            fre[curr]++;
            return curr;
        }
        return -1;
    }

    void renovate()
    {
        int i;
        for (i = curr; i >= 1; i--)
        {
            if (fre[curr] < fre[i - 1])
                break;
        }
        if (i == curr)
            return;
        E temp = listArray[curr];
        int ftemp = fre[curr];
        for (int j = curr; j >= i + 1; j--)
        {
            listArray[j] = listArray[j - 1];
            fre[j] = fre[j - 1];
        }
        listArray[i] = temp;
        fre[i] = ftemp;
    } //更新线性表
};

//移至前端自组织线性表启发式规则的类
template <typename E>
class MTFlist : public List<E>
{
  public:
    void append(const E &item)
    {
        if (listSize < maxSize)
            listSize++;
        for (int i = listSize - 1; i >= 1; i--)
        {
            listArray[i] = listArray[i - 1];
        }
        listArray[0] = item;
    } //把新加入检索的值插入表头

    void renovate()
    {
        E temp = listArray[curr];
        for (int i = curr; i >= 1; i--)
        {
            listArray[i] = listArray[i - 1];
        }
        listArray[0] = temp;
    } //更新线性表
};

//转置自组织线性表启发式规则的类
template <typename E>
class Tlist : public List<E>
{
  public:
    void renovate()
    {
        if (curr == 0)
            return;
        E temp = listArray[curr];
        listArray[curr] = listArray[curr - 1];
        listArray[curr - 1] = temp;
    }
};
#endif