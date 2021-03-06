#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;


enum Names
{
	UNDEF,//0
	ID,//1
	SEP,//2
	INTEGER_LITERAL,//3
	OP,//4
	AND,//5
	LT,//6
	GT,//7
	PLUS,//8
	MINUS,//9
	TIMES,//10
	DIVISION,//11
	ATTRIBUITION,//12
	EQUAL,//13
	DIFFERENT,//14
	NOT,//15
	OPEN_PARENTHESIS,//16
	CLOSE_PARENTHESIS,//17
	OPEN_BRACKET,//18
	CLOSE_BRACKETS,//19
	OPEN_CURLY,//20
	CLOSE_CURLY,//21
	SEMICOLON,//22
	COLON,//23
	DOT,//24
	SYSOUT,//25
	SINGLE_LINE_COMMENT,//26
	MULTI_LINE_COMMENT,//27
	BLANK,//28
	NEW_LINE,//29
	TAB,//30
	ENTER,//31
	NEST_PAGE,//32
	END_OF_FILE,//33
	CLASS, //34
	PUBLIC, //35
	STATIC, //36
	VOID, //37
	EXTENDS, //38
	STRING, //39
	MAIN, //40
	RETURN, //41
	INT, //42
	THEN, //43
	IF, //44
	ELSE, //45
	WHILE, //46
	BOOL, //47
	TRUE, //48
	FALSE, //49
	THIS, //50
	NEW, //51
	LENGTH, //52
	COMERCIAL_AND, //53
	BOOLEAN, //54
	RESERV, //55
	BREAK, //56
};

class Token
{
public:
	int name;
	int attribute;
	string lexeme;

	Token(int name, string lexeme)
	{
		this->name = name;
		this->lexeme = lexeme;
		attribute = UNDEF;
	}

	Token(int name)
	{
		this->name = name;
		attribute = UNDEF;
	}

	Token(int name, int attr)
	{
		this->name = name;
		attribute = attr;
	}
};