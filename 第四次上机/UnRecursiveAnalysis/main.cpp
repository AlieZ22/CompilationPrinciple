#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;
//#define N 5
//#define M 6
vector<string> nonterminals = {"E","E'","T","T'","F"};
vector<string> terminals = {"id","+","*","(",")","$"};
/*string analysisTable[N][M] = {
	"E->TE'", "","","E->TE'","","",
	"","E'->+TE'","","","E'->~","E'->~",
	"T->FT'","","","T->FT'","","",
	"","T'->~","T'->*FT'","","T'->~","T'->~",
	"F->id","","","F->(E)","",""
};*/
vector<string> input = {"id","*","id","+","id","$"};
int index = 0;
string lookahead = input.at(index);
stack<string> analysisStack;


string table[13] = { "E,id=E->TE`","E,(=E->TE`","E`,+=E`->+TE`","E`,)=E`->$","E`,$=E`->$","T,id=T->FT`","T,(=T->FT`","T`,+=T`->$","T`,*=T`->*FT`","T`,)=T`->$","T`,$=T`->$","F,id=F->id","F,(=F->(E)" };
string match(string s)
{
	int i = 0, k=0;
	for (; i < 13; i++)
	{
		int j = 0;
		string s1;
		while (table[i][j] != '=')
		{
			s1.append(1, table[i][j]);
			j++;
		}
		if (s == s1)
		{
			k = j;
			break;
		}
	}
	cout << &table[i][k + 1] << endl;
	while (table[i][k] != '>')
	{
		k++;
	}
	string temp;
	temp.append(&table[i][k + 1]);
	return temp; //return TE'
}
int if_special(string s)
{
	int len = s.length();
	int i = 0;
	for (; i < len; i++)
	{
		if (s[i] == '`')
			break;
	}
	if (i == len)
		return 0;
	else
		return 1;
}
void nextToken()
{
	if (index < input.size() - 1)
	{
		index++;
		lookahead = input.at(index);
	}

}
int if_nonteminal(string s)
{
	int i = 0;
	for (; i < 5; i++)
	{
		if (s == nonterminals.at(i))
			break;
	}
	if (i == 5)
		return 0;
	else
		return 1;
}

int if_terminal(string s)
{
	int i = 0;
	for (; i < 6; i++)
	{
		if (s == terminals.at(i))
			break;
	}
	if (i == 6)
		return 0;
	else
		return 1;
}

void f()
{
	analysisStack.push("$");
	analysisStack.push("E");
	while (!analysisStack.empty())
	{
		string top;
		top = analysisStack.top();
		if (if_terminal(top))
		{
			// 第一种情况：top是终结符且正确匹配
			if (top == lookahead)
			{
				cout << "match " << top << endl;
				nextToken();
				analysisStack.pop();
			}
			// 第二种情况：top是终结符且错误匹配
			else {
				cout << "error matching" << endl;
				system("exit");
			}
		}
		// top是非终结符
		else
		{
			top.append(1, ',');
			top.append(&lookahead[0]);
			string t1 = match(top);//E,id(stack in and stack out)
			int Len = t1.length();
			analysisStack.pop();
			string t2;
			if (t1 == "$")//$ not push into stack
			{
			}
			else if (if_special(t1))//T`
			{
				for (int i = Len - 1; i >= 0; i--)
				{
					t2 = "";
					if (t1[i] != '`')
					{
						t2.append(1, t1[i]);
						analysisStack.push(t2);
					}
					else
					{
						i--;
						t2.append(1, t1[i]);
						t2.append(1, '`');//FT' need another discuss
						analysisStack.push(t2);
					}
				}
			}
			else
			{
				analysisStack.push(t1);
			}
		}
	}
}
int main()
{
	f();
	return 0;
}

