grammar Calc;

prog
    : expr EOF
    ;

expr
    : expr op=('+'|'-') term       # AddSubExpr
    | term                          # ToTerm
    ;

term
    : term op=('*'|'/') power       # MulDivExpr
    | power                         # ToPower
    ;

power
    : power '^' factor              # InfixPowExpr
    | factor                        # ToFactor
    ;

factor
    : '-' factor                    # UnaryMinusExpr
    | '+' factor                    # UnaryPlusExpr
    | func '(' expr ')'             # FunctionCallExpr
    | NUMBER                        # NumberExpr
    | IDX                           # IdExpr
    | '(' expr ')'                  # ParenExpr
    ;

func
    : 'sin'
    | 'cos'
    | 'tan'
    | 'arctan'
    | 'arcsin'
    | 'arccos'
    | 'ln'
    | 'log'
    | 'exp'
    | 'sqrt'
    ;

NUMBER : [0-9]+ ('.' [0-9]+)?;
IDX    : 'x';
WS     : [ \t\r\n]+ -> skip;