#include <SimpleLLexer.h>
#include <Compiler.h>

CCompiler::CCompiler(void)
{

}

CCompiler::~CCompiler(void)
{

}

static unsigned int GerVariable(CProgram* _Prg, pANTLR3_BASE_TREE _Tree)
{
	if(_Tree->getType(_Tree) != IDENT)
	{
		char ErrMsg[512];
		sprintf(ErrMsg, "Error tree-type for variable\n");
		throw ErrMsg;
	}

	const char* Name = (const char*)_Tree->getText(_Tree)->chars;
	return _Prg->GetVariableIndex(Name);
}

static int GetInt(pANTLR3_BASE_TREE _Tree)
{
	return atoi((const char*)_Tree->getText(_Tree)->chars);
}

static CCommand ParseTree(CProgram* _Prg, pANTLR3_BASE_TREE _BaseTree, ANTLR3_UINT32 _Ind)
{
	pANTLR3_BASE_TREE Tree = (pANTLR3_BASE_TREE)_BaseTree->getChild(_BaseTree, _Ind);

	CCommand Cmd;
	CCommand::t_arg Dest, Src1, Src2;
	char ErrMsg[512];
	
	switch(Tree->getType(Tree))
	{
		case ASSIGN_VAR:
			Dest = GerVariable(_Prg, (pANTLR3_BASE_TREE)Tree->getChild(Tree, 0));
			Src1 = ParseTree(_Prg, Tree, 1).Dest;
			Cmd  = CCommand(CCommand::MOV_MR, Dest, Src1, 0);
			break;
		case STAR:
			Src1 = ParseTree(_Prg, Tree, 0).Dest;
			Src2 = ParseTree(_Prg, Tree, 1).Dest;
			Dest = _Prg->GetRegisterIndex();
			Cmd  = CCommand(CCommand::MUL_RRR, Dest, Src1, Src2);
			break;
		case SLASH:
			Src1 = ParseTree(_Prg, Tree, 0).Dest;
			Src2 = ParseTree(_Prg, Tree, 1).Dest;
			Dest = _Prg->GetRegisterIndex();
			Cmd  = CCommand(CCommand::DIV_RRR, Dest, Src1, Src2);
			break;
		case PLUS:
			Src1 = ParseTree(_Prg, Tree, 0).Dest;
			if(Tree->getChildCount(Tree) == 1)
			{
				Cmd  = CCommand(CCommand::MOV_RR, Src1, Src1, 0);
			}
			else
			{
				Src2 = ParseTree(_Prg, Tree, 1).Dest;
				Dest = _Prg->GetRegisterIndex();
				Cmd  = CCommand(CCommand::ADD_RRR, Dest, Src1, Src2);
			}
			break;
		case MINUS:
			Src1 = ParseTree(_Prg, Tree, 0).Dest;
			if(Tree->getChildCount(Tree) == 1)
			{
				Cmd  = CCommand(CCommand::SUB_RVR, Src1, 0, Src1);
			}
			else
			{
				Src2 = ParseTree(_Prg, Tree, 1).Dest;
				Dest = _Prg->GetRegisterIndex();
				Cmd  = CCommand(CCommand::SUB_RRR, Dest, Src1, Src2);
			}
			break;
		case INT:
			Dest = _Prg->GetRegisterIndex();
			Src1 = GetInt(Tree);
			Cmd  = CCommand(CCommand::MOV_RV, Dest, Src1, 0);
			break;
		case IDENT:
			Dest = _Prg->GetRegisterIndex();
			Src1 = GerVariable(_Prg, Tree);
			Cmd  = CCommand(CCommand::MOV_RM, Dest, Src1, 0);
			break;
		case FUNC_CALL:
			Src1 = ParseTree(_Prg, Tree, 1).Dest;
			Cmd  = CCommand(CCommand::EXIT_R, 0, Src1, 0);
			break;
		default:
			sprintf(ErrMsg, "Error type in ParseTree\n");
			throw ErrMsg;
	}

	_Prg->AddCmd(Cmd);
	return Cmd;
}

CProgram CCompiler::Compile(pANTLR3_BASE_TREE _ASTTree) const
{
	if(_ASTTree == NULL)
	{
		char ErrMsg[512];
		sprintf(ErrMsg, "AST tree is NULL\n");
		throw ErrMsg;
	}

	CProgram Prg;
	for(ANTLR3_UINT32 i=0; i!=_ASTTree->getChildCount(_ASTTree); ++i)
		ParseTree(&Prg, _ASTTree, i);
	return Prg;
}