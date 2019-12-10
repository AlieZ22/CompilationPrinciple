/*#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

vector<string> symbols = {"id","+","*","(",")","$","E","T","F"};
// ʹ��ʮ�����Ʊ�ʾ����ߣ�0��ʾ�ƽ���1��ʾ��Լ�����ұ߱�ʾ״̬��ʮ���Ƹ�����ʾ����������࣬99��ʾacc
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
	vector<string> inputTokens = {"id","*","id","+","id","$"};   // ���봮
	int index = 0;   // ��¼��ǰ��������ɨ���λ��
	string currentToken;  // ��ǰɨ��ļǺ�
	stack<int> stack_s;  // ״̬ջ
	stack<string> stack_x;  // ����ջ
	int s_top;  // ״̬ջջ��
	string x_top;   // ����ջջ��
	int i, j; // �ֱ��ʾ�����������

	stack_s.push(0);  // ��ʼ��״̬ջ
	while (true) {
		currentToken = inputTokens.at(index);
		s_top = stack_s.top();
		
		i = s_top;  // ȷ����ǰ״̬�ǵڼ���
		j = findColumn(currentToken);  // ȷ�����������
		int analysis = LRTable[i][j];

		if (analysis == 99) {   // ���ܶ���
			cout << "����" << endl;
			break;
		}
		else if (analysis > 0x00 && analysis < 0x0F) {   // �ƽ�����
			cout << "�ƽ�" << endl;
			stack_x.push(currentToken);
			stack_s.push(analysis);
			index++;
		}
		else if (analysis > 0x10 && analysis < 0x1F) {   // ��Լ����
			int no = analysis - 0x10;  // ���ĸ�����ʽ���й�Լ
			show_reduction(no);
			x_top = stack_x.top();
			while (x_top != pop_end[no-1][1]) {  // ȷ����ʱ�ò���ʽ��ջ���
				stack_s.pop();
				stack_x.pop();
				x_top = stack_x.top();
			}
			stack_s.pop();
			stack_x.pop();

			stack_x.push(pop_end[no-1][0]);  // �����Լ��Ĳ���ʽ��߷���
			// ��goto����Ѱ���µ�״̬
			int row = stack_s.top();
			int column = findColumn(pop_end[no-1][0]);
			int newState = LRTable[row][column];
			stack_s.push(newState);
		}
		else {       // ������
			if (analysis == -1) {
				cout << "error:ȱ��id(��id��״̬5��ջ)" << endl;
				stack_x.push("id");
				stack_s.push(5);
			}
			else if (analysis == -2) {
				cout << "error:��ƥ���������(����������)" << endl;
				index++;
			}
			else if (analysis == -3) {
				cout << "error:ȱ��+�����(��+��״̬6��ջ)" << endl;
				stack_x.push("+");
				stack_s.push(6);
			}
			else if (analysis == -4) {
				cout << "error:ȱ��*�����(��*��״̬7��ջ)" << endl;
				stack_x.push("*");
				stack_s.push(7);
			}
			else if (analysis == -5) {
				if (inputTokens.at(index) == "*") {
					cout << "error:+�������д��*(��*�滻Ϊ+)" << endl;
					inputTokens.at(index) = "+";
				}
			}
			else if (analysis == -6) {
				cout << "error:ȱ��������(��)��״̬11��ջ)" << endl;
				stack_x.push(")");
				stack_s.push(11);
			}
			else if (analysis == -7) {
				cout << "error:��������id(�����üǺ�)" << endl;
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
	case 1:cout << "��E->E+T��Լ" << endl; break;
	case 2:cout << "��E->T��Լ" << endl; break;
	case 3:cout << "��T->T*F��Լ" << endl; break;
	case 4:cout << "��T->F��Լ" << endl; break;
	case 5:cout << "��F->(E)��Լ" << endl; break;
	case 6:cout << "��F->id��Լ" << endl; break;
	default:
		cout << "Error in showing reduction" << endl;
		break;
	}
}*/