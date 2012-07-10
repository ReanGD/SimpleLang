#include <Parser.h>

CParser::CParser(void) : m_Parser(NULL), m_ASTTree(NULL)
{

}

CParser::~CParser(void)
{
	Destroy();
}

void CParser::Destroy(void)
{
	if(m_Parser)
	{
		m_Parser->free(m_Parser);
		m_Parser = NULL;
	}
	m_ASTTree = NULL;
}

pANTLR3_BASE_TREE CParser::Parse(pANTLR3_COMMON_TOKEN_STREAM _Stream)
{
	Destroy();

	if(_Stream == NULL)
	{
		char _ErrMsg[512];
		sprintf(_ErrMsg, "Input stream for parser is NULL\n");
		throw _ErrMsg;
	}

	m_Parser = SimpleLParserNew(_Stream);
	if(m_Parser == NULL)
	{
		char _ErrMsg[512];
		sprintf(_ErrMsg, "Out of memory trying to allocate parser\n");
		throw _ErrMsg;
	}

	SimpleLParser_program_return AST = m_Parser->program(m_Parser);
	m_ASTTree = AST.tree;

	if(m_Parser->pParser->rec->state->errorCount > 0)
	{
		char _ErrMsg[512];
		sprintf(_ErrMsg, "The parser returned %d errors, tree walking aborted.\n", m_Parser->pParser->rec->state->errorCount);
		throw _ErrMsg;
	}

	return m_ASTTree;
}

static void PrintToken(pANTLR3_COMMON_TOKEN _Token, int _Lvl, int _IsParent)
{
	for(int i=0; i!=_Lvl; ++i)
		printf(" ");

	/*if(_IsParent==0)
		printf("");
	else
		printf("");*/

	if(_Token == NULL)
		printf("NULL\n");
	else if ((_Token->line == 0) && (_Token->charPosition == 0))
		printf("%s(virt=%s)\n", _Token->getText(_Token)->chars, _Token->toString(_Token)->chars);
	else
		printf("%s (%s)\n", _Token->getText(_Token)->chars, _Token->toString(_Token)->chars);
}

static void PrintTree(pANTLR3_BASE_TREE _Tree, pANTLR3_COMMON_TOKEN _Token, int _Lvl)
{
	ANTLR3_UINT32 Count = _Tree->getChildCount(_Tree);
	if(_Lvl >= 0)
		PrintToken(_Token, _Lvl, Count);
	for(ANTLR3_UINT32 i=0; i!=Count; ++i)
	{
		pANTLR3_BASE_TREE Child = (pANTLR3_BASE_TREE)_Tree->getChild(_Tree, i);
		PrintTree(Child, Child->getToken(Child), _Lvl+1);
	}
}

void CParser::Print(void) const
{
	if(m_ASTTree == NULL)
	{
		char _ErrMsg[512];
		sprintf(_ErrMsg, "AST tree is NULL\n");
		throw _ErrMsg;
	}
	PrintTree(m_ASTTree, NULL, -1);
}