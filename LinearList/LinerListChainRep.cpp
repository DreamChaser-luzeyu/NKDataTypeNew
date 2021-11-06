#ifndef _LINERLISTCHAINREP_CPP
#define _LINERLISTCHAINREP_CPP
#include "LinerListChainRep.h"


template<class T>
ChainList<T>::ChainList(int initialCapacity){
    // std::cout << "default constructor called" << std::endl;
    if(initialCapacity < 0){
        throw "Must be > 0";
    }
    firstNode = nullptr;
    listSize = 0;
}

template<class T>
ChainList<T>::ChainList(const ChainList<T>& theList){           // 实现拷贝构造函数
    listSize = theList.listSize;                                // 拷贝链表容量
    if(listSize == 0){                                          // 空链表
        firstNode = nullptr;                                    //
        return;                                                 //
    }
    ChainNode<T>* sourceNode = theList.firstNode;               // 声明源指针
    firstNode = new ChainNode<T>(sourceNode -> element);        // 拷贝首节点
    sourceNode = sourceNode->next;                              // 源指针后移
    ChainNode<T>* targetNode = firstNode;                       // 声明目标指针
    while(sourceNode != nullptr){                               // 循环拷贝节点
        targetNode->next = new ChainNode<T>(sourceNode->element);
        targetNode = targetNode->next;                          // sourceNode指针比targetNode指针靠后一个节点
        sourceNode = sourceNode->next;                          // 源指针后移
    }
}

template<class T>
ChainList<T>::~ChainList(){
    while(firstNode != nullptr){
        ChainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
T& ChainList<T>::get(int theIndex) const {
    checkIndexStrict(theIndex);
    ChainNode<T>* currentNode = firstNode;
    for(int i=0; i<theIndex; i++){
        currentNode = currentNode->next;
    }
    return currentNode->element;
}

template<class T>
ChainNode<T>* ChainList<T>::getNode(int theIndex) const {
    checkIndexStrict(theIndex);
    ChainNode<T>* currentNode = firstNode;
    for(int i=0; i<theIndex; i++){
        currentNode = currentNode->next;
    }
    return currentNode;
}

template<class T>
int ChainList<T>::indexOf(const T& theElement) const {
    ChainNode<T>* currentNode = firstNode;
    int index = 0;
    while(currentNode != nullptr &&
          currentNode->element != theElement){
        currentNode = currentNode->next;
        index ++;      
    }
    if(currentNode == nullptr){
        return -1;
    }
    return index;
}

template<class T>
void ChainList<T>::erase(int theIndex){
    checkIndexStrict(theIndex);
    ChainNode<T>* deleteNode;
    if(theIndex == 0){                                      // 单独处理删除首元素的情况
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }else{
        ChainNode<T>* p = firstNode;
        for(int i=0; i<theIndex-1; i++){
            p = p->next;
        }                                                   // 结束后，p指向deleteNode的前驱节点
        deleteNode = p->next;
        p->next = p->next->next;
    }
    delete deleteNode;
    listSize --;
}

template<class T>
void ChainList<T>::eraseNextNode(ChainNode<T>* theNode){
    if(theNode->next == nullptr) {
        throw "eraseNextNode : Not a loop";
    }
    if(theNode == nullptr) {
        throw "eraseNextNode : nullptr";
    }
    delete theNode->next;
    theNode->next = theNode->next->next;
    listSize --;
}

template<class T>
void ChainList<T>::insert(int theIndex, const T& theElement){
    checkIndex(theIndex);
    if(theIndex == 0){                                      // 单独处理头节点插入
        firstNode = new ChainNode<T>(theElement, firstNode);
    } else {
        ChainNode<T>* p = firstNode;
        for(int i=0; i<theIndex-1; i++){
            p = p->next;
        }                                                   // 寻找前驱节点
        p->next = new ChainNode<T>(theElement, p->next);
    }
    listSize ++;
}

template<class T>
void ChainList<T>::checkIndexStrict(int theIndex) const {
    if(theIndex < 0 || theIndex >= listSize){
        throw "Index out of range";
    }
}

template<class T>
void ChainList<T>::checkIndex(int theIndex) const {
    if(theIndex < 0 || theIndex > listSize){
        throw "Index out of range";
    }
}


template<class T>
void ChainList<T>::output(std::ostream& out) const {
    out << "{";
    ChainNode<T>* p = this->firstNode;
    while(p!=nullptr){
        out << p->element << ", ";
        p = p->next;
    }
    out << "}";
}

#endif