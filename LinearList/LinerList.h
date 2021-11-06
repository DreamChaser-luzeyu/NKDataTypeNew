#ifndef _LINERLIST_H
#define _LINERLIST_H
#include <ostream>

template<class T>
class LinerList{
public:
    virtual ~LinerList(){};
    virtual bool isEmpty() const = 0;                             // 把不改变数组成员的函数加上const可以提高可读性
    virtual int size() const = 0;
    virtual T& get(int theIndex) const = 0;
    virtual int indexOf(const T& theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T& theElement) = 0;
    virtual void output(std::ostream& out) const = 0;
};

#endif