#include "scanner.h"  
#include <stdlib.h>  

Token** table;

void initTable()
{
// 	table = new Token * [3];

// 	table[0] = new Token(PUBLIC, "public");
// 	table[1] = new Token(STATIC, "static");
// 	table[2] = new Token(VOID, "void");
// 	table[3] = new Token(STRING, "String");
// 	table[4] = new Token(RETURN, "return");
// 	table[5] = new Token(WHILE, "while");
// 	table[6] = new Token(SYSOUT, "System.out.println");
// 	table[7] = new Token(IF, "if");
// 	table[8] = new Token(ELSE, "else");
// 	table[9] = new Token(EXTENDS, "extends");
// 	table[10] = new Token(LENGTH, "length");
// 	table[11] = new Token(RETURN, "return");
// 	table[12] = new Token(MAIN, "main");
// 	table[13] = new Token(INT, "int");
// 	table[14] = new Token(BOOLEAN, "boolean");
// 	table[15] = new Token(NEW, "new");
// 	table[16] = new Token(NEW, "new");
// 	table[17] = new Token(TRUE, "true");
// 	table[18] = new Token(FALSE, "false");
// 	table[19] = new Token(THIS, "this");
}

void freeTable()
{
	for (int i = 0; i < 3; i++)
		delete table[i];

	delete[] table;
}

Token* searchTable(string lexeme)
{
	for (int i = 0; i < 3; i++)
		if (lexeme == table[i]->lexeme)
			return table[i];

	return 0;
}

//Construtor
Scanner::Scanner(char * entryFile, SymbolTable* table)
{
	initTable();
	this->input = entryFile;
	cout << "Entrada: " << entryFile << endl;
	pos = 0;

	FILE* file = fopen(entryFile, "r+");
	if (file == NULL) {
		cout << "Erro ao abrir o arquivo\n";
	}
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	char *aux;
	rewind(file);
	printf("numb of bytes of file:  %d\n", size);
	aux = (char*)malloc(sizeof(char)*size);
	fread(aux, 1, size, file);
	printf("aux: %s\n", aux);
	this->input = aux;
	fclose(file);
	cout << "Arquivo de entreada: " << this->input << "\n";

}

Scanner::~Scanner()
{
	freeTable();
	fclose(file);
}

//Método que retorna o próximo token da entrada
Token*
Scanner::nextToken()
{
	Token* tok;
	string lexeme;


	//Consome espaços em branco
	while (isspace(input[pos])) {
		pos++;
	}

	//Verifica se chegou ao final do arquivo
	if (input[pos] == EOF)
	{
		tok = new Token(END_OF_FILE);

		return tok;
	}

	//Operadores relacionais
	if (input[pos] == '&')
	{
		pos++;
		if (input[pos] == '&') {
			pos++;
			tok = new Token(OP, AND);
			return tok;
		}
		lexicalError();

	}
	else if (input[pos] == '<')
	{
		pos++;
		tok = new Token(OP, LT);
		return tok;
	}
	else if (input[pos] == '>')
	{
		pos++;
		tok = new Token(OP, GT);
		return tok;
	}
	else if (input[pos] == '+')
	{
		pos++;
		tok = new Token(OP, PLUS);
		return tok;
	}
	else if (input[pos] == '-')
	{
		pos++;
		tok = new Token(OP, MINUS);
		return tok;
	}
	else if (input[pos] == '*')
	{
		pos++;
		tok = new Token(OP, TIMES);
		return tok;
	}
	else if (input[pos] == '/')
	{
		pos++;
		tok = new Token(OP, DIVISION);
		return tok;
	}
	else if (input[pos] == '=')
	{
		pos++;
		if (input[pos] == '=') {
			pos++;
			tok = new Token(OP, EQUAL);
			return tok;
		}
		else {
			tok = new Token(OP, ATTRIBUITION);
			return tok;
		}
	}
	else if (input[pos] == '!')
	{
		pos++;
		if (input[pos] == '=')
		{
			pos++;
			tok = new Token(OP, DIFFERENT);
			return tok;
		}
		else
		{
			tok = new Token(OP, NOT);
			return tok;
		}
	}

	//Identificadores
	if (isalpha(input[pos]))
	{
		lexeme.push_back(input[pos]);
		pos++;

		while (isalnum(input[pos]))
		{
			lexeme.push_back(input[pos]);
			pos++;
		}

		

		//Busco na tabela para ver se é palavra reservada
		cout << "Lexema: " << lexeme << "\n";
		tok = searchTable(lexeme);
		if(tok == 0){
			cout << "BBB\n";
			tok = new Token(ID, lexeme);
		}
		return tok;
	}

	//Números
	if (isdigit(input[pos]))
	{
		pos++;

		while (isdigit(input[pos]))
			pos++;

		tok = new Token(INTEGER_LITERAL, 69);
		return tok;
	}

	if (input[pos] == '/') {
		pos++;

		if (input[pos] == '/') {
			while (input[pos] != '\n')
				pos++;

			pos++;
			tok = new Token(SINGLE_LINE_COMMENT);
			return tok;

		}
		else if (input[pos] == '*') {
			while (input[pos] != '*' && input[pos + 1] != '/')
				pos++;

			pos++;
			tok = new Token(MULTI_LINE_COMMENT);
			return tok;
		}
	}

	lexicalError();

	tok = new Token(UNDEF);

	return tok;
}

void
Scanner::lexicalError()
{
	cout << input[pos];
	cout << "Token mal formado\n";

	exit(EXIT_FAILURE);
}

int
Scanner::getLine()
{
    return line;
}
