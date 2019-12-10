#include<iostream>
#include<string>
#include<vector>
#include<set>
using namespace std;

class Production {
public:
	char source;
	string production;
	set<char> FIRST;    // ��֤���ս�����ظ�
	vector<char> need;    // ��Ҫ����source��FIRST��
};

/*
	˵�����մ���~��ʾ
*/
int isFinalElement(char element);
void countFIRST(vector<Production>& S);

int main()
{
	vector<Production> S;
	Production temp;
	int num;     // ��¼����ʽ�ĸ���
	cout << "�������ʽ�ĸ�����" ;
	cin >> num;
	cout << "�����������ʽ(��ʽ��S->AB)��" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << i+1 << ": ";
		cin >> temp.source >> temp.production;
		temp.production = temp.production.substr(2, temp.production.size() - 2);   // ȥ��->
		cout << "source:" << temp.source << " production: " << temp.production << endl;
		temp.production += '|';
		S.push_back(temp);
	}
	countFIRST(S);
	return 0;
}


/*
	�ж�ĳ���ַ��ǲ����ս��(1:���ս����0:���ս����-1:��������)
*/
int isFinalElement(char element)
{
	// �ս����Сд��ĸ�����ֺͳ��������
	if ((element >= 'a' && element <= 'z') || (element >= '!' && element <= '@')) {
		return 1;
	}else if (element >= 'A' && element <= 'Z'){   // ���ս������д��ĸ
		return 0;
	}else{                       // ��������
		return -1;
	}
}

void countFIRST(vector<Production>& S)
{
	// ѭ������ÿһ������ʽ���õ�ÿһ��FIRST(source)
	// ��һ�ִ�ѭ����Ӧ�õ�һ�ڶ�������
	for (int i = 0; i < S.size(); i++) {
		// ��һ���������пմ�~��ֱ�Ӽ���FIRST��
		if (S[i].production.find('~')!=string::npos) {
			S[i].FIRST.insert('~');
		}
		// �ڶ������������Է��ս����ͷ�Ĳ�������ֱ�Ӽ���FIRST��
		if (isFinalElement(S[i].production[0])==1) {
			S[i].FIRST.insert(S[i].production[0]);
		}
		for (int j = 1; j < S[i].production.size(); j++) {
			if (isFinalElement(S[i].production[j]) == 1 && S[i].production[j - 1] == '|') {
				S[i].FIRST.insert(S[i].production[j]);
			}
		}
	}
	// �ڶ��ִ�ѭ����Ӧ�õ�������������
	for (int i = 0; i < S.size(); i++) {
		for (int j = 0; j < S[i].production.size(); j++) {
			// �жϲ���ʽ�е��Ӵ��ĵ�һ���ַ�Ϊ���ս��
			if ((j == 0 || S[i].production[j - 1] == '|') && isFinalElement(S[i].production[j]) == 0) {
			Label:
				S[i].need.push_back(S[i].production[j]);
				// ����source���id
				int id = 0;
				for (int k = 0; k < S.size(); k++) {
					if (S[k].source == S[i].production[j]) {
						id = k;
						break;
					}
				}
				// ������source��FIRST�����пմ�����ô����Ҫ�������Ԫ��
				if (S[id].production.find('~') != string::npos) {
					if (S[i].production[j + 1] == '|') {    // ������������Ӵ�
						S[i].FIRST.insert('~');
						j++;
						continue;
					}
					else if (isFinalElement(S[i].production[j + 1]) == 1) {   // �����ս���������������Ӵ�
						S[i].FIRST.insert(S[i].production[j + 1]);
						j++;
						continue;
					}
					else if (isFinalElement(S[i].production[j + 1]) == 0) {   // ������Ҫ�ķ��ս���������������Ԫ��
						j++;
						goto Label;
					}
				}
			}
		}
	}

	// �������ÿ��source��FIRST��
	for (int i = 0; i < S.size(); i++) {
		cout << S[i].source << "��FIRST��Ϊ: {";
		for (set<char>::iterator it = S[i].FIRST.begin(); it != S[i].FIRST.end(); it++) {
			cout << *it << " ";
		}
		cout << "} ";
		for (int j = 0; j < S[i].need.size(); j++) {
			cout <<"+ FIRST("<< S[i].need[j] << ") ";
			// ����need��source���id
			int id = 0;
			for (int k = 0; k < S.size(); k++) {
				if (S[k].source == S[i].need[j]) {
					id = k;
					break;
				}
			}
			for (int n = 0; n < S[id].FIRST.size(); n++) {
				for (set<char>::iterator it = S[id].FIRST.begin(); it != S[id].FIRST.end(); it++) {
					if (*it != '~') {
						S[i].FIRST.insert(*it);
					}
				}
			}
		}
		cout << endl;
		
		cout << "==���ȼ��ڣ�{";
		for (set<char>::iterator it = S[i].FIRST.begin(); it != S[i].FIRST.end(); it++) {
			cout << *it << " ";
		}
		cout << "} " << endl;;
	}
}
