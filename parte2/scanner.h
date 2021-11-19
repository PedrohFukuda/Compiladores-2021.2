#include "symboltable.cpp"
#include <fstream>

class Scanner
{
private:
	char * input;//Armazena o texto de entrada
	int pos;//Posição atual
  int line;
	FILE* file;
	SymbolTable *st;

public:
	//Construtor
	Scanner(char *, SymbolTable* table);
	~Scanner();

	//Método que retorna o próximo token da entrada
	Token* nextToken();

  int getLine();
	
	//Método para manipular erros
	void lexicalError();
};
