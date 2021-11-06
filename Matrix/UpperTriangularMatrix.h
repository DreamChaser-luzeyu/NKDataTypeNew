#ifndef _UPPERTRIANGULARMATRIX_H
#define _UPPERTRIANGULARMATRIX_H
#include <iostream>
using std::ostream;
using std::endl;

template <class T>
class UpperTriangularMatrix {
public:
    UpperTriangularMatrix(int size);
    UpperTriangularMatrix(const UpperTriangularMatrix<T>& m);
    ~UpperTriangularMatrix();

    void set(int row, int col, const T& newValue);
    T get(int row, int col) const;
    void setZero(T zero) {
        this->zeroElement = zero;
        for(int i=0; i<(1+size)*size/2; i++) {
            elements[i] = zeroElement;
        }
    }
    void output(ostream&) const;

protected:
    int size;
    T* elements;    
    T zeroElement;
};
#endif