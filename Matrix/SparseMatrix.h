#ifndef _SPAREMATRIX_H
#define _SPAREMATRIX_H

#include <vector>
#include <ostream>
using std::ostream;
using std::vector;

template <class T>
class ArrayElement {
public:
    ArrayElement(int row, int col, const T& val) {
        this->row = row;
        this->col = col;
        this->val = val;
    }
    ArrayElement(){}
    int row, col;
    T val;
};

template <class T>
ostream& operator<<(ostream& out, const ArrayElement<T>& e) {
    return (out << "<row: " << e.row
                << " col: " << e.col
                << " val: " << e.val << ">");
}

template <class T>
ostream& operator<<(ostream& out, ArrayElement<T>& element) {
    return (out << "<row:" << element.row
                << "col: " << element.col
                << "val: " << element.val);
}

template <class T>
class SparseMatrix {
public:
    SparseMatrix(int row, int col, const T& zero);
    SparseMatrix(int row, int col);
    void setZero(const T& zero) {this->zeroElement = zero;}
    // void get(int row, int col, T& theElement) const;
    void set(int row, int col, const T& theElement);
    T get(int row, int col) const;
    void output(ostream& out) const;
    void output_struct(ostream& out) const;
    void transpose();
    int getRow() const {return row;}
    int getCol() const {return col;}
private:
    int row, col;
    T zeroElement;
    vector<ArrayElement<T> > elements;
    void checkIndex(int row, int col) const;
};

#endif