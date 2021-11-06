#ifndef _LINKEDMATRIX_CPP
#define _LINKEDMATRIX_CPP

#include "LinkedMatrix.h"

template <class T>
LinkedMatrix<T>::LinkedMatrix(int row, int col) {
    this->row = row; this->col = col;
    this->matrix = new ChainList<MatrixElement<T> > [row];
    // for(int i=0; i<row; i++) {
    //     matrix[i] = new ChainList<MatrixElement<T> >(0);
    // }
}

template <class T>
void LinkedMatrix<T>::set(int row, int col, const T& theElement) {
    if(row<0 || row>=this->row || col<0 || col>=this->col) {
        throw "Set : Index out of range.";
    }
    ChainList<MatrixElement<T> >* theLine = &matrix[row];
    if(theLine->isEmpty()) {
        theLine->insert(0, MatrixElement<T>(col, theElement));
    } else {
        int i;
        for(i=0; i<theLine->size(); i++) {
            if(theLine->get(i).col > col) {break;}      // 跳过列数靠前的元素
            if(theLine->get(i).col == col) {
                theLine->erase(i);                      // 已有元素，先删除
                break;
            }
        }
        theLine->insert(i, MatrixElement<T>(col, theElement));             // 插入元素
    }
}

template <class T>
T LinkedMatrix<T>::get(int row, int col) const {
    if(row<0 || row>=this->row || col<0 || col>=this->col) {
        throw "Get : Index out of range.";
    }
    ChainList<MatrixElement<T> >* theLine = &matrix[row];
    for(int i=0; i<theLine->size(); i++) {
        MatrixElement<T> tmp = theLine->get(i);
        if(tmp.col == col) {
            return tmp.theElement;
        }
        if(tmp.col > col) {break;}
    }
    return zeroElement;
}

// 减少拷贝开销
template <class T>
void LinkedMatrix<T>::get(int row, int col, T& theElement) const {
    if(row<0 || row>=this->row || col<0 || col>=this->col) {
        throw "Index out of range.";
    }
    ChainList<MatrixElement<T> >* theLine = matrix[row];
    for(int i=0; i<theLine->size(); i++) {
        MatrixElement<T> tmp = theLine->get(i);
        if(tmp.col == col) {
            theElement = tmp.theElement;
        }
        if(tmp.col > col) {break;}
    }
    theElement = zeroElement;
}

template <class T>
void LinkedMatrix<T>::output(ostream& out) const {
    out << endl;
    for(int i=0; i<this->row; i++) {
        for(int j=0; j<this->col; j++) {
            out << this->get(i, j);
            out << "\t";
        }
        out << endl;
    }
}

template <class T>
void LinkedMatrix<T>::output_struct(ostream& out) const {
    out << endl;
    for(int i=0; i<this->row; i++) {
        ChainList<MatrixElement<T> >* theLine = &matrix[i];
        theLine->output(out);
        out << endl;
    }
}

#endif