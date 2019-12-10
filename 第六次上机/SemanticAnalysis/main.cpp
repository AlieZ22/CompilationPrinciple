#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<sstream>
using namespace std;

class Symbol {
public:
	string symbol;   // 表示id,+,-,E,T等
	double val;

	Symbol() {}
	Symbol(string symbol,double val=0) {
		this->symbol = symbol;
		this->val = val;
	}
};

vector<string> symbols = { "id","+","-","*","/","(",")","$","E","T","F" };
// 使用十六进制表示，左边（0表示移进，1表示归约），右边表示状态。十进制负数表示错误处理的种类，99表示acc
// 扩充减法和除法
int LRTable[16][11] = {
	{0x05,-1,-1,-1,-1,0x04,-1,-1,1,2,3},
	{-1,0x06,0x07,-1,-1,-1,-1,99,0,0,0},
	{-1,0x13,0x13,0x08,0x09,-1,0x13,0x13,0,0,0},
	{-1,0x16,0x16,0x16,0x16,-1,0x16,0x16,0,0,0},
	{0x05,-1,-1,-1,-1,0x04,-1,-1,10,2,3},
	{-1,0x18,0x18,0x18,0x18,-1,0x18,0x18,0,0,0},
	{0x05,-1,-1,-1,-1,0x04,-1,-1,0,11,3},
	{0x05,-1,-1,-1,-1,0x04,-1,-1,0,12,3},
	{0x05,-1,-1,-1,-1,0x04,-1,-1,0,0,13},
	{0x05,-1,-1,-1,-1,0x04,-1,-1,0,0,14},
	{-1,0x06,0x07,-1,-1,-1,0x0F,-1,0,0,0},
	{-1,0x11,0x11,0x08,0x09,-1,0x11,0x11,0,0,0},
	{-1,0x12,0x12,0x08,0x09,-1,0x12,0x12,0,0,0},
	{-1,0x14,0x14,0x14,0x14,-1,0x14,0x14,0,0,0},
	{-1,0x15,0x15,0x15,0x15,-1,0x15,0x15,0,0,0},
	{-1,0x17,0x17,0x17,0x17,-1,0x17,0x17,0,0,0},
};

void string2num(string str, double& num);
void match(string current,Symbol& s);
int findColumn(string s);

int main() 
{
	//vector<string> inputStr = { "5","+","3","+","8","*","2","$" };  // 常规
	vector<string> inputStr = { "10","-","6","/","1e2","$" };    // 支持浮点数和科学记数法
	//vector<string> inputStr = {"3","+","+","2.09","$"};    // 错误输入
	int index = 0;
	Symbol current;   // 当前的输入符号
	stack<int> stack_s;    // 状态栈
	stack<Symbol> stack_x;   // 符号栈
	int s_top;    // 状态栈栈顶
	Symbol x_top;  // 符号栈
	int i, j;    // LR分析表的行列

	stack_s.push(0);    // 初始化符号栈
	while (true) {
		match(inputStr.at(index), current);
		s_top = stack_s.top();

		i = s_top;   // 确定当前状态是第几行
		j = findColumn(current.symbol);   // 确定当前状态是第几列
		int analysis = LRTable[i][j];

		if (analysis == 99) {   // 接受动作
			cout << "接受" << endl;
			cout << "最终结果：" << stack_x.top().val << endl;
			break;
		}
		else if (analysis > 0x00 && analysis <= 0x0f) {   // 移进动作
			cout << "移进" << endl;
			stack_x.push(current);
			stack_s.push(analysis);
			index++;
		}
		else if (analysis > 0x10 && analysis <= 0x1F) {   // 归约动作
			int no = analysis - 0x10;  // 按哪个产生式进行归约
			double val1 = 0.0, val2 = 0.0;
			int row = -1, column = -1, newState = -1;
			Symbol temp;
			switch (no) {
			case 1:   // 按E->E+T归约
			case 2:   // 按E->E-T归约
			case 4:   // 按T->T*F归约
			case 5:   // 按T->T/F归约
				val2 = stack_x.top().val;
				stack_s.pop(); stack_x.pop();
				stack_s.pop(); stack_x.pop();
				val1 = stack_x.top().val;
				stack_s.pop(); stack_x.pop();
				if (no == 1) {
					cout << "按E->E+T归约: E.val="<<val1<<"+"<<val2 << endl;
					temp = Symbol("E", val1 + val2);
				}
				else if (no == 2) {
					cout << "按E->E-T归约: E.val=" << val1 << "-" << val2 << endl;
					temp = Symbol("E", val1 - val2);
				}
				else if (no == 4) {
					cout << "按T->T*F归约: T.val=" << val1 << "*" << val2 << endl;
					temp = Symbol("T", val1 * val2);
				}
				else if (no == 5) {
					cout << "按T->T/F归约: T.val=" << val1 << "/" << val2 << endl;
					temp = Symbol("T", val1 / val2);
				}
				stack_x.push(temp);
				break;
			case 3:   // 按E->T归约
			case 6:   // 按T->F归约
			case 8:   // 按F->id归约
				val1 = stack_x.top().val;
				stack_s.pop(); stack_x.pop();
				if (no == 3) {
					cout << "按E->T归约: E.val="<<val1 << endl;
					temp = Symbol("E", val1);
				}
				else if (no == 6) {
					cout << "按T->F归约: T.val="<<val1 << endl;
					temp = Symbol("T", val1);
				}
				else if (no == 8) {
					cout << "按F->id归约: F.val="<<val1 << endl;
					temp = Symbol("F", val1);
				}
				stack_x.push(temp);
				break;
			case 7:   // 按F->(E)归约
				stack_s.pop(); stack_x.pop();
				val1 = stack_x.top().val;
				stack_s.pop(); stack_x.pop();
				stack_s.pop(); stack_x.pop();
				cout << "按F->(E)归约: F.val=" << val1 << endl;
				temp = Symbol("F", val1);
				stack_x.push(temp);
				break;
			default:
				break;
			}
			// 在goto表中寻找新的状态
			row = stack_s.top();
			column = findColumn(temp.symbol);
			newState = LRTable[row][column];
			stack_s.push(newState);
		}
		else if (analysis < 0) {    // 错误动作
			cout << "error: 输入有误，重新输入！" << endl;
			break;
		}
	}
	return 0;
}


// 将字符串转换成数字（支持小数）
void string2num(string str, double& num)
{
	stringstream ss;
	ss << str;
	ss >> num;
}

// 根据当前输入位置的内容返回一个封装的Symbol
void match(string current, Symbol& s)
{
	char first = current.at(0);
	//第一个字符若是数字，那么它一定是数字
	if (first >= 48 && first <= 57) {
		double num = 0.0;
		string2num(current, num);
		s.symbol = "id";
		s.val = num;
	}
	else {   // 其他情况就是+,-,*,/,(,),$
		s.symbol = current;
	}
}

// 根据当前的输入的符号找到列数
int findColumn(string s)
{
	for (int i = 0; i < symbols.size(); i++) {
		if (s == symbols.at(i)) {
			return i;
		}
	}
	return -1;
}