#include<stdio.h>
#include<string>
#include<iostream>
#include<vector>
using namespace std;

vector<string> input = {"id","*","id","+","id","#"};
string lookahead = input.at(0);
int index = 0;

/*
	ȡ��һ������
*/
void nextToken()
{
	lookahead = input.at(++index);
}

void match(string c)
{
	if (lookahead == c) {
		nextToken();  // ��ǰ����ƥ�䣬��ȡ��һ������
	}
	else {
		if (c == ")") {
			cout << "error����ջ�������ս�� ) ���û���������һ��������" << endl;
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
	cout << "���봮��";
	for (int j = 0; j < input.size(); j++) {
		cout << input.at(j);
	}
	cout << endl<<"�ݹ��Ԥ��������̣�"<<endl;
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
		cout << "E'->��" << endl;
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
			cout << "errror:��ջ���������ս��F���û���������һ��id" << endl;
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
		cout << "T'->��" << endl;
	}
	else {
		if (lookahead == "id") {
			nextToken();
			cout << "error:���봮�����Ǻ�id���û���������һ��id" << endl;
			T1();
		}
		else if (lookahead == "(") {
			nextToken();
			cout << "error:�û����������˲�ƥ�������( ,�����üǺ�" << endl;
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
			cout << "error:��ջ���������ս��F���û���������һ��id" << endl;
		}
	}
}