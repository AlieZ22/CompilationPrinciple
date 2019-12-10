#include"myHead.h"

void init();
bool isLetter(char letter);
bool isDigit(char digit);
bool isKeyword(string kw);
bool isId(string id);
bool isNum(string num);
string intToStr(int i);
int findToken(string key);
string lexical(string test, int lineNum);
void file_analysis(const char* filename);

string keyword[8] = { "for","if","then","else","while","do","until","int" };
map<string, int> dictionary;

int main()
{
	init();
	file_analysis("demo.txt");
	return 0;
}

// ��ʼ�����ű�
void init()
{
	dictionary.insert(map<string, int>::value_type("for", 1));
	dictionary.insert(map<string, int>::value_type("if", 2));
	dictionary.insert(map<string, int>::value_type("then", 3));
	dictionary.insert(map<string, int>::value_type("else", 4));
	dictionary.insert(map<string, int>::value_type("while", 5));
	dictionary.insert(map<string, int>::value_type("do", 6));
	dictionary.insert(map<string, int>::value_type("id", 10));
	dictionary.insert(map<string, int>::value_type("num", 11));
	dictionary.insert(map<string, int>::value_type("+", 13));
	dictionary.insert(map<string, int>::value_type("-", 14));
	dictionary.insert(map<string, int>::value_type("*", 15));
	dictionary.insert(map<string, int>::value_type("/", 16));
	dictionary.insert(map<string, int>::value_type(":", 17));
	dictionary.insert(map<string, int>::value_type(":=", 18));
	dictionary.insert(map<string, int>::value_type("<", 20));
	dictionary.insert(map<string, int>::value_type("<>", 21));
	dictionary.insert(map<string, int>::value_type("<=", 22));
	dictionary.insert(map<string, int>::value_type(">", 23));
	dictionary.insert(map<string, int>::value_type(">=", 24));
	dictionary.insert(map<string, int>::value_type("=", 25));
	dictionary.insert(map<string, int>::value_type(";", 26));
	dictionary.insert(map<string, int>::value_type("(", 27));
	dictionary.insert(map<string, int>::value_type(")", 28));
	dictionary.insert(map<string, int>::value_type("until", 29));
	dictionary.insert(map<string, int>::value_type("int", 30));
	dictionary.insert(map<string, int>::value_type("input", 31));
	dictionary.insert(map<string, int>::value_type("output", 32));
	dictionary.insert(map<string, int>::value_type("#", 0));
}

