#include "../Matrix/LinkedMatrix.cpp"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
    LinkedMatrix<string> aMatrix(5,6);
    aMatrix.setZero("zero");
    while(true) {
        cout << "选择操作：" << endl
             << "1.取出         get [row] [col]" << endl
             << "2.写入         set [row] [col] [data]" << endl
             << "3.输出         output" << endl
             << "4.输出         outputS" << endl
             << "5.退出         exit" << endl;
        string method; cin >> method;
        if(method == "get") {
            int row, col;
            cin >> row >> col;
            cout << endl 
                 <<"Get: " << aMatrix.get(row, col)
                 << endl;
        } else if(method == "set") {
            int row, col;
            cin >> row >> col;
            string data; cin >> data;
            try{
                aMatrix.set(row, col, data);
            } catch(char const* str) {cout << str;}
        } else if(method == "output") {
            aMatrix.output(cout);
        } else if(method == "outputS") {
            aMatrix.output_struct(cout);
        } else if(method == "exit") {
            break;
        } else {
            cout << "Invalid method." << endl;
        }
    }
}