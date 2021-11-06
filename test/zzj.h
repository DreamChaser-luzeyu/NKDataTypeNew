//标头.h
#pragma once
#include <iostream>
using namespace std;
template <typename T>
class HashTable
{
private:
    int size;
    T *items;
    bool *neverused;
public:
    HashTable(int n)
    {
        size = n;
        items = new T[size];
        neverused = new bool[size];
        for (int k = 0; k < size; k++)
        {
            items[k] = 0;
            neverused[k] = 1;
        }
    }
    HashTable(const HashTable<T> &target)
    {
        size = target.size;
        items = new T[size];
        neverused = new bool[size];
        for (int k = 0; k < size; k++)
        {
            items[k] = target.items[k];
            neverused[k] = target.neverused[k];
        }
    }
    ~HashTable()
    {
        delete[] items;
        delete[] neverused;
    }
    void operator=(HashTable<T> target)
    {
        delete[] items;
        delete[] neverused;
        size = target.size;
        items = new T[size];
        neverused = new bool[size];
        for (int k = 0; k < size; k++)
        {
            items[k] = target.items[k];
            neverused[k] = target.neverused[k];
        }
    }
    int hash(const T &t) { return t % 10; }
    int search(const T &t)
    {
        int i = hash(t) % size;
        int j = 0;
        while (1)
        {
            if (neverused[(i + j) % size] == 1 || items[(i + j) % size] == t)
                return (i + j) % size;
            j++;
            if (((i + j) % size) == i)
                break;
        }
        return ((i + j) % size);
    }
    bool find(const T &t)
    {
        int n = search(t);
        if (neverused[n] == 1 || items[n] != t)
            return false;
        return true;
    }
    bool needReset()
    {
        int n = 0;
        for (int k = 0; k < size; k++)
        {
            if (neverused[k] == 0)
                n++;
        }
        if (double(n) / double(size) >= 0.6)
            return true;
        return false;
    }
    void insert(T t)
    {
        int n = search(t);
        if (neverused[n] == 1)
        {
            neverused[n] = 0;
            items[n] = t;
        }
    }
    void erase(T t)
    {
        int n = search(t);
        if (neverused[n] == 1 || items[n] != t)
            cout << "该元素不存在" << endl;
        else
            items[n] = 0;
        if (needReset())
            reset();
    }
    void output()
    {
        cout << "输出哈希表" << endl;
        for (int k = 0; k < size; k++)
            cout << items[k] << " ";
        cout << endl;
        for (int k = 0; k < size; k++)
            cout << neverused[k] << " ";
        cout << endl;
    }
    void reset()
    {
        HashTable<T> temp(size);
        for (int k = 0; k < size; k++)
        {
            if (items[k] != 0)
            {
                temp.insert(items[k]);
            }
        }
        *this = temp;
    }
};