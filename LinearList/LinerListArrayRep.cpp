#ifndef _LINERLISTARRAYREP_CPP
#define _LINERLISTARRAYREP_CPP

#include <iostream>
#include "LinerListArrayRep.h"

using std::cin;
using std::cout;

template<class T>
ArrayList<T>::ArrayList(int initialCapacity){
    if(initialCapacity < 0){
        throw "Constructor : initial capacity must be > 0";
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template<class T>
ArrayList<T>::ArrayList(const ArrayList<T>& theList){
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    this->element = new T[arrayLength];
    for(int i=0; i<arrayLength; i++) {
        this->element[i] = theList.element[i];
    }
}

template <class T>
ArrayList<T>::checkIndex(int theIndex) const {
    if(theIndex<0 || theIndex>=listSize) {
        throw "checkIndex : index out of range";
    }
}

template <class T>
T& ArrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return element[theIndex];
}

template <class T>
int ArrayList<T>::indexOf(const T& theElement) const {
    for(int i=0; i<listSize; i++) {
        if(theElement == element[i]) {return i;}
    }
    return -1;
}

template <class T>
void ArrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    copy(element+theIndex+1, element+listSize, element+theIndex);
    element[--listSize].~T();
}

template <class T>
void ArrayList<T>::insert(int theIndex, const T& theElement) {
    if(theIndex<0 || theIndex>listSize) {
        throw "insert : illegal index";
    }
    if(listSize == arrayLength) {
        
    }
}


#endif