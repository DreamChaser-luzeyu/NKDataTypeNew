#ifndef _LINKEDMATRIX_H
#define _LINKEDMATRIX_H

#include "../LinearList/LinerListChainRep.cpp"
#include <ostream>
using std::ostream;
using std::endl;

template <class T>
class MatrixElement {
public:
    int col; T theElement;
    MatrixElement(int col, T theElement) {
        this->col = col;
        this->theElement = theElement;
    }
    MatrixElement() {this->col = 0;}
    bool operator==(const MatrixElement& c) {
        return (c.col==this->col) 
            && (c.theElement==this->theElement);
    }
    bool operator!=(const MatrixElement& c) {
        return !this->operator==(c);
    }
    // friend ostream& operator<<(ostream& out, const MatrixElement<T>& m);
};

template <class T>
ostream& operator<<(ostream& out, const MatrixElement<T>& m) {
    return (out << "<" << m.col << " ," << m.theElement << ">");
}

template <class T>
class LinkedMatrix {
public:
    LinkedMatrix(int row, int col);
    int getRow() const {return row;}
    int getCol() const {return col;}
    void set(int row, int col, const T& theElement);
    T get(int row, int col) const;
    // 减少拷贝开销
    void get(int row, int col, T& theElement) const;
    void setZero(const T& zero) {this->zeroElement = zero;}
    void output(ostream& out) const;
    void output_struct(ostream& out) const;

private:
    int row; int col;
    T zeroElement;
    ChainList<MatrixElement<T> >* matrix;
};

#endif