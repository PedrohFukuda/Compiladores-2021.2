#include "scanner.h"

string* vet;

void print(Token*);
void allocVetor();
void freeVetor();

int main(int argc, char* argv[])
{

	string input;
	std::ifstream file("test.txt", std::ifstream::in);
	if (file) {
		while (!file.eof())
			input.push_back(file.get());
		file.close();
	}
	else {
		cout << "Arquivo nao encontrado, digite a entrada\n";
		getline(cin, input);
	}

	Scanner* scanner = new Scanner(input);

	allocVetor();
	Token* t;

	do
	{
		t = scanner->nextToken();
		print(t);
	} while (t->name != END_OF_FILE);

	delete scanner;
	system("pause");
	return 0;
}

void allocVetor()
{
	vet = new string[END_OF_FILE + 1]
	{
	"UNDEF",
	"ID",
	"SEP",
	"INTEGER_LITERAL",
	"OP",
	"AND",
	"LT",
	"GT",
	"PLUS",
	"MINUS",
	"TIMES",
	"DIVISION",
	"ATTRIBUITION",
	"EQUAL",
	"DIFFERENT",
	"NOT",
	"OPEN_PARENTHESIS",
	"CLOSE_PARENTHESIS",
	"OPEN_BRACKET",
	"CLOSE_BRACKETS",
	"OPEN_CURLY",
	"CLOSE_CURLY",
	"SEMICOLON",
	"COLON",
	"DOT",
	"SYSOUT",
	"SINGLE_LINE_COMMENT",
	"MULTI_LINE_COMMENT",
	"BLANK",
	"NEW_LINE",
	"TAB",
	"ENTER",
	"NEST_PAGE",
	"END_OF_FILE"
	};
}

void freeVetor()
{
	delete[] vet;
}

void print(Token* t)
{
	cout << vet[t->name] << " ";
	if (t->attribute != UNDEF)
	{
		cout << "(" << vet[t->attribute] << ")";
	}
	if (!t->lexeme.empty())
	{
		cout << "(" << t->lexeme << ")";
	}

	cout << "\n";
}