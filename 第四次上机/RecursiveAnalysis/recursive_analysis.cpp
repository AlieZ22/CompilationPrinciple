#include<stdio.h>
#include<string>
#include<iostream>
#include<vector>
using namespace std;

vector<string> input = {"id","*","id","+","id","#"};
string lookahead = input.at(0);
int index = 0;

/*
	取下一个符号
*/
void nextToken()
{
	lookahead = input.at(++index);
}

void match(string c)
{
	if (lookahead == c) {
		nextToken();  // 当前符号匹配，则取下一个符号
	}
	else {
		if (c == ")") {
			cout << "error：弹栈，弹出终结符 ) ，用户少输入了一个右括号" << endl;
		}
	}
}

void E();
void E1();
void T();
void T1();
void F();

int main()
{
	cout << "输入串：";
	for (int j = 0; j < input.size(); j++) {
		cout << input.at(j);
	}
	cout << endl<<"递归地预测分析过程："<<endl;
	E();

	return 0;
}

void E()
{
	if (lookahead == "(" || lookahead == "id") {
		cout << "E->TE'" << endl;
		T();
		E1();
	}
	else {
		cout << "error breaks when try to match E" << endl;
	}

}

void E1()
{
	if (lookahead == "+") {
		cout << "E'->+TE'" << endl;
		match("+");
		T();
		E1();
	}
	else if(lookahead=="#"||lookahead==")"){
		cout << "E'->ε" << endl;
	}
	else {
		cout << "error breaks when try to match E'" << endl;
	}
}

void T() 
{
	if (lookahead == "(" || lookahead == "id") {
		cout << "T->FT'" << endl;
		F();
		T1();
	}
	else {
		if (lookahead == "+") {
			cout << "errror:弹栈，弹出非终结符F，用户少输入了一个id" << endl;
		}
	}
}

void T1()
{
	if (lookahead=="*"){
		cout << "T'->*FT'" << endl;
		match("*");
		F();
		T1();
	}
	else if (lookahead == "#" || lookahead == "+" || lookahead == ")") {
		cout << "T'->ε" << endl;
	}
	else {
		if (lookahead == "id") {
			nextToken();
			cout << "error:输入串跳过记号id，用户多输入了一个id" << endl;
			T1();
		}
		else if (lookahead == "(") {
			nextToken();
			cout << "error:用户错误输入了不匹配的括号( ,跳过该记号" << endl;
			T1();
		}
	}
}

void F()
{
	if (lookahead == "(") {
		match("(");
		cout << "F->(E)" << endl;
		E();
		match(")");
	}
	else if (lookahead == "id") {
		match("id");
		cout << "F->id" << endl;
	}
	else {
		if (lookahead == "*") {
			cout << "error:弹栈，弹出非终结符F，用户少输入了一个id" << endl;
		}
	}
}