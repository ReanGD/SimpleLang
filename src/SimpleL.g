grammar SimpleL;

options 
{
    output        = AST;
    language      = C;
    ASTLabelType  = pANTLR3_BASE_TREE;
}

tokens 
{
    FUNC_CALL;
    ASSIGN_VAR;
}

/**********************************************
    Program
**********************************************/
program
    : (statement SEMI!)*
    ;
 
/**********************************************
    Statements
**********************************************/
statement
    : assignmentStatement
    | callStatement
    ;

assignmentStatement
    : identifier ASSIGN expression -> ^(ASSIGN_VAR identifier expression)
    ;

callStatement
    : KW_EXIT identifier -> ^(FUNC_CALL KW_EXIT identifier)
    ;

/**********************************************
    Expression
**********************************************/
expression
    : term
      ( (PLUS^ | MINUS^ ) term )*
    ;

term
    : signedFactor
      ( (STAR^ | SLASH^ ) signedFactor )*
    ;

signedFactor
    : (PLUS^|MINUS^)? factor
    ;

factor
    : variable
    | LPAREN! expression RPAREN!
    ;

variable
    : unsignedInteger
    | identifier
    ;


/**********************************************
    identifier
**********************************************/
identifier
    : ident
    ;

ident
    : IDENT
    ;

/**********************************************
    Datetypes impl
**********************************************/
unsignedInteger
    : INT
    ;

/**********************************************
    Keywords
**********************************************/
KW_EXIT : 'EXIT' ;

/**********************************************
    Operators
**********************************************/
EQUAL     : '==' ;
ASSIGN    : '='  ;
NOT_EQUAL : '!=' ;
ELT       : '<'  ;
ELE       : '<=' ;
EGE       : '>=' ;
EGT       : '>'  ;
PLUS      : '+'  ;
MINUS     : '-'  ;
STAR      : '*'  ;
SLASH     : '/'  ;
DOT       : '.'  ;
COLON     : ':'  ;
LPAREN    : '('  ;
RPAREN    : ')'  ;
LBRACK    : '['  ;
RBRACK    : ']'  ;
SEMI      : ';'  ;

/**********************************************
    Datetypes
**********************************************/
fragment DIGIT
    : '0'..'9'
    ;

fragment LETTER
    : 'A'..'Z'
    ;

IDENT
    : (LETTER|'_') (LETTER|DIGIT|'_')*
    ;

INT
    : DIGIT+
    ;

/**********************************************
    Hiddens
**********************************************/
WS
    :(' ' | '\t' | '\r' | '\n')+ { $channel=HIDDEN; }
    ;

COMMENT
    : '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    ;