// �ж�Ϊ������ĸ
bool isLetter(char letter)
{
	if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) {
		return true;
	}
	else {
		return false;
	}
}
// �ж�Ϊ��������
bool isDigit(char digit)
{
	if (digit >= '0' && digit <= '9') {
		return true;
	}
	else {
		return false;
	}
}
// �ж�Ϊ�ؼ���
bool isKeyword(string kw)
{
	for (int i = 0; i < 8; i++) {
		if (keyword[i] == kw) {
			return true;
		}
	}
	return false;
}
// �ж�Ϊ��ʶ�� letter(letter | digit)*
bool isId(string id)
{
	if (isLetter(id[0])) {
		for (int i = 1; i < id.length(); i++) {
			if (!isLetter(id[i]) && !isDigit(id[i])) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}
// �ж�Ϊ���� digit.digit*
bool isNum(string num)
{
	if (isDigit(num[0])) {
		int pointFlag = 1;   // ֻ����һ������
		int eFlag = 1;       // ֻ����һ��E(e)
		for (int i = 0; i < num.length(); i++) {
			if (isDigit(num[i])) {
				continue;
			}
			else if (num[i] == '.' && isDigit(num[i + 1]) && pointFlag) {
				pointFlag = 0;
			}
			else if ((num[i] == 'E' || num[i] == 'e') && (isDigit(num[i + 1]) || num[i + 1] == '+' || num[i + 1] == '-') && eFlag) {
				eFlag = 0;
			}
			else if ((num[i] == '+' || num[i] == '-') && isDigit(num[i + 1])) {
				continue;
			}
			else {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}
// ������ת��Ϊ�ַ���
string intToStr(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}
// �ɴʷ���Ԫ�ҵ��ʷ��Ǻ�
int findToken(string key)
{
	map<string, int>::iterator it;
	it = dictionary.find(key);
	if (it == dictionary.end()) {
		return -1;
	}
	else {
		return it->second;
	}
}
// ��ĳ�е�һ���ʽ��з���
string lexical(string test, int lineNum)
{
	int token;
	if (isKeyword(test)) {
		token = findToken(test);
	}
	else if (isId(test)) {
		token = findToken("id");
	}
	else if (isNum(test)) {
		token = findToken("num");
	}
	else if (-1 == findToken(test)) {
		string info = "errors break in line ";
		info += intToStr(lineNum);
		return info;
	}
	else {
		token = findToken(test);
	}
	string tuple = "";
	tuple = "(" + intToStr(token) + "," + test + ")";
	return tuple;
}
// ���ļ��е�Դ������дʷ�����
void file_analysis(const char* filename)
{
	fstream file;
	int lineNum = 0;
	string currentLine;
	list<string> words;
	string tuple;
	string result = "";
	file.open(filename, ios_base::in | ios_base::out);
	if (!file.is_open()) {
		cout << "can't open the file!" << endl;
	}
	else {
		while (getline(file, currentLine))
		{
			lineNum++;

			string temp = "";
			string next = "";
			string str = "";
			// �Ե�ǰline���з���
			for (int i = 0; i < currentLine.length(); i++) {
				// ��Ϊ�ָ���������
				if (currentLine[i] == ' ') {
					continue;
				}
				else {
					temp += currentLine[i];
					next += currentLine[i + 1];
					if (isLetter(currentLine[i])) { // ��ǰɨ��Ϊ��ĸ
						//�����һ�����������հף��򽫸���ĸ���
						if (findToken(next) >= 13 && findToken(next) <= 28 || findToken(next) == 0
							|| currentLine[i + 1] == '\0' || currentLine[i + 1] == ' ')
						{
							words.push_back(temp);
							tuple = lexical(temp, lineNum);
							result += tuple;
							result += "\n";
							temp = "";
							next = "";
						}
						else {   // �������ƥ��֮���������
							next = "";
						}
					}
					else if (isDigit(currentLine[i])) {  // ��ǰɨ��Ϊ����
						//�����һ�����������հ�(������.)��ֱ�����
						if ((findToken(next) >= 13 && findToken(next) <= 28 || findToken(next) == 0) && (currentLine[i + 1] != '.')
							|| currentLine[i + 1] == '\0' || currentLine[i + 1] == ' ')
						{
							words.push_back(temp);
							tuple = lexical(temp, lineNum);
							result += tuple;
							result += "\n";
							temp = "";
							next = "";
						}
						else if (currentLine[i + 1] == '.') {   // ��һ���������С����
							str += temp;
							str += currentLine[i + 1];
							int j = i + 2;
							// ������һֱ��������һֱ��ӣ�ֱ����������Ϊֹ
							while (isDigit(currentLine[j])) {
								str += currentLine[j++];
							}
							if (isNum(str)) {  // ����һ�������֣��������
								words.push_back(str);
								tuple = lexical(str, lineNum);
								result += tuple;
								result += "\n";
								temp = "";
								i = j - 1;
							}
							else {    // ��һ���������֣������ǰ����
								words.push_back(temp);
								tuple = lexical(temp, lineNum);
								result += tuple;
								result += "\n";
								temp = "";
								next = "";
							}
						}
						else if (isDigit(currentLine[i + 1]) || isLetter(currentLine[i + 1])) {  // ��֮������
							next = "";
						}


					}
					else if (findToken(temp) >= 13 && findToken(temp) <= 28 || findToken(temp) == 0) {  // ��ǰɨ��Ϊ�����
						// ��Ϊ��������
						if ((currentLine[i] == ':' && currentLine[i + 1] == '=') || (currentLine[i] == '<' && currentLine[i + 1] == '>')
							|| (currentLine[i] == '<' && currentLine[i + 1] == '=') || (currentLine[i] == '>' && currentLine[i + 1]) == '=')
						{
							temp += next;
							words.push_back(temp);
							tuple = lexical(temp, lineNum);
							result += tuple;
							result += "\n";
							temp = "";
							next = "";
							i++;
						}
						else {
							words.push_back(temp);
							tuple = lexical(temp, lineNum);
							result += tuple;
							result += "\n";
							temp = "";
							next = "";
						}
					}
				}
			}

		}
		cout << result << endl;
	}
}
