#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<sstream>
using namespace std;

class Symbol {
public:
	string symbol;   // ��ʾid,+,-,E,T��
	double val;

	Symbol() {}
	Symbol(string symbol,double val=0) {
		this->symbol = symbol;
		this->val = val;
	}
};

vector<string> symbols = { "id","+","-","*","/","(",")","$","E","T","F" };
// ʹ��ʮ�����Ʊ�ʾ����ߣ�0��ʾ�ƽ���1��ʾ��Լ�����ұ߱�ʾ״̬��ʮ���Ƹ�����ʾ����������࣬99��ʾacc
// ��������ͳ���
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
	//vector<string> inputStr = { "5","+","3","+","8","*","2","$" };  // ����
	vector<string> inputStr = { "10","-","6","/","1e2","$" };    // ֧�ָ������Ϳ�ѧ������
	//vector<string> inputStr = {"3","+","+","2.09","$"};    // ��������
	int index = 0;
	Symbol current;   // ��ǰ���������
	stack<int> stack_s;    // ״̬ջ
	stack<Symbol> stack_x;   // ����ջ
	int s_top;    // ״̬ջջ��
	Symbol x_top;  // ����ջ
	int i, j;    // LR�����������

	stack_s.push(0);    // ��ʼ������ջ
	while (true) {
		match(inputStr.at(index), current);
		s_top = stack_s.top();

		i = s_top;   // ȷ����ǰ״̬�ǵڼ���
		j = findColumn(current.symbol);   // ȷ����ǰ״̬�ǵڼ���
		int analysis = LRTable[i][j];

		if (analysis == 99) {   // ���ܶ���
			cout << "����" << endl;
			cout << "���ս����" << stack_x.top().val << endl;
			break;
		}
		else if (analysis > 0x00 && analysis <= 0x0f) {   // �ƽ�����
			cout << "�ƽ�" << endl;
			stack_x.push(current);
			stack_s.push(analysis);
			index++;
		}
		else if (analysis > 0x10 && analysis <= 0x1F) {   // ��Լ����
			int no = analysis - 0x10;  // ���ĸ�����ʽ���й�Լ
			double val1 = 0.0, val2 = 0.0;
			int row = -1, column = -1, newState = -1;
			Symbol temp;
			switch (no) {
			case 1:   // ��E->E+T��Լ
			case 2:   // ��E->E-T��Լ
			case 4:   // ��T->T*F��Լ
			case 5:   // ��T->T/F��Լ
				val2 = stack_x.top().val;
				stack_s.pop(); stack_x.pop();
				stack_s.pop(); stack_x.pop();
				val1 = stack_x.top().val;
				stack_s.pop(); stack_x.pop();
				if (no == 1) {
					cout << "��E->E+T��Լ: E.val="<<val1<<"+"<<val2 << endl;
					temp = Symbol("E", val1 + val2);
				}
				else if (no == 2) {
					cout << "��E->E-T��Լ: E.val=" << val1 << "-" << val2 << endl;
					temp = Symbol("E", val1 - val2);
				}
				else if (no == 4) {
					cout << "��T->T*F��Լ: T.val=" << val1 << "*" << val2 << endl;
					temp = Symbol("T", val1 * val2);
				}
				else if (no == 5) {
					cout << "��T->T/F��Լ: T.val=" << val1 << "/" << val2 << endl;
					temp = Symbol("T", val1 / val2);
				}
				stack_x.push(temp);
				break;
			case 3:   // ��E->T��Լ
			case 6:   // ��T->F��Լ
			case 8:   // ��F->id��Լ
				val1 = stack_x.top().val;
				stack_s.pop(); stack_x.pop();
				if (no == 3) {
					cout << "��E->T��Լ: E.val="<<val1 << endl;
					temp = Symbol("E", val1);
				}
				else if (no == 6) {
					cout << "��T->F��Լ: T.val="<<val1 << endl;
					temp = Symbol("T", val1);
				}
				else if (no == 8) {
					cout << "��F->id��Լ: F.val="<<val1 << endl;
					temp = Symbol("F", val1);
				}
				stack_x.push(temp);
				break;
			case 7:   // ��F->(E)��Լ
				stack_s.pop(); stack_x.pop();
				val1 = stack_x.top().val;
				stack_s.pop(); stack_x.pop();
				stack_s.pop(); stack_x.pop();
				cout << "��F->(E)��Լ: F.val=" << val1 << endl;
				temp = Symbol("F", val1);
				stack_x.push(temp);
				break;
			default:
				break;
			}
			// ��goto����Ѱ���µ�״̬
			row = stack_s.top();
			column = findColumn(temp.symbol);
			newState = LRTable[row][column];
			stack_s.push(newState);
		}
		else if (analysis < 0) {    // ������
			cout << "error: ���������������룡" << endl;
			break;
		}
	}
	return 0;
}


// ���ַ���ת�������֣�֧��С����
void string2num(string str, double& num)
{
	stringstream ss;
	ss << str;
	ss >> num;
}

// ���ݵ�ǰ����λ�õ����ݷ���һ����װ��Symbol
void match(string current, Symbol& s)
{
	char first = current.at(0);
	//��һ���ַ��������֣���ô��һ��������
	if (first >= 48 && first <= 57) {
		double num = 0.0;
		string2num(current, num);
		s.symbol = "id";
		s.val = num;
	}
	else {   // �����������+,-,*,/,(,),$
		s.symbol = current;
	}
}

// ���ݵ�ǰ������ķ����ҵ�����
int findColumn(string s)
{
	for (int i = 0; i < symbols.size(); i++) {
		if (s == symbols.at(i)) {
			return i;
		}
	}
	return -1;
}