#ifndef _DOUBLYLINKEDLIST_CPP
#define _DOUBLYLINKEDLIST_CPP
#include "DoublyLinkedList.h"

template <class T>
DoublyChainList<T>::DoublyChainList(int initialCapacity) {
    if (initialCapacity < 0) {
        throw "Must be > 0";
    }
    firstNode = nullptr;
    lastNode = nullptr;
    listSize = 0;
}

template <class T>
DoublyChainList<T>::DoublyChainList(const DoublyChainList<T> &theList)
{
    listSize = theList.listSize;
    if (listSize == 0) {
        firstNode = nullptr;
        return;
    }
    DoublyChainNode<T> *sourceNode = theList.firstNode;
    this->firstNode = new DoublyChainNode<T>(sourceNode->element); // 拷贝首节点
    sourceNode = sourceNode->next;
    DoublyChainNode<T> *targetNode = this->firstNode;
    while (sourceNode != nullptr) {
        targetNode->next = new DoublyChainNode<T>(sourceNode->element);
        targetNode->next->previous = targetNode; // 双向链接
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
}

template <class T>
DoublyChainList<T>::~DoublyChainList() {
    for(int i=0; i<this->listSize; i++) {
        DoublyChainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
T &DoublyChainList<T>::get(int theIndex) const {
    checkIndexStrict(theIndex);
    DoublyChainNode<T> *currentNode = getNode(theIndex);
    // if (theIndex < (this->listSize) / 2) {
    //     currentNode = firstNode;
    //     for (int i = 0; i < theIndex; i++) {
    //         currentNode = currentNode->next;
    //     }
    // }
    // else {
    //     currentNode = lastNode;
    //     for (int i = 0; i < listSize - theIndex - 1; i++) {
    //         currentNode = currentNode->previous;
    //     }
    // }
    return currentNode->element;
}

template <class T>
int DoublyChainList<T>::indexOf(const T &theElement) const {
    DoublyChainNode<T>* currentNode = firstNode;
    int index = 0;
    for (int i=0; i<listSize && currentNode->element != theElement; i++) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == nullptr) {
        return -1;
    }
    return index;
}

template <class T>
int DoublyChainList<T>::indexOfCirculatedWithHead(const T& theElement) const {
    DoublyChainNode<T>* currentNode = this->firstNode->next;
    int index = 0;
    this->firstNode->element = theElement;
    for (; currentNode->element != theElement; ) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == this->firstNode) {
        return -1;
    }
    return index;
}

template <class T>
void DoublyChainList<T>::erase(int theIndex)
{
    checkIndexStrict(theIndex);
    DoublyChainNode<T> *deleteNode;
    if (theIndex == 0) { // 单独处理删除首元素的情况
        deleteNode = firstNode;
        firstNode = firstNode->next;
        if(firstNode != nullptr){
            firstNode->previous = nullptr;
        } else {
            lastNode = nullptr;
        }
    } else if(theIndex == listSize-1) {
        deleteNode = lastNode;
        lastNode->previous->next = nullptr;
        lastNode = lastNode->previous;
    } else {
        DoublyChainNode<T>* currentNode = getNode(theIndex);
        // if (theIndex < (this->listSize) / 2) {
        //     currentNode = firstNode;
        //     for (int i = 0; i < theIndex; i++) {
        //         currentNode = currentNode->next;
        //     }
        // } else {
        //     currentNode = lastNode;
        //     for (int i = 0; i < listSize - theIndex - 1; i++) {
        //         currentNode = currentNode->previous;
        //     }
        // }
        currentNode->previous->next = currentNode->next;
        currentNode->next->previous = currentNode->previous;
        deleteNode = currentNode;
    }
    delete deleteNode;
    listSize--;
}

template<class T>
void DoublyChainList<T>::insert(int theIndex, const T& theElement) {
    checkIndex(theIndex);
    DoublyChainNode<T>* newNode = new DoublyChainNode<T>(theElement);
    insertNode(theIndex, newNode);
    // if(theIndex == 0) {               // 单独处理插入起始位置
    //     DoublyChainNode<T>* newNode = new DoublyChainNode<T>(theElement, firstNode, nullptr);
    //     if(!isEmpty()) {
    //         firstNode->previous = newNode;
    //         firstNode = newNode;
    //     } else {
    //         firstNode = newNode;
    //         lastNode = firstNode;
    //     }
    // } else if(theIndex == listSize) {  // 单独处理插入结束位置
    //     DoublyChainNode<T>* newNode = new DoublyChainNode<T>(theElement, nullptr, lastNode);
    //     lastNode->next = newNode;
    //     lastNode = newNode;
    // } else {
    //     DoublyChainNode<T>* currentNode = getNode(theIndex);  // 被插入下标之前下标对应节点
    //     DoublyChainNode<T>* newNode = new DoublyChainNode<T>(theElement, currentNode, currentNode->previous);
    //     currentNode->previous = newNode;
    //     newNode->previous->next = newNode;
    // }
    // listSize ++;
}

template<class T>
void DoublyChainList<T>::output(std::ostream& out) const {
    out << "{";
    DoublyChainNode<T>* p = this->firstNode;
    for(int i=0; i<listSize; i++){
        out << p->element << ", ";
        p = p->next;
    }
    out << "}";
}

template<class T>
void DoublyChainList<T>::outputRev(std::ostream& out) const {
    out << "{";
    DoublyChainNode<T>* p = this->lastNode;
    for(int i=0; i<listSize; i++){
        out << p->element << ", ";
        p = p->previous;
    }
    out << "}";
}

template<class T>
void DoublyChainList<T>::circulateWithHead(){
    this->insert(0, "HeadNode");
    lastNode->next = firstNode;
    firstNode->previous = lastNode;
}

template<class T>
void DoublyChainList<T>::deCirculateWithHead(){
    this->erase(0);
    if(!isEmpty()){
        this->lastNode->next = nullptr;
    }
    // lastNode->next = firstNode;
    // firstNode->previous = lastNode;
}

template <class T>
void DoublyChainList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex > listSize)
    {
        throw "Index out of range";
    }
}

