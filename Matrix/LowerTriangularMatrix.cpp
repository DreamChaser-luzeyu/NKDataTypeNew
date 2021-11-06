#ifndef _LOWERTRIANGULARMATRIX_CPP
#define _LOWERTRIANGULARMATRIX_CPP
#include "LowerTriangularMatrix.h"

template <class T>
LowerTriangularMatrix<T>::LowerTriangularMatrix(int size) {
    elements = new T[(1+size)*size/2];
    this->size = size;
    for(int i=0; i<(1+size)*size/2; i++) {
        elements[i] = zeroElement;
    }
}

template <class T>
LowerTriangularMatrix<T>::LowerTriangularMatrix(const LowerTriangularMatrix<T>& m) {
    elements = new T[(1+m.size)*(m.size)/2];
    this->size = m.size;
    for(int i=0; i<(1+size)*size/2; i++){
        this->elements[i] = m.elements[i];
    }
}

template <class T>
LowerTriangularMatrix<T>::~LowerTriangularMatrix() {
    delete[] elements;
}


template <class T>
void LowerTriangularMatrix<T>::set(int row, int col, const T& newValue) {
    if(row<0 || col<0 || row>=size || col>=size) {
        throw "IndexOutOfRange";
    }
    if(row < col) {
        if(newValue != zeroElement){
            throw "illegalParameterValue";
        }
    }
    elements[row*(row+1)/2 + col] = newValue;
}

template <class T>
T LowerTriangularMatrix<T>::get(int row, int col) const {
    if(row<0 || col<0 || row>=size || col>=size) {
        throw "IndexOutOfRange";
    }
    if(row < col) {
        return zeroElement;
    }
    return elements[row*(row+1)/2 + col];
}

template <class T>
void LowerTriangularMatrix<T>::output(ostream& out) const {
    out << endl;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            out << this->get(i, j) << " ";
        }
        out << endl;
    }
}

#endif