#include <iostream>
#include <string>
#include "../Matrix/LowerTriangularMatrix.cpp"
#include "../Matrix/UpperTriangularMatrix.cpp"
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::string;

template <class T>
class LowerTriangularMatrixExtended : public LowerTriangularMatrix<T> {
public:
    UpperTriangularMatrix<T> transpose(); 
    // 显式调用父类构造函数
    LowerTriangularMatrixExtended(int size): LowerTriangularMatrix<T>(size) {}
};

template <class T>
UpperTriangularMatrix<T> LowerTriangularMatrixExtended<T>::transpose() {
    UpperTriangularMatrix<T> upperMatrix(this->size);
    for(int i=0; i<this->size; i++) {
        for(int j=0; j<=i; j++) {
            upperMatrix.set(j, i, this->get(i, j));
        }
    }
    return upperMatrix;
}

template <class T>
LowerTriangularMatrixExtended<T> buildLowerTriangularMatrixExtendedManually(istream& is, T zeroElement) {
    LowerTriangularMatrixExtended<T> aMatrix(5);
    aMatrix.setZero(zeroElement); // setZero会清空矩阵数据，一般在构造后立即执行，或清空时执行
    while(true) {
        cout << "选择操作：" << endl
             << "1.取出         get [row] [col]" << endl
             << "2.写入         set [row] [col] [data]" << endl
             << "3.输出         output" << endl
             << "4.退出         exit" << endl;
        string method; is >> method;
        if(method == "get") {
            int row, col;
            is >> row >> col;
            cout << endl 
                 <<"Get: " << aMatrix.get(row, col)
                 << endl;
        } else if(method == "set") {
            int row, col;
            is >> row >> col;
            int data; is >> data;
            aMatrix.set(row, col, data);
        } else if(method == "output") {
            aMatrix.output(cout);
        } else if(method == "exit") {
            break;
        } else {
            cout << "Invalid method." << endl;
        }
    }
    return aMatrix;
}


/*
Test data:
set 0 0 1
set 4 0 2
set 4 4 3
set 2 2 4
set 3 1 5
set 3 2 6
*/

int main() {
    buildLowerTriangularMatrixExtendedManually<int>(cin, 0).transpose().output(cout);
    system("pause");
    return 0;
}