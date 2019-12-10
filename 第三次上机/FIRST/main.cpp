#include<iostream>
#include<string>
#include<vector>
#include<set>
using namespace std;

class Production {
public:
	char source;
	string production;
	set<char> FIRST;    // 保证非终结符不重复
	vector<char> need;    // 需要其他source的FIRST集
};

/*
	说明：空串用~表示
*/
int isFinalElement(char element);
void countFIRST(vector<Production>& S);

int main()
{
	vector<Production> S;
	Production temp;
	int num;     // 记录产生式的个数
	cout << "输入产生式的个数：" ;
	cin >> num;
	cout << "依次输入产生式(格式：S->AB)：" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << i+1 << ": ";
		cin >> temp.source >> temp.production;
		temp.production = temp.production.substr(2, temp.production.size() - 2);   // 去掉->
		cout << "source:" << temp.source << " production: " << temp.production << endl;
		temp.production += '|';
		S.push_back(temp);
	}
	countFIRST(S);
	return 0;
}


/*
	判断某个字符是不是终结符(1:是终结符；0:非终结符；-1:其他符号)
*/
int isFinalElement(char element)
{
	// 终结符：小写字母，数字和常用运算符
	if ((element >= 'a' && element <= 'z') || (element >= '!' && element <= '@')) {
		return 1;
	}else if (element >= 'A' && element <= 'Z'){   // 非终结符：大写字母
		return 0;
	}else{                       // 其他符号
		return -1;
	}
}

void countFIRST(vector<Production>& S)
{
	// 循环遍历每一个产生式，得到每一个FIRST(source)
	// 第一轮大循环：应用第一第二条规则
	for (int i = 0; i < S.size(); i++) {
		// 第一条规则：若有空串~则直接加入FIRST集
		if (S[i].production.find('~')!=string::npos) {
			S[i].FIRST.insert('~');
		}
		// 第二条规则：若有以非终结符开头的产生串则直接加入FIRST集
		if (isFinalElement(S[i].production[0])==1) {
			S[i].FIRST.insert(S[i].production[0]);
		}
		for (int j = 1; j < S[i].production.size(); j++) {
			if (isFinalElement(S[i].production[j]) == 1 && S[i].production[j - 1] == '|') {
				S[i].FIRST.insert(S[i].production[j]);
			}
		}
	}
	// 第二轮大循环：应用第三第四条规则
	for (int i = 0; i < S.size(); i++) {
		for (int j = 0; j < S[i].production.size(); j++) {
			// 判断产生式中的子串的第一个字符为非终结符
			if ((j == 0 || S[i].production[j - 1] == '|') && isFinalElement(S[i].production[j]) == 0) {
			Label:
				S[i].need.push_back(S[i].production[j]);
				// 根据source获得id
				int id = 0;
				for (int k = 0; k < S.size(); k++) {
					if (S[k].source == S[i].production[j]) {
						id = k;
						break;
					}
				}
				// 如果这个source的FIRST集中有空串，那么还需要看下面的元素
				if (S[id].production.find('~') != string::npos) {
					if (S[i].production[j + 1] == '|') {    // 继续看下面的子串
						S[i].FIRST.insert('~');
						j++;
						continue;
					}
					else if (isFinalElement(S[i].production[j + 1]) == 1) {   // 加入终结符后继续看下面的子串
						S[i].FIRST.insert(S[i].production[j + 1]);
						j++;
						continue;
					}
					else if (isFinalElement(S[i].production[j + 1]) == 0) {   // 加入需要的非终结符并继续看下面的元素
						j++;
						goto Label;
					}
				}
			}
		}
	}

	// 遍历输出每个source的FIRST集
	for (int i = 0; i < S.size(); i++) {
		cout << S[i].source << "的FIRST集为: {";
		for (set<char>::iterator it = S[i].FIRST.begin(); it != S[i].FIRST.end(); it++) {
			cout << *it << " ";
		}
		cout << "} ";
		for (int j = 0; j < S[i].need.size(); j++) {
			cout <<"+ FIRST("<< S[i].need[j] << ") ";
			// 根据need的source获得id
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
		
		cout << "==》等价于：{";
		for (set<char>::iterator it = S[i].FIRST.begin(); it != S[i].FIRST.end(); it++) {
			cout << *it << " ";
		}
		cout << "} " << endl;;
	}
}
