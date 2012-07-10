#ifndef _Interpreter_H
#define _Interpreter_H

#include <Program.h>

class CInterpreter
{
public:
	CInterpreter(void);
	~CInterpreter(void);
public:
	void Execute(CProgram* _Prg) const;
};

#endif