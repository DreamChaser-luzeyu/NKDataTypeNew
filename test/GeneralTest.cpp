#include <iostream>
#include <vector>
using namespace std;


class B {
    public: ~B() {
        cout << "B destructed";
    }
};

class A {
    B data;
    // public: void func() {
    //     cout << data.val() << endl;
    // }
    public: A() {
        cout << "A Constructor called" << endl; 
    }
    // public: A() {
    //     cout << "Default constructor called" << endl;
    // }
};




int main() {
    A* a = new A();
    delete a;

    system("pause");
    return 0;
}