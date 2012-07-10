#include <Command.h>
#include <stdio.h>

CCommand::CCommand(void) : Cmd(OPCODE_UNKNOWN), Dest(0), Src1(0), Src2(0)
{

}

CCommand::CCommand(OPCODE _Cmd, t_arg _Dest, t_arg _Src1, t_arg _Src2) : Cmd(_Cmd), Dest(_Dest), Src1(_Src1), Src2(_Src2)
{

}

CCommand::~CCommand(void)
{

}

void CCommand::Print(void) const
{
    switch(Cmd)
    {
        case MUL_RRR:
            printf("mul  r%.2i, r%.2i, r%.2i", Dest, Src1, Src2);
            break;
        case MUL_RRV:
            printf("mul  r%.2i, r%.2i, %i", Dest, Src1, Src2);
            break;
        case MUL_RVR:
            printf("mul  r%.2i, %i, r%.2i", Dest, Src1, Src2);
            break;
        case MUL_RVV:
            printf("mul  r%.2i, %i, %i", Dest, Src1, Src2);
            break;
        case DIV_RRR:
            printf("div  r%.2i, r%.2i, r%.2i", Dest, Src1, Src2);
            break;
        case DIV_RRV:
            printf("div  r%.2i, r%.2i, %i", Dest, Src1, Src2);
            break;
        case DIV_RVR:
            printf("div  r%.2i, %i, r%.2i", Dest, Src1, Src2);
            break;
        case DIV_RVV:
            printf("div  r%.2i, %i, %i", Dest, Src1, Src2);
            break;
        case ADD_RRR:
            printf("add  r%.2i, r%.2i, r%.2i", Dest, Src1, Src2);
            break;
        case ADD_RRV:
            printf("add  r%.2i, r%.2i, %i", Dest, Src1, Src2);
            break;
        case ADD_RVR:
            printf("add  r%.2i, %i, r%.2i", Dest, Src1, Src2);
            break;
        case ADD_RVV:
            printf("add  r%.2i, %i, %i", Dest, Src1, Src2);
            break;
        case SUB_RRR:
            printf("sub  r%.2i, r%.2i, r%.2i", Dest, Src1, Src2);
            break;
        case SUB_RRV:
            printf("sub  r%.2i, r%.2i, %i", Dest, Src1, Src2);
            break;
        case SUB_RVR:
            printf("sub  r%.2i, %i, r%.2i", Dest, Src1, Src2);
            break;
        case SUB_RVV:
            printf("sub  r%.2i, %i, %i", Dest, Src1, Src2);
            break;
        case MOV_RR:
            printf("mov  r%.2i, r%.2i", Dest, Src1);
            break;
        case MOV_RV:
            printf("mov  r%.2i, %i", Dest, Src1);
            break;
        case MOV_RM:
            printf("mov  r%.2i, [%i]", Dest, Src1);
            break;
        case MOV_MR:
            printf("mov  [%i], r%.2i", Dest, Src1);
            break;
        case MOV_MV:
            printf("mov  [%i], %i", Dest, Src1);
            break;
        case EXIT_R:
            printf("exit r%.2i", Src1);
            break;
        case EXIT_V:
            printf("exit %i", Src1);
            break;
        case EXIT_M:
            printf("exit [%i]", Src1);
            break;
        case OPCODE_UNKNOWN:
        default:
            printf("error");
            break;
    }
    printf("\n");
}