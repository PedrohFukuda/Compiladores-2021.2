#include "scanner.cpp"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;
		SymbolTable *currentST, *globalST; 

		void advance();
		void match(int);
		

	public:
		Parser(char *);
		void initSymbolTable();
		void run();

		void program();
		void mainClass();
		void classDeclaration();
		void varDeclaration();
		void MethodDeclaration();
		void type();
		void postTypeInt();
		void statement();
		void postStatement();
		void expression();
		void expression_();
		void postExpressionNew();
		void postExpressionDot();
		void op();

		void error(string);
};