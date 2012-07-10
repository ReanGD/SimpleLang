#include <Lexer.h>

CLexer::CLexer(void) : m_Lexer(NULL), m_InStream(NULL), m_TokStream(NULL)
{

}

CLexer::~CLexer(void)
{
	Destroy();
}

void CLexer::ParseStream(void)
{
	m_Lexer = SimpleLLexerNew(m_InStream);
	if(m_Lexer == NULL)
	{
		char ErrMsg[512];
		sprintf(ErrMsg, "Unable to create the lexer due to malloc() failure\n");
		throw ErrMsg;
	}

	m_TokStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(m_Lexer));
	if(m_TokStream == NULL)
	{
		char ErrMsg[512];
		sprintf(ErrMsg, "Out of memory trying to allocate token stream\n");
		throw ErrMsg;		
	}
}

void CLexer::Destroy(void)
{
	if(m_TokStream)
	{
		m_TokStream->free(m_TokStream);
		m_TokStream = NULL;
	}
	if(m_Lexer)
	{
		m_Lexer->free(m_Lexer);
		m_Lexer = NULL;
	}
	if(m_InStream)
	{
		m_InStream->close(m_InStream);
		m_InStream = NULL;
	}
}

pANTLR3_COMMON_TOKEN_STREAM CLexer::Init(const char* _Path)
{
	Destroy();

	if(_Path == NULL)
	{
		char ErrMsg[512];
		sprintf(ErrMsg, "Path to program is NULL\n");
		throw ErrMsg;
	}

	m_InStream = antlr3FileStreamNew((pANTLR3_UINT8)_Path, ANTLR3_ENC_8BIT);
	m_InStream->setUcaseLA(m_InStream, ANTLR3_TRUE);

	if(m_InStream == NULL)
	{
		char ErrMsg[512];
		sprintf(ErrMsg, "Unable to open file %s\n", _Path);
		throw ErrMsg;
	}

	ParseStream();
	return m_TokStream;
}

pANTLR3_COMMON_TOKEN_STREAM CLexer::Init(const char* _Data, unsigned int _Size)
{
	Destroy();
	
	if(_Data == NULL)
	{
		char ErrMsg[512];
		sprintf(ErrMsg, "Program text is NULL\n");
		throw ErrMsg;
	}

	m_InStream = antlr3StringStreamNew((pANTLR3_UINT8)_Data, ANTLR3_ENC_8BIT, _Size, (pANTLR3_UINT8)"Stream from text");
	m_InStream->setUcaseLA(m_InStream, ANTLR3_TRUE);

	if(m_InStream == NULL)
	{
		char ErrMsg[512];
		sprintf(ErrMsg, "Unable to open stream\n");
		throw ErrMsg;
	}

	ParseStream();
	return m_TokStream;
}

void CLexer::Print(void) const
{
	if(m_TokStream == NULL)
	{
		char ErrMsg[512];
		sprintf(ErrMsg, "Token stream is NULL\n");
		throw ErrMsg;
	}

	pANTLR3_TOKEN_SOURCE TokenSource = m_TokStream->tstream->tokenSource;
	pANTLR3_COMMON_TOKEN Token = TokenSource->nextToken(TokenSource);
	while (Token != NULL && Token->type != ANTLR3_TOKEN_EOF)
	{
		if(Token->getChannel(Token) == 0)
			printf("%s\n", Token->toString(Token)->chars);
		Token = TokenSource->nextToken(TokenSource);
	}
}