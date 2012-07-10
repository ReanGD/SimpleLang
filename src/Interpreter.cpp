#include <Interpreter.h>
#include <stdio.h>

CInterpreter::CInterpreter(void)
{

}

CInterpreter::~CInterpreter(void)
{

}

static void ExecCommand(CCommand _Cmd, int *_Reg, int *_Mem)
{
	char ErrMsg[512];
	switch(_Cmd.Cmd)
	{
		case CCommand::MUL_RRR:        //mul reg, reg, reg
			_Reg[_Cmd.Dest] = _Reg[_Cmd.Src1] * _Reg[_Cmd.Src2];
			break;
		case CCommand::MUL_RRV:        //mul reg, reg, val
			_Reg[_Cmd.Dest] = _Reg[_Cmd.Src1] * _Cmd.Src2;
			break;
		case CCommand::MUL_RVR:        //mul reg, val, reg
			_Reg[_Cmd.Dest] = _Cmd.Src1 * _Reg[_Cmd.Src2];
			break;
		case CCommand::MUL_RVV:        //mul reg, val, val
			_Reg[_Cmd.Dest] = _Cmd.Src1 * _Cmd.Src2;
			break;
		case CCommand::DIV_RRR:        //div reg, reg, reg
			_Reg[_Cmd.Dest] = _Reg[_Cmd.Src1] / _Reg[_Cmd.Src2];
			break;
		case CCommand::DIV_RRV:        //div reg, reg, val
			_Reg[_Cmd.Dest] = _Reg[_Cmd.Src1] / _Cmd.Src2;
			break;
		case CCommand::DIV_RVR:        //div reg, val, reg
			_Reg[_Cmd.Dest] = _Cmd.Src1 / _Reg[_Cmd.Src2];
			break;
		case CCommand::DIV_RVV:        //div reg, val, val
			_Reg[_Cmd.Dest] = _Cmd.Src1 / _Cmd.Src2;
			break;
		case CCommand::ADD_RRR:        //add reg, reg, reg
			_Reg[_Cmd.Dest] = _Reg[_Cmd.Src1] + _Reg[_Cmd.Src2];
			break;
		case CCommand::ADD_RRV:        //add reg, reg, val
			_Reg[_Cmd.Dest] = _Reg[_Cmd.Src1] + _Cmd.Src2;
			break;
		case CCommand::ADD_RVR:        //add reg, val, reg
			_Reg[_Cmd.Dest] = _Cmd.Src1 + _Reg[_Cmd.Src2];
			break;
		case CCommand::ADD_RVV:        //add reg, val, val
			_Reg[_Cmd.Dest] = _Cmd.Src1 + _Cmd.Src2;
			break;
		case CCommand::SUB_RRR:        //sub reg, reg, reg
			_Reg[_Cmd.Dest] = _Reg[_Cmd.Src1] - _Reg[_Cmd.Src2];
			break;
		case CCommand::SUB_RRV:        //sub reg, reg, val
			_Reg[_Cmd.Dest] = _Reg[_Cmd.Src1] - _Cmd.Src2;
			break;
		case CCommand::SUB_RVR:        //sub reg, val, reg
			_Reg[_Cmd.Dest] = _Cmd.Src1 - _Reg[_Cmd.Src2];
			break;
		case CCommand::SUB_RVV:        //sub reg, val, val
			_Reg[_Cmd.Dest] = _Cmd.Src1 - _Cmd.Src2;
			break;
		case CCommand::MOV_RR:         //mov reg, reg
			_Reg[_Cmd.Dest] = _Reg[_Cmd.Src1];
			break;
		case CCommand::MOV_RV:         //mov reg, val
			_Reg[_Cmd.Dest] = _Cmd.Src1;
			break;
		case CCommand::MOV_RM:         //mov reg, mem
			_Reg[_Cmd.Dest] = _Mem[_Cmd.Src1];
			break;
		case CCommand::MOV_MR:         //mov mem, reg
			_Mem[_Cmd.Dest] = _Reg[_Cmd.Src1];
			break;
		case CCommand::MOV_MV:         //mov mem, val
			_Mem[_Cmd.Dest] = _Cmd.Src1;
			break;
		case CCommand::EXIT_R:         //exit none, reg
			printf("result = %i\n", _Reg[_Cmd.Src1]);
			break;
		case CCommand::EXIT_V:         //exit none, val
			printf("result = %i\n", _Cmd.Src1);
			break;
		case CCommand::EXIT_M:         //exit none, mem
			printf("result = %i\n", _Mem[_Cmd.Src1]);
			break;
		case CCommand::OPCODE_UNKNOWN: //error command
		default:
			sprintf(ErrMsg, "Error opcode");
			throw ErrMsg;
	}
}

void CInterpreter::Execute(CProgram* _Prg) const
{
	int* Reg = new int[_Prg->GetCntRegister()];
	int* Mem = new int[_Prg->GetCntVariable()];
	try
	{
		for(unsigned int i=0; i!=_Prg->GetCntCommand(); ++i)
			ExecCommand(_Prg->GetCmd(i), Reg, Mem);
	}
	catch(const char* _ErrMsg)
	{
		delete [] Reg;
		delete [] Mem;
		char ErrMsg[512];
		sprintf(ErrMsg, "Exec error: %s\n", _ErrMsg);
		throw ErrMsg;
	}
	for (unsigned int i=0; i!=_Prg->GetCntRegister(); ++i)
		printf("r%.2i=%i\n", i, Reg[i]);
	for (unsigned int i=0; i!=_Prg->GetCntVariable(); ++i)
		printf("[%i]=%i\n", i, Mem[i]);
	delete [] Reg;
	delete [] Mem;
}