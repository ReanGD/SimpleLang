#ifndef _Lexer_H
#define _Lexer_H

#include <SimpleLLexer.h>

class CLexer
{
private:
	pSimpleLLexer				m_Lexer;
	pANTLR3_INPUT_STREAM		m_InStream;
	pANTLR3_COMMON_TOKEN_STREAM	m_TokStream;
public:
	CLexer(void);
	~CLexer(void);
private:
	void ParseStream(void);
	void Destroy(void);
public:
	pANTLR3_COMMON_TOKEN_STREAM Init(const char* _Path);
	pANTLR3_COMMON_TOKEN_STREAM Init(const char* _Data, unsigned int _Size);
public:
	void Print(void) const;
};

#endif