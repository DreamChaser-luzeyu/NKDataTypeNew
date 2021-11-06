#include <iostream>
#include <fstream>
#include <string>
using namespace std;

unsigned long long cache[91] = {0};


unsigned long long fibonacci(unsigned long long n){
    if(cache[n] != 0){return cache[n];}
    if(n == 1){return 1;}
    if(n == 0){return 0;}
    unsigned long long r = fibonacci(n-2) + fibonacci(n-1);
    cache[n] = r;
    return r;
}

int main(){
    // ifstream fin("./input.txt");
    // if(!fin.is_open()){
    //     cout << "Could not open file" << endl;
    //     return -1;
    // }

    string str; cin >> str;
    int n;
    try{
        n = stoi(str);
    } catch(exception e){
        cout << "Not a num" << endl;
        return -1;
    }
    if(n > 90 || n < 0){
        cout << "Num invalid";
        return -1;
    }
    //fin.close();
    //cout << n << endl;
    cout << fibonacci(n) << endl;
    return 0;
}

