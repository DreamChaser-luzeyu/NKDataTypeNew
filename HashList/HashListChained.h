// no .cpp any more
#ifndef _HASHLISTCHAINED_H
#define _HASHLISTCHAINED_H
#include <vector>
#include <iostream>
#include <limits.h>
#include "hash.h"
#include <unordered_map>

using std::vector;
//using std::hash;
using std::ostream;
using std::cout;
using std::endl;

template <class V>
class Pair {
private:
    int key = INT_MAX; V value;
    
public:
    Pair* nextPair = nullptr; 
    Pair(const int& theKey, const V& theValue) {
        key = theKey;
        value = theValue;
    }
    Pair(){} // Constructing tail pointer
    Pair(Pair* nextPair){this->nextPair = nextPair;}
    int getKey() const {return key;}
    V getValue() const {return value;}
    void setValue(const V& theValue) {this->value = theValue;}
    friend ostream& operator<<(ostream& out, Pair<V> p) {
        out << "[key: " << p.key << " val:" << p.value << "]";
        return out;
    }
};


template <class V>
class HashListChained {
private:
    vector<Pair<V>* > elems;
    Pair<V>* lastNode;
    int sizeNow = 0;
    int divisor;
    int usedAmount = 0;
    int search(const int& theKey) const;
    int searchElem(const int& theKey) const;
    Pair<V>* tailNode;
public:
    HashListChained(int divisor, int initSize);
    bool isEmpty() const {return sizeNow == 0;}
    void insert(Pair<V>* thePair);
    Pair<V>* find(const int& theKey) const;
    void output(ostream& out) const;
    void erase(const int& theKey);
};


template <class V>
HashListChained<V>::HashListChained(int divisor, int initSize) {
    elems.resize(initSize);
    tailNode = new Pair<V>();
    typename vector<Pair<V>* >::iterator i;
    for(i=elems.begin(); i!=elems.end(); i++) {
        *i = tailNode;                          // theKey = INT_MAX
                                                // insert tail node
    }
    sizeNow = initSize;
    this->divisor = divisor;
}

// 查找可插入的下标
template <class V>
int HashListChained<V>::search(const int& theKey) const {     // 返回可以插入的下标
                                                              // 在这里与searchElem()相同
    int beginIndex = (unsigned int) hash<int>{}(theKey) % divisor;
    return beginIndex;
}

// 查找元素下标
template <class V>
int HashListChained<V>::searchElem(const int& theKey) const {     // 找到theKey对应的下标
                                                                  // 与search()相同
    int beginIndex = (unsigned int) hash<int>{}(theKey) % divisor;
    return beginIndex;
}

template <class V>
Pair<V>* HashListChained<V>::find(const int& theKey) const {
    int b = searchElem(theKey);
    Pair<V>* ptr = elems.at(b);                                                    
    while(ptr->getKey() < theKey) {
        ptr = ptr->nextPair;
    }
    if(ptr->getKey() == theKey) {return ptr;}       // Found the Pair
    return nullptr;                                 // Not found
}

template <class V>
void HashListChained<V>::insert(Pair<V>* thePair) {
    if(thePair == nullptr) {
        throw "Cannot insert nullptr!";
    }
    // if(thePair->getKey() == INT_MAX) {throw "Unpermitted key";}
    int b = searchElem(thePair->getKey());                  // Found the index
    Pair<V>* ptr = elems.at(b); 
    // check the first ptr
    if(ptr->getKey() > thePair->getKey()) {                 // insert before the first ptr
        elems[b] = thePair;                                 // insert the pair
        thePair->nextPair = ptr;                            // 
        return;
    }
    if(ptr->getKey() == thePair->getKey()) {                // change the value of the first ptr
        ptr->setValue(thePair->getValue());
        return;
    }
    // loop and find
    while(ptr->nextPair->getKey() <= thePair->getKey()) {   // first ptr is skipped
        ptr = ptr->nextPair;                                // 跳出循环时ptr->nextPair->getKey()已经大于thePair->getKey()
    }                                                       // ptr是要插入位置的指针
    if(ptr->getKey() < thePair->getKey()) {                 // Key不同->在后面插入Pair
        thePair->nextPair = ptr->nextPair;
        ptr->nextPair = thePair;
    } else if(ptr->getKey() == thePair->getKey()) {         // Key相同->修改Pair
        ptr->setValue(thePair->getValue());
    } else {                                                // Key不同->在前面插入Pair
                                                            // 只有需要插在首节点之前时才可能插入在ptr之前
        cout << "Code error";                               // 个人觉得在这写并不优雅，不应该把特殊情况并入一般情况
                                                            // 本特殊情况已在前面考虑，所以并未在此实现
    }
}

template <class V>
void HashListChained<V>::output(ostream& out) const {    
    for(int i=0; i<sizeNow; i++) {
        Pair<V>* ptr = elems.at(i);
        out << "index: " << i << "\t";
        while(ptr != nullptr) {
            out << *ptr << "-->";
            ptr = ptr->nextPair;
        }
        out << endl;
    }
}

template <class V>
void HashListChained<V>::erase(const int& theKey) {
    if(theKey == INT_MAX) {throw "Cannot erase tail node";}
    int b = searchElem(theKey);
    Pair<V>* ptr = elems.at(b);
    if(ptr == tailNode) {throw "Pair does not exist";}
    if(ptr->getKey() == theKey) {                       // 单独搜索首节点
        elems[b] = ptr->nextPair;
        delete ptr;
        return;
    }
    while(true) {                                   // First node is skipped
        if(ptr->nextPair->getKey() >= theKey) {break;}  // reach the position
        ptr = ptr->nextPair;
    }
    if(ptr->nextPair->getKey() != theKey) {throw "Pair does not exist";}
    else {                                          // delete the pair
        Pair<V>* deletePtr = ptr->nextPair;
        ptr->nextPair = ptr->nextPair->nextPair;
        delete deletePtr;
    }
}

#endif