#ifndef _Parser_H
#define _Parser_H

#include <SimpleLParser.h>

class CParser
{
private:
	pSimpleLParser		m_Parser;
	pANTLR3_BASE_TREE	m_ASTTree;
public:
	CParser(void);
	~CParser(void);
private:
	void Destroy(void);
public:
	pANTLR3_BASE_TREE Parse(pANTLR3_COMMON_TOKEN_STREAM _Stream);
public:
	void Print(void) const;
};

#endif