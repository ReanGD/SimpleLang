#ifndef _Compiler_H
#define _Compiler_H

#include <Program.h>
#include <antlr3.h>

class CCompiler
{
public:
	CCompiler(void);
	~CCompiler(void);
public:
	CProgram Compile(pANTLR3_BASE_TREE _ASTTree) const;
};

#endif