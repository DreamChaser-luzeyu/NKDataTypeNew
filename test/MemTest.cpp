#include <iostream>

using namespace std;

class B { 
public:
    ~B() {
        cout << "B destructor" << endl;
    }

};

class A {
public:
    B b;
    void func() {
        B* pb = new B();
        b = *pb;
    }

};

int main() {
    A* p = new A();
    p->func();
    //delete p;
    system("pause");
    return 0;
}