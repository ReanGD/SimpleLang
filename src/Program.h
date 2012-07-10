#ifndef _Program_H
#define _Program_H

#include <Command.h>
#include <vector>

class CProgram
{
public:
	typedef std::vector<CCommand>		t_commands;
	typedef std::vector<const char*>	t_variables;
private:
	t_commands		m_Commands;
	t_variables		m_Variables;
	unsigned int	m_RegisterCounter;
public:
	CProgram(void);
	~CProgram(void);
private:
	void Destroy(void);
public:
	void AddCmd(CCommand _Cmd);
	CCommand GetCmd(unsigned int _Index);
public:
	unsigned int GetVariableIndex(const char* _Name);
	unsigned int GetRegisterIndex(void);
	unsigned int GetCntCommand(void) const;
	unsigned int GetCntVariable(void) const;
	unsigned int GetCntRegister(void) const;
public:
	void Print(void) const;
};

#endif