#include "parser.h"

void Parser::initSymbolTable(){
    Token* t;
  	cout<< "yadaaa\n";
    t = new Token(RESERV, CLASS);
  	cout<< "yoloo\n";
    globalST->add(new STEntry(t, "class", true));
  	cout<< "yadaaa\n";

    t = new Token(RESERV, EXTENDS);
    globalST->add(new STEntry(t, "extends", true));

    t = new Token(RESERV, INT);
    globalST->add(new STEntry(t, "int", true));

    t = new Token(RESERV, STRING);
    globalST->add(new STEntry(t, "string", true));

    t = new Token(RESERV, BREAK);
    globalST->add(new STEntry(t, "break", true));

    t = new Token(RESERV, RETURN);
    globalST->add(new STEntry(t, "return", true));

    t = new Token(RESERV, IF);
    globalST->add(new STEntry(t, "if", true));

    t = new Token(RESERV, ELSE);
    globalST->add(new STEntry(t, "else", true));

    t = new Token(RESERV, NEW);
    globalST->add(new STEntry(t, "new", true));
}

Parser::Parser(char * input)
{
  cout<< "111111111111\n";
	initSymbolTable();
  cout<< "222222\n";

	currentST = globalST = new SymbolTable();
	scanner = new Scanner(input, globalST);
}

void
Parser::advance()
{
	cout << "Avançando token\n";
	lToken = scanner->nextToken();
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else{
		cout << "Erro: Experava: " << t << ", encontrado: " << lToken->lexeme << "\n";
		error("Erro Inesperado");
	}
}

void
Parser::run()
{
	cout << "Iniciando Parser\n";

	if(lToken && lToken->name == END_OF_FILE)
        return;

	advance();
  currentST = new SymbolTable(currentST);
	program();
	
	cout << "Compilação encerrada com sucesso!\n";
}

void
Parser::program()
{
	cout << "Program\n";
	mainClass();
	while(lToken->attribute == CLASS){
	classDeclaration();
	}

	match(EOF);
}

void
Parser::mainClass()
{
	cout << "Main Class\n";
	match(ID);
	if(lToken->attribute == CLASS){
		match(CLASS);
		if(globalST->add(new STEntry(lToken, lToken->lexeme))){
			match(ID);
			}
			else{
					cout << "Classe " << lToken->lexeme << " já existe\n";
			}
    }
    else {
			error("esperava nome de classe");
    }
	match(OPEN_CURLY);
	match(PUBLIC);
	match(STATIC);
	match(VOID);
	match(MAIN);
	match(OPEN_PARENTHESIS);
	match(STRING);
	match(OPEN_BRACKET);
	match(CLOSE_BRACKETS);
	match(ID);
	match(OPEN_CURLY);
	statement();
	match(CLOSE_CURLY);
	match(CLOSE_CURLY);
}

void
Parser::classDeclaration()
{
	cout << "Class Declaration\n";
	match(CLASS);
	match(ID);
	if(lToken->attribute == EXTENDS){
		match(EXTENDS);
		match(ID);
	}
	match(OPEN_CURLY);
	varDeclaration();
	MethodDeclaration();
	match(CLOSE_CURLY);	
}

void
Parser::varDeclaration()
{
	cout << "Var Declaration\n";
	 type();
	 match(ID);
}

void
Parser::MethodDeclaration()
{
	cout << "Method Declaration\n";
	 match(PUBLIC);
	 type();
	 match(ID);
	 match(OPEN_PARENTHESIS);
	if(lToken->attribute == INT || lToken->attribute == BOOL || lToken->attribute == ID){
		type();
		match(ID);
		while(lToken->attribute == COLON){
			match(COLON);
			type();
			match(ID);
		}
	}

	match(CLOSE_PARENTHESIS);
	match(OPEN_CURLY);
	while(lToken->attribute == INT || lToken->attribute == BOOL || lToken->attribute == ID){
		varDeclaration();
	}
	while(lToken->attribute == OPEN_CURLY || lToken->attribute == IF || lToken->attribute == WHILE 
	|| lToken->attribute == OPEN_PARENTHESIS || lToken->attribute == SYSOUT || lToken->attribute == ID){
		statement();
	}
	match(RETURN);
	expression();
	match(SEMICOLON);
	match(CLOSE_CURLY);
}

void
Parser::type()
{
	cout << "Type\n";
	if(lToken->attribute == INT){
		match(INT);
		postTypeInt();
	}else if(lToken->attribute == BOOL){
		match(BOOL);
	} else {
		match(ID);
	}
}

void
Parser::postTypeInt()
{
	cout << "Post Type Int\n";
	if(lToken->attribute == OPEN_BRACKET){
		match(OPEN_BRACKET);
		match(CLOSE_BRACKETS);
	}
}

