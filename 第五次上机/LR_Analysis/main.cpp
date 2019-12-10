/*#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

vector<string> symbols = {"id","+","*","(",")","$","E","T","F"};
// 使用十六进制表示，左边（0表示移进，1表示归约），右边表示状态。十进制负数表示错误处理的种类，99表示acc
int LRTable[12][9] = {
	{0x05,-1,-1,0x04,-2,-1,1,2,3},
	{-3,0x06,-5,-3,-2,99,0,0,0},
	{-4,0x12,0x07,-4,0x12,0x12,0,0,0},
	{-7,0x14,0x14,-7,0x14,0x14,0,0,0},
	{0x05,-1,-1,0x04,-2,-1,8,2,3},
	{-7,0x16,0x16,-7,0x16,0x16,0,0,0},
	{0x05,-1,-1,0x04,-2,-1,0,9,3},
	{0x05,-1,-1,0x04,-2,-1,0,0,10},
	{-3,0x06,-5,-3,0x0B,-6,-0,0,0},
	{-4,0x11,0x07,-4,0x11,0x11,0,0,0},
	{-7,0x13,0x13,-7,0x13,0x13,0,0,0},
	{-7,0x15,0x15,-7,0x15,0x15,0,0,0}
};
string pop_end[6][2] = {
	{"E","E"},    // 1,E->E+T
	{"E","T"},    // 2,E->T
	{"T","T"},    // 3,T->T*F
	{"T","F"},    // 4,T->F
	{"F","("},    // 5,F->(E)
	{"F","id"}    // 6,F->id
};
void initPop_end();
int findColumn(string s);
void show_reduction(int num);

int main()
{
	vector<string> inputTokens = {"id","*","id","+","id","$"};   // 输入串
	int index = 0;   // 记录当前从左向右扫描的位置
	string currentToken;  // 当前扫描的记号
	stack<int> stack_s;  // 状态栈
	stack<string> stack_x;  // 符号栈
	int s_top;  // 状态栈栈顶
	string x_top;   // 符号栈栈顶
	int i, j; // 分别表示分析表的行列

	stack_s.push(0);  // 初始化状态栈
	while (true) {
		currentToken = inputTokens.at(index);
		s_top = stack_s.top();
		
		i = s_top;  // 确定当前状态是第几行
		j = findColumn(currentToken);  // 确定分析表的列
		int analysis = LRTable[i][j];

		if (analysis == 99) {   // 接受动作
			cout << "接受" << endl;
			break;
		}
		else if (analysis > 0x00 && analysis < 0x0F) {   // 移进动作
			cout << "移进" << endl;
			stack_x.push(currentToken);
			stack_s.push(analysis);
			index++;
		}
		else if (analysis > 0x10 && analysis < 0x1F) {   // 归约动作
			int no = analysis - 0x10;  // 按哪个产生式进行归约
			show_reduction(no);
			x_top = stack_x.top();
			while (x_top != pop_end[no-1][1]) {  // 确定何时该产生式弹栈完成
				stack_s.pop();
				stack_x.pop();
				x_top = stack_x.top();
			}
			stack_s.pop();
			stack_x.pop();

			stack_x.push(pop_end[no-1][0]);  // 加入归约后的产生式左边符号
			// 在goto表中寻找新的状态
			int row = stack_s.top();
			int column = findColumn(pop_end[no-1][0]);
			int newState = LRTable[row][column];
			stack_s.push(newState);
		}
		else {       // 错误动作
			if (analysis == -1) {
				cout << "error:缺少id(将id与状态5入栈)" << endl;
				stack_x.push("id");
				stack_s.push(5);
			}
			else if (analysis == -2) {
				cout << "error:不匹配的右括号(跳过右括号)" << endl;
				index++;
			}
			else if (analysis == -3) {
				cout << "error:缺少+运算符(将+与状态6入栈)" << endl;
				stack_x.push("+");
				stack_s.push(6);
			}
			else if (analysis == -4) {
				cout << "error:缺少*运算符(将*与状态7入栈)" << endl;
				stack_x.push("*");
				stack_s.push(7);
			}
			else if (analysis == -5) {
				if (inputTokens.at(index) == "*") {
					cout << "error:+运算符错写成*(将*替换为+)" << endl;
					inputTokens.at(index) = "+";
				}
			}
			else if (analysis == -6) {
				cout << "error:缺少右括号(将)与状态11入栈)" << endl;
				stack_x.push(")");
				stack_s.push(11);
			}
			else if (analysis == -7) {
				cout << "error:多输入了id(跳过该记号)" << endl;
				index++;
			}
		}
	}
	return 0;
}

int findColumn(string s)
{
	for (int i = 0; i < symbols.size(); i++) {
		if (s == symbols.at(i)) {
			return i;
		}
	}
	return -1;
}

void show_reduction(int num)
{
	switch (num)
	{
	case 1:cout << "按E->E+T归约" << endl; break;
	case 2:cout << "按E->T归约" << endl; break;
	case 3:cout << "按T->T*F归约" << endl; break;
	case 4:cout << "按T->F归约" << endl; break;
	case 5:cout << "按F->(E)归约" << endl; break;
	case 6:cout << "按F->id归约" << endl; break;
	default:
		cout << "Error in showing reduction" << endl;
		break;
	}
}*/