#include <Lexer.h>
#include <Parser.h>
#include <Compiler.h>
#include <Interpreter.h>

int ANTLR3_CDECL main(int argc, char *argv[])
{
	const char* Path;

	if(argc < 2 || argv[1] == NULL)
		Path = "../test/input";
	else
		Path = argv[1];

	int result = -1;
	CLexer Lexer;
	CProgram Prg;
	CParser Parser;
	CCompiler Compiler;
	CInterpreter Interpreter;
	pANTLR3_BASE_TREE ASTTree;
	pANTLR3_COMMON_TOKEN_STREAM TokStream;
	try
	{
		TokStream = Lexer.Init(Path);
		ASTTree   = Parser.Parse(TokStream);
		Parser.Print();
		Prg = Compiler.Compile(ASTTree);
		Prg.Print();
		Interpreter.Execute(&Prg);
		result = 0;
	}
	catch(const char* _ErrMsg)
	{
		printf("%s\n", _ErrMsg);
	}
	return result;
}