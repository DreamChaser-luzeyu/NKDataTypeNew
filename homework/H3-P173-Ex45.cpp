#include "../Matrix/SparseMatrix.cpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::istream;
using std::ostream;

template <class T>
SparseMatrix<T> buildMatrix(istream& in, ostream& out, int row, int col, T zeroElement) {
    SparseMatrix<T> aMatrix(row, col, zeroElement);
    
    out << "Building matrix " << row << "rows, " << col << "cols..."
        << endl;
    while(true) {
        out  << "选择操作：" << endl
             << "1.取出         get [row] [col]" << endl
             << "2.写入         set [row] [col] [data]" << endl
             << "3.输出         output" << endl
             << "4.输出         outputS" << endl
             << "5.转置         transpose" << endl
             << "6.退出         exit" << endl;
        string method; in >> method;
        if(method == "get") {
            int row, col;
            in >> row >> col;
            out << endl 
                 <<"Get: " << aMatrix.get(row, col)
                 << endl;
        } else if(method == "set") {
            int row, col;
            in >> row >> col;
            T data; in >> data;
            try{
                aMatrix.set(row, col, data);
            } catch(char const* str) {out << str;}
        } else if(method == "output") {
            aMatrix.output(out);
        } else if(method == "outputS") {
            aMatrix.output_struct(out);
        } else if(method == "transpose") {
            aMatrix.transpose();
        } else if(method == "exit") {
            break;
        } else {
            out << "Invalid method." << endl;
        }
    }
    return aMatrix;
}

int mult(int row, int col, const SparseMatrix<int>& matrix1, const SparseMatrix<int>& matrix2) {
    int sum = 0;
    if(matrix1.getCol() != matrix2.getRow()) {
        throw "Cannot multiply : wrong size";
    }
    int size = matrix1.getCol();
    for(int i=0; i<size; i++) {
        sum += (matrix1.get(row, i)) * (matrix2.get(i, col));
    }
    return sum;
}

SparseMatrix<int> operator*(const SparseMatrix<int>& matrix1, const SparseMatrix<int>& matrix2) {
    if(matrix1.getCol() != matrix2.getRow()) {
        throw "Cannot multiply : wrong size";
    }
    int row, col;
    row = matrix1.getRow();
    col = matrix2.getCol();
    SparseMatrix<int> matrix3(row, col);
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            matrix3.set(i, j, mult(i, j, matrix1, matrix2));
        }
    }
    return matrix3;
}


/*
测试数据：
set 0 0 1
set 0 1 2
set 0 2 3
set 0 3 4
set 0 0 3
set 4 1 233
set 3 2 666
set 2 3 24
set 2 3 48
*/

int main() {
    SparseMatrix<int> aMatrix_1 = buildMatrix<int>(cin, cout, 2, 3, 0);
    SparseMatrix<int> aMatrix_2 = buildMatrix<int>(cin, cout, 3, 2, 0);
    (aMatrix_1 * aMatrix_2).output(cout);
    system("pause");
    return 0;
}