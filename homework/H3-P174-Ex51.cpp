#include "../Matrix/LinkedMatrix.cpp"
#include <iostream>
#include <string>
using std::ostream;
using std::istream;
using std::cin;
using std::cout;
using std::endl;
using std::string;

template <class T>
LinkedMatrix<T> buildMatrix(istream& in, ostream& out, int row, int col, T zeroElement) {
    LinkedMatrix<T> aMatrix(row, col);
    aMatrix.setZero(zeroElement);// setZero()函数可以随时执行
    out << "Building matrix " << row << "rows, " << col << "cols..."
        << endl;
    while(true) {
        out  << "选择操作：" << endl
             << "1.取出         get [row] [col]" << endl
             << "2.写入         set [row] [col] [data]" << endl
             << "3.输出         output" << endl
             << "4.输出         outputS" << endl
             << "5.退出         exit" << endl;
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
        } else if(method == "exit") {
            break;
        } else {
            out << "Invalid method." << endl;
        }
    }
    return aMatrix;
}

LinkedMatrix<int> operator+(const LinkedMatrix<int>& matrix1, const LinkedMatrix<int>& matrix2) {
    if(!((matrix1.getRow() == matrix2.getRow()) 
     && (matrix1.getCol() == matrix2.getCol()))) {
         throw "Cannot add : different size";
    }
    int row, col;
    row = matrix1.getRow();
    col = matrix1.getCol();
    LinkedMatrix<int> matrix3(row, col);
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            matrix3.set(i, j, (matrix1.get(i, j) + matrix2.get(i,j)));
        }
    }
    return matrix3;
}

LinkedMatrix<int> operator-(const LinkedMatrix<int>& matrix1, const LinkedMatrix<int>& matrix2) {
    if(!((matrix1.getRow() == matrix2.getRow()) 
     && (matrix1.getCol() == matrix2.getCol()))) {
         throw "Cannot minus : different size";
    }
    int row, col;
    row = matrix1.getRow();
    col = matrix1.getCol();
    LinkedMatrix<int> matrix3(row, col);
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            matrix3.set(i, j, (matrix1.get(i, j) - matrix2.get(i,j)));
        }
    }
    return matrix3;
}

int mult(int row, int col, const LinkedMatrix<int>& matrix1, const LinkedMatrix<int>& matrix2) {
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

LinkedMatrix<int> operator*(const LinkedMatrix<int>& matrix1, const LinkedMatrix<int>& matrix2) {
    if(matrix1.getCol() != matrix2.getRow()) {
        throw "Cannot multiply : wrong size";
    }
    int row, col;
    row = matrix1.getRow();
    col = matrix2.getCol();
    LinkedMatrix<int> matrix3(row, col);
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            matrix3.set(i, j, mult(i, j, matrix1, matrix2));
        }
    }
    return matrix3;
}


void runDemo(istream& in, ostream& out) {
    while(true) {
        out << "请输入要进行的演示：" << endl
            << "1.矩阵相加\t" << "plus" << endl
            << "2.矩阵相减\t" << "minus" << endl
            << "3.矩阵相乘\t" << "mult" << endl
            << "4.退出\t\t" << "exit" << endl;
        string method; in >> method;
        if(method == "plus") {
            LinkedMatrix<int> matrix5Row6Col_1 = buildMatrix<int>(cin, cout, 5, 6, 0);
            LinkedMatrix<int> matrix5Row6Col_2 = buildMatrix<int>(cin, cout, 5, 6, 0);
            out << endl
                << "Result:"
                << endl;
            (matrix5Row6Col_1 + matrix5Row6Col_2).output(out);
        } else if(method == "minus") {
            LinkedMatrix<int> matrix5Row6Col_1 = buildMatrix<int>(cin, cout, 5, 6, 0);
            LinkedMatrix<int> matrix5Row6Col_2 = buildMatrix<int>(cin, cout, 5, 6, 0);
            out << endl
                << "Result:"
                << endl;
            (matrix5Row6Col_1 - matrix5Row6Col_2).output(out);
        } else if(method == "mult") {
            LinkedMatrix<int> matrix5Row6Col = buildMatrix<int>(cin, cout, 5, 6, 0);
            LinkedMatrix<int> matrix6Row5Col = buildMatrix<int>(cin, cout, 6, 4, 0);
            out << endl
                << "Result:"
                << endl;
            try {
                (matrix5Row6Col * matrix6Row5Col).output(out);
            } catch(char const* str) {
                out << str << endl;
            }
        } else if(method == "exit") {
            break;
        } else {
            out << "Wrong input." << endl;
        }
    }

}

/*
demo data:
matrix5Row6Col_1:
set 0 0 1
set 0 1 2
set 0 2 3
set 0 3 4
set 0 0 3
set 3 1 233
set 3 2 666
set 2 3 24
set 2 4 48

matrix6Row4Col
set 0 0 1
set 0 1 2
set 0 2 3
set 0 3 4
set 0 0 3
set 3 1 233
set 3 2 666
set 2 3 24

Online calc:
http://www.yunsuan.info/cgi-bin/matrix_multiplication.py
3,2,3,4,0,0
0,0,0,0,0,0
0,0,0,24,48,0
0,233,666,0,0,0
0,0,0,0,0,0

3,2,3,4
0,0,0,0
0,0,0,24
0,233,666,0
0,0,0,0
0,0,0,0

*/

int main() {
    runDemo(cin, cout);
    system("pause");
}