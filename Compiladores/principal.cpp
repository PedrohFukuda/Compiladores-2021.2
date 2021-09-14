#include "scanner.h"

string* vet;

void print(Token*);
void allocVetor();
void freeVetor();

int main(int argc, char* argv[]) 
{
    string input;
    
    getline(cin, input);

    Scanner* scanner = new Scanner(input);

    allocVetor();
    Token* t;

    do
    {
        t = scanner->nextToken();
        print(t);
    }while (t->name != END_OF_FILE);

    delete scanner;
    system("pause");
    return 0;
}

void allocVetor()
{
    vet = new string[34];

    vet[0] = "UNDEF";//0
    vet[1] = "ID";//1
    vet[2] = "SEP";//2
    vet[3] = "INTEGER_LITERAL";//3
    vet[4] = "OP";//4
    vet[5] = "AND"; //5
    vet[6] = "LT";//6
    vet[7] = "GT";//7
    vet[8] = "PLUS";//8
    vet[9] = "MINUS";//9
    vet[10] = "TIMES";//10
    vet[11] = "DIVISION";//11
    vet[12] = "ATTRIBUITION";//12
    vet[13] = "EQUAL";//13
    vet[14] = "DIFFERENT";//14
    vet[15] = "NOT";//15
    vet[16] = "OPEN_PARENTHESIS";//16
    vet[17] = "CLOSE_PARENTHESIS";//17
    vet[18] = "OPEN_BRACKET";//1
    vet[19] = "CLOSE_BRACKETS";//2
    vet[20] = "OPEN_CURLY";//3
    vet[21] = "CLOSE_CURLY";//4
    vet[22] = "SEMICOLON"; //5
    vet[23] = "COLON";//6
    vet[24] = "DOT";//7
    vet[25] = "SYSOUT";//8
    vet[26] = "SINGLE_LINE_COMMENT";//9
    vet[27] = "MULTI_LINE_COMMENT";//10
    vet[28] = "BLANK";//11
    vet[29] = "NEW_LINE";//29
    vet[30] = "TAB";//30
    vet[31] = "ENTER";//31
    vet[32] = "NEST_PAGE";//32
    vet[33] = "END_OF_FILE";//33
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