template <class T>
void DoublyChainList<T>::checkIndexStrict(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize)
    {
        throw "Index out of range";
    }
}

template <class T>
DoublyChainNode<T>* DoublyChainList<T>::getNode(int theIndex) const {
    checkIndexStrict(theIndex);
    DoublyChainNode<T>* currentNode;
    if (theIndex < (this->listSize) / 2) {
        currentNode = firstNode;
        for (int i = 0; i < theIndex; i++) {
            currentNode = currentNode->next;
        }
    } else {
        currentNode = lastNode;
        for (int i = 0; i < listSize - theIndex - 1; i++) {
            currentNode = currentNode->previous;
        }
    }
    return currentNode;
}

template<class T>
void DoublyChainList<T>::insertNode(int theIndex, DoublyChainNode<T>* theNode) {
    checkIndex(theIndex);
    DoublyChainNode<T>* newNode = theNode;
    if(theIndex == 0) {               // 单独处理插入起始位置
        // DoublyChainNode<T>* newNode = new DoublyChainNode<T>(theElement, firstNode, nullptr);
        if(!isEmpty()) {
            firstNode->previous = newNode;
            newNode->next = firstNode;
            firstNode = newNode;
        } else {
            firstNode = newNode;
            lastNode = firstNode;
        }
    } else if(theIndex == listSize) {  // 单独处理插入结束位置
        // DoublyChainNode<T>* newNode = new DoublyChainNode<T>(theElement, nullptr, lastNode);
        lastNode->next = newNode;
        newNode->previous = lastNode;
        lastNode = newNode;
        lastNode->next = nullptr;
    } else {
        DoublyChainNode<T>* currentNode = getNode(theIndex);  // 被插入下标之前下标对应节点
        // DoublyChainNode<T>* newNode = new DoublyChainNode<T>(theElement, currentNode, currentNode->previous);
        currentNode->previous = newNode;
        newNode->next = currentNode;
        newNode->previous->next = newNode;
    }
    listSize ++;
}

#endif