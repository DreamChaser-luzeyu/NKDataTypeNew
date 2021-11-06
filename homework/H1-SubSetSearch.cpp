#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

vector<string> showSubSets(int n){
    if(n == 0){
        vector<string> r;
        r.push_back("");
        return r;
    }
    
    vector<string> r = showSubSets(n-1);                // 递归调用,r存储上次递归的返回值
    vector<string> a;                                   // 本次返回
    
    char letter = 'a' + n - 1;                          // 本次递归的结束字母
    for(string s : r){                                  // 取出上次递归的值
        string str = " "; str.push_back(letter);        // str = " x"
        a.push_back(s + str);                           // 给上次的每个子集加上这次的字母
    }
    
    a.insert(a.begin(), r.begin(), r.end());
    return a;
}

int main(){
    fstream fin("input.txt");
    if(!fin.is_open()){cout << "Cannot open file." << endl; return -1;}

    string str; fin >> str;
    int n; 
    try{
        n = stoi(str);// fstream fin("input.txt");
    // if(!fin.is_open()){cout << "Cannot open file." << endl; return -1;}
    } catch(exception e) {
        cout << "Not a number" << endl;
        return -1;
    }
    
    vector<string> result = showSubSets(n);
    
    for(string s : result){
        cout << s << endl;
    }
    fin.close();
    return 0;
}