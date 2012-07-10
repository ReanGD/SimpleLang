#include <Program.h>
#include <SimpleLLexer.h>

CProgram::CProgram(void) : m_RegisterCounter(0)
{

}

CProgram::~CProgram(void)
{
	Destroy();
}

void CProgram::Destroy(void)
{
	m_Commands.clear();
	m_Variables.clear();
	m_RegisterCounter = 0;
}

void CProgram::AddCmd(CCommand _Cmd)
{
	m_Commands.push_back(_Cmd);
}

CCommand CProgram::GetCmd(unsigned int _Index)
{
	if(_Index >= m_Commands.size())
	{
		char ErrMsg[512];
		sprintf(ErrMsg, "Error command index\n");
		throw ErrMsg;
	}
	return m_Commands[_Index];
}

unsigned int CProgram::GetVariableIndex(const char* _Name)
{
	int i = 0;
	for(t_variables::iterator it=m_Variables.begin(), it_end=m_Variables.end(); it!=it_end; ++it, ++i)
		if (strcmp(*it, _Name) == 0)
			return i;
	
	m_Variables.push_back(_Name);
	return m_Variables.size()-1;
}

unsigned int CProgram::GetRegisterIndex(void)
{
	return m_RegisterCounter++;
}

unsigned int CProgram::GetCntCommand(void) const
{
	return m_Commands.size();
}

unsigned int CProgram::GetCntVariable(void) const
{
	return m_Variables.size();
}

unsigned int CProgram::GetCntRegister(void) const
{
	return m_RegisterCounter;
}


void CProgram::Print(void) const
{
	for(t_commands::const_iterator it=m_Commands.begin(), it_end=m_Commands.end(); it!=it_end; ++it)
		it->Print();
}