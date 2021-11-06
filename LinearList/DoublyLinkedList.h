#ifndef _DOUBLYLINKEDLIST_H
#define _DOUBLYLINKEDLIST_H
#include "LinerList.h"
#include <ostream>

template<class T>
class DoublyChainNode{
public:
    T element;
    DoublyChainNode<T>* next = nullptr;
    DoublyChainNode<T>* previous = nullptr;
    DoublyChainNode(){}
    DoublyChainNode(const T& element) {this->element = element;}
    // DoublyChainNode(const T& element, DoublyChainNode<T>* next){
    //     this->element = element;
    //     this->next = next;
    //     this->previous = nullptr;
    // }
    DoublyChainNode(const T& element, DoublyChainNode<T>* next, DoublyChainNode<T>* previous){
        this->element = element;
        this->next = next;
        this->previous = previous;
    }
};

template<class T>
class DoublyChainList : LinerList<T>{
public:
    DoublyChainList(int initialCapacity = 0);
    DoublyChainList(const DoublyChainList<T>&);
    ~DoublyChainList();

    bool isEmpty() const { return listSize == 0;}
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    int indexOfCirculatedWithHead(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream& out) const;
    void outputRev(std::ostream& out) const;
    void circulateWithHead(); // 使之成为有头节点的双向循环链表
    void deCirculateWithHead(); // 恢复为普通双向链表


protected:
    void checkIndex(int theIndex) const;
    void checkIndexStrict(int theIndex) const;
    
    DoublyChainNode<T>* firstNode;
    DoublyChainNode<T>* lastNode;
    int listSize;
    // int test;

public:
    DoublyChainNode<T>* getNode(int theIndex) const;
    void insertNode(int theIndex, DoublyChainNode<T>* theNode);
};

#endif