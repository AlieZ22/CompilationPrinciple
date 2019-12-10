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

// 初始化符号表
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

// 判断为单个字母
bool isLetter(char letter)
{
	if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) {
		return true;
	}
	else {
		return false;
	}
}
// 判断为单个数字
bool isDigit(char digit)
{
	if (digit >= '0' && digit <= '9') {
		return true;
	}
	else {
		return false;
	}
}
// 判断为关键词
bool isKeyword(string kw)
{
	for (int i = 0; i < 8; i++) {
		if (keyword[i] == kw) {
			return true;
		}
	}
	return false;
}
// 判断为标识符 letter(letter | digit)*
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
// 判断为数字 digit.digit*
bool isNum(string num)
{
	if (isDigit(num[0])) {
		int pointFlag = 1;   // 只能有一个数点
		int eFlag = 1;       // 只能有一个E(e)
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
// 将数字转化为字符串
string intToStr(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}
// 由词法单元找到词法记号
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
// 对某行的一个词进行分析
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
// 对文件中的源程序进行词法分析
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
			// 对当前line进行分析
			for (int i = 0; i < currentLine.length(); i++) {
				// 若为分隔符，跳过
				if (currentLine[i] == ' ') {
					continue;
				}
				else {
					temp += currentLine[i];
					next += currentLine[i + 1];
					if (isLetter(currentLine[i])) { // 当前扫描为字母
						//如果下一个是运算符或空白，则将该字母输出
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
						else {   // 否则继续匹配之后的作连接
							next = "";
						}
					}
					else if (isDigit(currentLine[i])) {  // 当前扫描为数字
						//如果下一个是运算符或空白(不包括.)，直接输出
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
						else if (currentLine[i + 1] == '.') {   // 下一个运算符是小数点
							str += temp;
							str += currentLine[i + 1];
							int j = i + 2;
							// 若后面一直是数字则一直添加，直到不是数字为止
							while (isDigit(currentLine[j])) {
								str += currentLine[j++];
							}
							if (isNum(str)) {  // 若这一串是数字，输出数字
								words.push_back(str);
								tuple = lexical(str, lineNum);
								result += tuple;
								result += "\n";
								temp = "";
								i = j - 1;
							}
							else {    // 这一串不是数字，输出当前符号
								words.push_back(temp);
								tuple = lexical(temp, lineNum);
								result += tuple;
								result += "\n";
								temp = "";
								next = "";
							}
						}
						else if (isDigit(currentLine[i + 1]) || isLetter(currentLine[i + 1])) {  // 与之后的组合
							next = "";
						}


					}
					else if (findToken(temp) >= 13 && findToken(temp) <= 28 || findToken(temp) == 0) {  // 当前扫描为运算符
						// 若为组合运算符
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
