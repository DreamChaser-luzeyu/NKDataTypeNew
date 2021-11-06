
#ifndef _LINERLISTARRAYREP_H
#define _LINERLISTARRAYREP_H

#include <iostream>
using std::ostream;

#include "LinerList.h"

// template<class T>
// class LinerList{
// public:
//     virtual ~LinerList(){};
//     virtual bool empty() const = 0;                             // 把不改变数组成员的函数加上const可以提高可读性
//     virtual int size() const = 0;
//     virtual T& get(int theIndex) const = 0;
//     virtual int indexOf(const T& theElement) const = 0;
//     virtual void erase(int theIndex) = 0;
//     virtual void insert(int theIndex, const T& theElement) = 0;
//     virtual void output(ostream& out) const = 0;
// };

template<class T>
class ArrayList : public LinerList<T>{
public:
    ArrayList(int initialCapacity = 10);
    ArrayList(const ArrayList<T>&);
    ~ArrayList() {delete[] element;}

    bool isEmpty() const {return listSize == 0;}
    int size() const {return listSize;}
    T& get(int theIndex) const;             // 可以返回对成员变量的引用 
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;
    int capacity() const {return arrayLength;}

protected:
    void checkIndex(int theIndex) const;
    T* element;
    int arrayLength;                                            // 数组的长度
    int listSize;                                               // 线性表所存储的元素个数
};

#endif