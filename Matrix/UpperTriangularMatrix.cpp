#ifndef _UPPERTRIANGULARMATRIX_CPP
#define _UPPERTRIANGULARMATRIX_CPP
#include "UpperTriangularMatrix.h"

template <class T>
UpperTriangularMatrix<T>::UpperTriangularMatrix(int size) {
    elements = new T[(1+size)*size/2];
    this->size = size;
    for(int i=0; i<(1+size)*size/2; i++) {
        elements[i] = zeroElement;
    }
}

template <class T>
UpperTriangularMatrix<T>::UpperTriangularMatrix(const UpperTriangularMatrix<T>& m) {
    elements = new T[(1+m.size)*(m.size)/2];
    this->size = m.size;
    for(int i=0; i<(1+size)*size/2; i++){
        this->elements[i] = m.elements[i];
    }
}

template <class T>
UpperTriangularMatrix<T>::~UpperTriangularMatrix() {
    delete[] elements;
}


template <class T>
void UpperTriangularMatrix<T>::set(int row, int col, const T& newValue) {
    if(row<0 || col<0 || row>=size || col>=size) {
        throw "IndexOutOfRange";
    }
    if(row > col) {
        if(newValue != zeroElement){
            throw "illegalParameterValue";
        }
    }
    elements[col*(col+1)/2 + row] = newValue;
}

template <class T>
T UpperTriangularMatrix<T>::get(int row, int col) const {
    if(row<0 || col<0 || row>=size || col>=size) {
        throw "IndexOutOfRange";
    }
    if(row > col) {
        return zeroElement;
    }
    return elements[col*(col+1)/2 + row];
}

template <class T>
void UpperTriangularMatrix<T>::output(ostream& out) const {
    out << endl;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            out << this->get(i, j) << " ";
        }
        out << endl;
    }
}

#endif