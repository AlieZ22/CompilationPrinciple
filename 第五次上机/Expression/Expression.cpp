// Expression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"

#define E 1
#define T 2
#define E_ 3
#define T_ 4
#define F 6
#define digit 7		// 数字
#define add 8		// 左括号
#define mul 9		// 右括号
#define lb  10
#define rb	11

int nStackPtr;
int stack[100];		// 栈

void Push(int n)
{
	nStackPtr ++;

	stack[nStackPtr] = n;
}

void Pop()
{
	nStackPtr--;
}

void PrintStack()
{
	int i;
	for (i = nStackPtr; i >= 0; i--) 
	{
		if (stack[i] == E) printf("E ");
		if (stack[i] == E_ ) printf("E' ");
		if (stack[i] == T ) printf("T ");
		if (stack[i] == T_ ) printf("T' ");
		if (stack[i] == F) printf("F ");
		if (stack[i] == digit) printf("digit ");
		if (stack[i] == add) printf("+ ");
		if (stack[i] == mul) printf("* ");
		if (stack[i] == lb) printf("( ");
		if (stack[i] == rb) printf(") ");
	}
	printf("\n");
}

/////////////////////////////////////////////////////////////////
// 利用栈来分析表达式串，判定表达式串是否正确
// 
/////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	char strInput[100];	// 存放表达式串
	bool bResult;
	int nInputPtr;

	nStackPtr = -1;
	nInputPtr = 0;

	bResult = true;

	// 输入表达式串，存放在 strInput中
	printf("请输入表达式串：");
	scanf("%s",strInput);
	
	Push(E);
	PrintStack();	

	while (bResult && nStackPtr >= 0)
	{	
		switch(stack[nStackPtr])
		{
		case E:
			if (strInput[nInputPtr] >= '0' && strInput[nInputPtr] <= '9') 
			{
				Pop();
				Push(E_);
				Push(T);
			}
			else if (strInput[nInputPtr] == '(')
				{
					Pop();
					Push(E_);
					Push(T);
				}
				else
					bResult = false;
			
			PrintStack();	
			break;
		case T:
			if (strInput[nInputPtr] >= '0' && strInput[nInputPtr] <= '9') 
			{
				Pop();
				Push(T_);
				Push(F);
			}
			else if (strInput[nInputPtr] == '(')
				{
					Pop();
					Push(T_);
					Push(F);
				} 
				else bResult = false;

			PrintStack();	
			break;

		case E_:
			if (strInput[nInputPtr] == '+') 
			{
				Pop();
				Push(E_);
				Push(T);
				Push(add);
			}
			else if (strInput[nInputPtr] == ')' || strInput[nInputPtr] == 0) Pop();
				 else bResult = false;

			PrintStack();	
			break;	
		case T_:
			if (strInput[nInputPtr] == '+' || strInput[nInputPtr] == ')' || strInput[nInputPtr] == 0) Pop();
			else if (strInput[nInputPtr] == '*') 
				{
					Pop();
					Push(T_);
					Push(F);
					Push(mul);
				}  
				 else bResult = false;
			PrintStack();				
			break;
		case F:
			if (strInput[nInputPtr] >= '0' && strInput[nInputPtr]<='9') 
			{
				Pop();
				Push(digit);
			}
			else if (strInput[nInputPtr] == '(')
				{
					Pop();
					Push(rb);
					Push(E);
					Push(lb);
				}
				else bResult = false;

			PrintStack();							
			break;
		case digit:
			if (strInput[nInputPtr] >= '0' && strInput[nInputPtr]<='9') 
			{
				Pop();
				nInputPtr++;
			}
			else bResult = false;
			PrintStack();	
			break;
		case add:
			if (strInput[nInputPtr] == '+')  
			{
				Pop();
				nInputPtr++;
			}
			else bResult = false;
			PrintStack();	
			break;
		case mul:
			if (strInput[nInputPtr] == '*')  
			{
				Pop();
				nInputPtr++;
			}
			else bResult = false;
			PrintStack();	
			break;

		case lb:
			if (strInput[nInputPtr] == '(')  
			{
				Pop();
				nInputPtr++;
			}
			else bResult = false;

			PrintStack();	
			break;

		case rb:
			if (strInput[nInputPtr] == ')')  
			{
				Pop();
				nInputPtr++;
			}
			else bResult = false;

			PrintStack();	
			break;
			
		default: bResult = false; break;
		}
	}

	if (bResult == false) printf("表达式有问题了\n");
	else	printf("表达式没问题!!\n");

	

	getch();

//	printf("Hello World!\n");
	return 0;
}



