#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;


// Auto generated
// 中缀表达式转后缀表达式
string infixToSuffix(string infix) {
	string suffix = "";
	vector<char> stack;
	for (int i = 0; i < infix.size(); i++) {
		if ('a' <= infix[i] && infix[i] <= 'z') {
			suffix += infix[i];
		}
		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
			while (!stack.empty() && (stack.back() == '*' || stack.back() == '/')) {
				suffix += stack.back();
				stack.pop_back();
			}
			stack.push_back(infix[i]);
		}
		else if (infix[i] == '(') {
			stack.push_back(infix[i]);
		}
		else if (infix[i] == ')') {
			while (!stack.empty() && stack.back() != '(') {
				suffix += stack.back();
				stack.pop_back();
			}
			stack.pop_back();
		}
	}
	while (!stack.empty()) {
		suffix += stack.back();
		stack.pop_back();
	}
	return suffix;
}


int main()
{
    string str="a+b*(c/d+e)";
    cout << infixToSuffix(str) << endl;
    system("pause");
    return 0;
}