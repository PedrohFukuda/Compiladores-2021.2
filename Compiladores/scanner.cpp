#include "scanner.h"    

Token** table;

void initTable()
{
    table = new Token*[3];

    table[0] = new Token(IF, "if");
    table[1] = new Token(ELSE, "else");
    table[2] = new Token(THEN, "then");
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
Scanner::Scanner(string input)
{
    initTable();
    this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;
    pos = 0;
}

Scanner::~Scanner()
{
    freeTable();
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    Token* tok;
    string lexeme;

    //Verifica se chegou ao final do arquivo
    if (input[pos] == '\0')
    {
        tok = new Token(END_OF_FILE);

        return tok;
    }

    //Consome espaços em branco
    while (isspace(input[pos]))
        pos++;

    //Operadores relacionais
		if (input[pos] == '&')
    {
			if(input[pos] == '&'){
				pos++
				tok = new Token(OP, AND);
				retun tok;
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
				if(input[pos] == '='){
					pos++
					tok = new Token(OP, EQUAL);
					retun tok;
				} else {
					pos--;
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
					pos--;
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
        // tok = searchTable(lexeme);
        if (!tok)
            tok = new Token(ID);
    
        return tok;
    }

    //Números
    if (isdigit(input[pos]))
    {
			pos++;

			while (isdigit(input[pos]))
					pos++;

      tok = new Token(NUMBER, INTEGER_LITERAL); 
      return tok;
    }

		if(input[pos] == '/') {
			pos++;

			if(input[pos] == '/'){
				while(input[pos] != '\n')
					pos++;

				pos++;
				tok = new Toke(SINGLE_LINE_COMMENT);
				return tok;
				
			}
			else if(input[pos] == '*') {
				while(input[pos] != '*' && input[pos+1] != '/')
					pos++;

				pos++;
				tok = new Toke(MULTI_LINE_COMMENT);
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
    cout << "Token mal formado\n";
    
    exit(EXIT_FAILURE);
}
