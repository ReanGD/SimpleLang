#ifndef _Command_H
#define _Command_H

class CCommand
{
public:
	enum OPCODE
	{
		MUL_RRR, //mul reg, reg, reg
		MUL_RRV, //mul reg, reg, val
		MUL_RVR, //mul reg, val, reg
		MUL_RVV, //mul reg, val, val
		DIV_RRR, //div reg, reg, reg
		DIV_RRV, //div reg, reg, val
		DIV_RVR, //div reg, val, reg
		DIV_RVV, //div reg, val, val
		ADD_RRR, //add reg, reg, reg
		ADD_RRV, //add reg, reg, val
		ADD_RVR, //add reg, val, reg
		ADD_RVV, //add reg, val, val
		SUB_RRR, //add reg, reg, reg
		SUB_RRV, //add reg, reg, val
		SUB_RVR, //add reg, val, reg
		SUB_RVV, //add reg, val, val
		MOV_RR,  //mov reg, reg
		MOV_RV,  //mov reg, val
		MOV_RM,  //mov reg, mem
		MOV_MR,  //mov mem, reg
		MOV_MV,  //mov mem, val
		EXIT_R,  //exit none, reg
		EXIT_V,  //exit none, val
		EXIT_M,  //exit none, mem
		OPCODE_UNKNOWN  //error command
	};

	typedef int t_arg;
public:
	OPCODE  Cmd;
	t_arg   Dest;
	t_arg   Src1;
	t_arg   Src2;
public:
	CCommand(void);
	CCommand(OPCODE _Cmd, t_arg _Dest, t_arg _Src1, t_arg _Src2);
	~CCommand(void);
public:
	void Print(void) const;
};

#endif