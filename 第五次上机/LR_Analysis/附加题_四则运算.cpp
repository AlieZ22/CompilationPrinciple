#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

vector<string> symbols = { "id","+","-","*","/","(",")","$","E","T","F" };
// ʹ��ʮ�����Ʊ�ʾ����ߣ�0��ʾ�ƽ���1��ʾ��Լ�����ұ߱�ʾ״̬��ʮ���Ƹ�����ʾ����������࣬99��ʾacc
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
string pop_end[8][2] = {
	{"E","E"},    // 1,E->E+T
	{"E","E"},    // 2,E->E-T
	{"E","T"},    // 3,E->T
	{"T","T"},    // 4,T->T*F
	{"T","T"},    // 5,T->T/F
	{"T","F"},    // 6,T->F
	{"F","("},    // 7,F->(E)
	{"F","id"}    // 8,F->id
};
void initPop_end();
int findColumn(string s);
void show_reduction(int num);

int main()
{
	//vector<string> inputTokens = { "id","/","id","*","id","-","id","$" };   // ���봮
	//vector<string> inputTokens = { "id","/","(","id","-","id",")","$" };
	vector<string> inputTokens = { "id","+","id","+","id","*","id","$" };
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
		else if (analysis > 0x00 && analysis <= 0x0F) {   // �ƽ�����
			cout << "�ƽ�" << endl;
			stack_x.push(currentToken);
			stack_s.push(analysis);
			index++;
		}
		else if (analysis > 0x10 && analysis <= 0x1F) {   // ��Լ����
			int no = analysis - 0x10;  // ���ĸ�����ʽ���й�Լ
			show_reduction(no);
			x_top = stack_x.top();
			while (x_top != pop_end[no - 1][1]) {  // ȷ����ʱ�ò���ʽ��ջ���
				stack_s.pop();
				stack_x.pop();
				x_top = stack_x.top();
			}
			stack_s.pop();
			stack_x.pop();

			stack_x.push(pop_end[no - 1][0]);  // �����Լ��Ĳ���ʽ��߷���
			// ��goto����Ѱ���µ�״̬
			int row = stack_s.top();
			int column = findColumn(pop_end[no - 1][0]);
			int newState = LRTable[row][column];
			stack_s.push(newState);
		}
		else if(analysis<0) {       // ������
			cout << "error��exit! ���ķ�����SLR��" << endl;
			break;
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
	case 2:cout << "��E->E-T��Լ" << endl; break;
	case 3:cout << "��E->T��Լ" << endl; break;
	case 4:cout << "��T->T*F��Լ" << endl; break;
	case 5:cout << "��T->T/F��Լ" << endl; break;
	case 6:cout << "��T->F��Լ" << endl; break;
	case 7:cout << "��F->(E)��Լ" << endl; break;
	case 8:cout << "��F->id��Լ" << endl; break;
	default:
		cout << "Error in showing reduction" << endl;
		break;
	}
}