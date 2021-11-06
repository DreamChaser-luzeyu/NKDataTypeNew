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
    // aMatrix.setZero(zeroElement); // setZero()函数可以随时执行
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



int main() {
    SparseMatrix<int> aMatrix = buildMatrix<int>(cin, cout, 5, 4, 0);
    
    return 0;
}