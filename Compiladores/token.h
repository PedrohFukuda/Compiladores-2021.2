#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,//0
    ID,//1
    IF,//2
    ELSE,//3
    THEN,//4
    RELOP,//5
    EQ,//6
    NE,//7
    GT,//8
    GE,//9
    LT,//10
    LE,//11
    NUMBER,//12
    DOUBLE_LITERAL,//13
    FLOAT_LITERAL,//14
    INTEGER_LITERAL,//15
    END_OF_FILE//16
};

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
		TIMES,//12
		DIVISION,//11
		ATTRIBUITION,//12
		EQUAL,//13
		DIFFERENT,//14
		NOT,//15
    SEP,//16
		OPEN_PARENTHESIS,//17
		CLOSE_PARENTHESIS,//18
		OPEN_BRACKET,//19
		CLOSE_BRACKETS,//20
		OPEN_CURLY,//21
		CLOSE_CURLY,//22
		SEMICOLON,//23
		COLON,//24
		DOT,//25
		SYSOUT,//26
		SINGLE_LINE_COMMENT,//27
		MULTI_LINE_COMMENT,//28
		BLANK,//30
		NEW_LINE,//31
		TAB,//32
		ENTER,//33
		NEST_PAGE,//34
    END_OF_FILE//35
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