#ifndef _LINERLISTCHAINREP_H
#define _LINERLISTCHAINREP_H
#include "LinerList.h"
#include <ostream>

template<class T>
class ChainNode{
public:
    T element;
    ChainNode<T>* next = nullptr;
    ChainNode(){}
    ChainNode(const T& element) {this->element = element;}
    ChainNode(const T& element, ChainNode<T>* next){
        this->element = element;
        this->next = next;
    }
};

template<class T>
class ChainList : LinerList<T>{
public:
    ChainList(int initialCapacity = 0);
    ChainList(const ChainList<T>&);
    ~ChainList();

    bool isEmpty() const { return listSize == 0;}
    int size() const { return listSize; }
    T& get(int theIndex) const;
    ChainNode<T>* getNode(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void eraseNextNode(ChainNode<T>* theNode);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream& out) const;

protected:
    void checkIndexStrict(int theIndex) const;
    void checkIndex(int theIndex) const;
    ChainNode<T>* firstNode;
    int listSize;
};

#endif