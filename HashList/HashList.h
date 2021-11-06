// no .cpp any more
#ifndef _HASHLIST_H
#define _HASHLIST_H
#include <vector>
#include <iostream>
#include <iomanip>
#include "hash.h"
#include <unordered_map>

using std::vector;
//using std::hash;
using std::ostream;
using std::cout;
using std::endl;
using std::ios;

template <class K, class V>
class Pair {
private:
    K key; V value;
public:
    Pair(const K& theKey, const V& theValue) {
        key = theKey;
        value = theValue;
    }
    K getKey() const {return key;}
    V getValue() const {return value;}
    void setValue(const V& theValue) {this->value = theValue;}
    friend ostream& operator<<(ostream& out, Pair<K, V> p) {
        out << "<key: " << p.key << "\tval:" << p.value << ">";
        return out;
    }

};


template <class K, class V>
class HashList {
private:
    vector<Pair<K, V>* > elems;
    bool* neverUsed;                                    // 标记对应下标有没有被使用过，默认true
    int sizeNow = 0;
    int divisor;
    int usedAmount = 0;
    int search(const K& theKey) const;
    int searchElem(const K& theKey) const;
    bool needReset() const;
    void resetList();
public:
    HashList(int divisor, int initSize);
    bool isEmpty() const {return sizeNow == 0;}
    void insert(Pair<K, V>* thePair);
    Pair<K, V>* find(const K& theKey) const;
    void output(ostream& out) const;
    // void erase_move(const K& theKey);
    void erase_mark(const K& theKey);
};


template <class K, class V>
HashList<K, V>::HashList(int divisor, int initSize) {
    elems.resize(initSize);
    typename vector<Pair<K, V>* >::iterator i;
    for(i=elems.begin(); i!=elems.end(); i++) {
        *i = nullptr;
    }
    neverUsed = new bool[initSize];
    for(int i=0; i<initSize; i++) {neverUsed[i] = true;}
    sizeNow = initSize;
    this->divisor = divisor;
}

// 查找可插入的下标
template <class K, class V>
int HashList<K, V>::search(const K& theKey) const {     // 返回可以插入的下标
                                                        // 但是可能没法成功定位key相同的Pair
                                                        // 导致出现Key相同的Pair
                                                        // 所以此函数已经弃用
                                                        // 若没有可以插入的下标，就返回hash值对应的下标
    int beginIndex = (unsigned int) hash<K>{}(theKey) % divisor;
    int tmpIndex = beginIndex;
    while(true) {
        Pair<K, V>* ptr = elems.at(tmpIndex);
        if(ptr == nullptr && !neverUsed[tmpIndex]) {break;}                   // found a deleted elem, use the position
        if(ptr == nullptr &&  neverUsed[tmpIndex]) {break;}                   // elem does not exist, return the index now
        if(ptr->getKey() == theKey) {return tmpIndex;}                        // Found it
        tmpIndex ++;
        if(tmpIndex == beginIndex) {break;}             // loop back, not found
        if(tmpIndex == sizeNow) {tmpIndex = 0;}         // loop search
    }
    return tmpIndex;
}

// 查找元素下标
template <class K, class V>
int HashList<K, V>::searchElem(const K& theKey) const {     // 找到theKey对应的下标
                                                            // 若没有，就返回最近的未用过的空位
                                                            // 若没有可以插入的下标，就返回hash值对应的下标
    int beginIndex = (unsigned int) hash<K>{}(theKey) % divisor;
    int tmpIndex = beginIndex;
    while(true) {
        Pair<K, V>* ptr = elems.at(tmpIndex);
        if(ptr == nullptr && !neverUsed[tmpIndex]) {tmpIndex++; continue;}    // skip deleted elem and continue
        if(ptr == nullptr &&  neverUsed[tmpIndex]) {break;}                   // elem does not exist, return the index now
        if(ptr->getKey() == theKey) {return tmpIndex;}                        // Found it
        tmpIndex ++;
        if(tmpIndex == beginIndex) {break;}             // loop back, not found
        if(tmpIndex == sizeNow) {tmpIndex = 0;}         // loop search
    }
    return tmpIndex;
}


template <class K, class V>
bool HashList<K, V>::needReset() const {
    double usedPercentage = (double)usedAmount / (double)sizeNow;
    return (usedPercentage >= 0.6d); 
}

template <class K, class V>
void HashList<K, V>::resetList() {
    cout << "Reseting list..." << endl;
    vector<Pair<K, V>* > tmp(elems);
    // typename vector<Pair<K, V>* >::iterator i;
    for(int i=0; i<sizeNow; i++) {
        elems[i] = nullptr;
        Pair<K, V>* ptr = tmp.at(i);
        neverUsed[i] = true;
        insert(ptr);
    }
}

template <class K, class V>
Pair<K, V>* HashList<K, V>::find(const K& theKey) const {
    int b = searchElem(theKey);
    Pair<K, V>* ptr = elems.at(b);
    if(ptr == nullptr) {return nullptr;}    // 没有找到这个Key 
                                                        // 不会继续向后查找，所以删除Pair时必须移动后面连续的Pair
                                                        // 练习27要求通过标注的方式，在不移动后面元素、不改变elems的同时实现删除功能
    if(ptr->getKey() != theKey) {                       // 没有找到这个Key
        return nullptr;
    }
    return elems.at(b);
}

template <class K, class V>
void HashList<K, V>::insert(Pair<K, V>* thePair) {
    if(thePair == nullptr) {return;}
    int b = searchElem(thePair->getKey());
    if(elems.at(b) == nullptr) {                            // b是可使用的下标
        elems[b] = thePair;                                 // 插入Pair
        neverUsed[b] = false;
        usedAmount ++;
    } else {
        if(elems.at(b)->getKey() == thePair->getKey()) {    // 找到Key重复的Pair
            // delete elems[b];
            elems[b] = thePair;                             // 修改对应的Value（覆盖原Pair）
        } else {
            throw "Full hash list!";                        // 已经被不同Key，但具有相同Hash值的Pair占据，表已满
        }
    }
}

template <class K, class V>
void HashList<K, V>::output(ostream& out) const {
    for(int i=0; i<sizeNow; i++) {
        Pair<K, V>* ptr = elems.at(i);
        out << "index: " << i << "\t";
        
        // out.setf(std::ios::right);
        if(ptr == nullptr) {
            out << "nullptr\t\t\t\t";
        } else {
            out << "<key: " << ptr->getKey() << "  value: " << ptr->getValue() << ">";
            out << "\t\t";
        }
        if(neverUsed[i] == true) {
            out << "" << "Never used" << endl;
        } else {
            out << "" << "Used" << endl;
        }
    }
}

template <class K, class V>
void HashList<K, V>::erase_mark(const K& theKey) {
    int b = searchElem(theKey);
    Pair<K, V>* ptr = elems.at(b);
    if(ptr == nullptr) {
        throw "No this element";
    }                                                   // 没有找到这个Key
    if(ptr->getKey() != theKey) {                       // 表满了，且没有找到这个Key
        throw "No this element and list is full";
    }
    delete ptr;
    elems[b] = nullptr;                                 // 删除Pair

    if(needReset()) {
        resetList();
    }
}

#endif