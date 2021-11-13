#include <iostream>
#include <vector>
using namespace std;


class B {
    public: B(){}
    public: B(const B& b) {
        cout << "copy constructor B called" << endl;
    }
    public: ~B() {
        cout << "B destructed";
    }
};

// class A {
//     B data;
//     // public: void func() {
//     //     cout << data.val() << endl;
//     // }
//     public: A() {
//         cout << "A Constructor called" << endl; 
//     }
//     // public: A() {
//     //     cout << "Default constructor called" << endl;
//     // }
// };




int main() {
    vector<B> vec;
    B b;
    vec.push_back(b);
    vector<B> vec2;
    vec2 = vec;
    system("pause");
    return 0;
}