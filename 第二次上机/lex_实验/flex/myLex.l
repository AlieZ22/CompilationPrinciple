%{
#include <stdlib.h>
#include <stdio.h>
#define NUM 你的学号
int num_chars = 0;
int num_ids=0;
%}
delim [ ]
letter [A-Za-z]
digit [0-9]
number {digit}+
id {letter}+

%%
{number} {int r=atoi(yytext);if(r==NUM) printf("你的名字");
else printf("%s ",yytext);
num_ids+=yyleng;}
{delim} {printf(" ");}
{id} {printf("%s ",yytext);num_chars+=yyleng;}
\n {printf("\n");}


%%
main()
{
	yylex();

	printf("\n数字的个数为： %d ,\t字母的个数为： %d ",num_ids , num_chars);
}