void
Parser::statement()
{
	cout << "Statement\n";

	if(lToken->attribute == OPEN_BRACKET){
		match(OPEN_BRACKET);
		while(lToken->attribute == OPEN_CURLY || lToken->attribute == IF || lToken->attribute == WHILE 
		|| lToken->attribute == OPEN_PARENTHESIS || lToken->attribute == SYSOUT || lToken->attribute == ID){
			statement();
		}
		match(CLOSE_BRACKETS);
	} else if(lToken->attribute == IF){
		match(IF);
		match(OPEN_PARENTHESIS);
		expression();
		match(CLOSE_PARENTHESIS);
		statement();
		match(ELSE);
		statement();
	} else if(lToken->attribute == WHILE){
		match(WHILE);
		match(OPEN_PARENTHESIS);
		expression();
		match(CLOSE_PARENTHESIS);
		statement();
	} else if(lToken->attribute == SYSOUT){
		match(SYSOUT);
		match(OPEN_PARENTHESIS);
		expression();
		match(CLOSE_PARENTHESIS);
		match(SEMICOLON);
	} else if(lToken->attribute == ID){
		match(ID);
		postStatement();
		match(SEMICOLON);
	}
}

void
Parser::postStatement()
{
	cout << "Post Statement\n";

	if(lToken->attribute == EQUAL){
		match(EQUAL);
		expression();
		match(SEMICOLON);
	} else if(lToken->attribute == OPEN_BRACKET){
		match(OPEN_BRACKET);
		expression();
		match(CLOSE_BRACKETS);
		match(EQUAL);
		expression();
		match(SEMICOLON);
	}
}

void
Parser::expression(){
	cout << "Expression\n";

	if(lToken->attribute == INTEGER_LITERAL){
		expression_();
	} else if(lToken->attribute == TRUE){
		expression_();
	} else if(lToken->attribute == FALSE){
		expression_();
	} else if(lToken->attribute == ID){
		expression_();
	} else if(lToken->attribute == THIS){
		expression_();
	} else if(lToken->attribute == NEW){
		postExpressionNew();
		expression_();
	} else if(lToken->attribute == NOT){
		expression_();
	} else if(lToken->attribute == OPEN_PARENTHESIS){
		expression_();
	}
}

void
Parser::expression_(){
	cout << "Expression_\n";

	if(lToken->attribute == OPEN_BRACKET){
		match(OPEN_BRACKET);
		expression();
		match(CLOSE_BRACKETS);
	} else if (lToken->attribute == DOT){
		match(DOT);
		postExpressionDot();
	}
}

void
Parser::postExpressionNew(){
	cout << "Post Expression New\n";
	if(lToken->attribute == INT){
		match(INT);
		match(OPEN_BRACKET);
		expression();
		match(CLOSE_BRACKETS);
	} else if(lToken->attribute == INT){
		match(ID);
		match(OPEN_PARENTHESIS);
		match(CLOSE_PARENTHESIS);
	}
}

void
Parser::postExpressionDot(){
	cout << "Post Expression Dot\n";
	if(lToken->attribute == LENGTH){
		match(LENGTH);
		expression_();
	}	 else if(lToken->attribute == ID){
		match(ID);
		match(OPEN_PARENTHESIS);
		// // 0 OR 1 
		if(lToken->attribute == INT || lToken->attribute == TRUE || lToken->attribute == FALSE 
		|| lToken->attribute == ID || lToken->attribute == THIS || lToken->attribute == NEW 
		|| lToken->attribute == NOT || lToken->attribute == OPEN_PARENTHESIS){
			expression();
			while(lToken->attribute == COLON){
				match(COLON);
				expression();
			}
		}
		match(CLOSE_PARENTHESIS);
		expression_();

	}
}

void
Parser::op(){
	cout << "OP\n";
	if(lToken->attribute == COMERCIAL_AND){
		match(COMERCIAL_AND);
		match(COMERCIAL_AND);
	} else if(lToken->attribute == LT){
		match(LT);
	} else if(lToken->attribute == GT){
		match(GT);
	} else if(lToken->attribute == EQUAL){
		match(EQUAL);
		match(EQUAL);
	} else if(lToken->attribute == NOT){
		match(NOT);
		match(EQUAL);
	} else if(lToken->attribute == PLUS){
		match(PLUS);
	} else if(lToken->attribute == MINUS){
		match(MINUS);
	} else if(lToken->attribute == TIMES){
		match(TIMES);
	} else if(lToken->attribute == DIVISION){
		match(DIVISION);
	}

}

void 
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
