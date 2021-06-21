%skeleton "lalr1.cc" // -*- C++ -*-
%require "3.7.6"

%defines
%locations

%define parse.trace
%define parse.error detailed
%define parse.lac full

%define api.token.raw
%define api.token.constructor
%define api.value.type variant
%define parse.assert


%code requires {
#include <string>
#include "types.hh"
class driver;
}

// The parsing context.
%param { driver& drv }

%code {
# include "driver.hh"
}


%define api.token.prefix {TOK_}
// tokens
%token
  IF                "if"
  ELSE              "else"
  ELSE_IF           "elseif"
  WHILE             "while"
  CONTINUE          "continue"
  BREAK             "break"
  FOR               "for"
  RETURN            "return"
  MAIN              "main"
;

%token
  ASSIGN            "="
  MINUS             "-"
  PLUS              "+"
  MULT              "*"
  DIV               "/"
  LOR               "||"
  LAND              "&&"
  AND               "&"
  OR                "|"
  XOR               "^"
  NOT               "!"
  LESSTHAN          "<"
  LESSTHANEQUAL     "<="
  EQUAL             "=="
  NOTEQUAL          "!="
  GREATERTHAN       ">"
  GREATERTHANEQUAL  ">="
;

%token
  LPAREN            "("
  RPAREN            ")"
  LBRACK            "["
  RBRACK            "]"
  LCBRACK           "{"
  RCBRACK           "}"
  COMMA             ","
  DOT               "."
;


%token
  INT              "int"
  CHAR             "char"
  VOID             "void"
;


%token <int>            INTCONST         "const int";
%token <int>            CHARCONST        "const char";
%token <std::string>    ID               "identifier";

%nterm <int>                              varType;
%nterm <std::vector<Var>>          params paramList;
%nterm <Var>                              paramItem;

%nterm <int>                unaryop sumop mulop;
%nterm <std::string>        relop;


%nterm <Node>           constant immutable mutable exp call unaryExp factor;
%nterm <Node>           simpleExp andExp unaryRelExp relExp sumExp mulExp;
%nterm <Node>           programm declLists decl funcDecl expStmt;

// grammar
%%
%start unit;

unit: programm YYEOF                      { drv.make_output($1); std::cout << "goodbye" << std::endl;  /* TODO: Output code. */}


programm: declLists                       { $$ = $1; }
        ;

declLists: %empty                         { $$ = Node(); }
         | declLists decl                 { $$ = helpers::merge_nodes($1, $2); }
         ;

decl: varDecl "."                         { $$ = Node(); }
    | funcDecl                            { $$ = Node();  /* TODO */}
    ;

varDecl: varType ID                       { drv.make_variable($2, @2, $1, 1, 0); }
       | varType ID "=" constant          { drv.make_variable($2, @2, $1, 1, $4.value); }
       | varType ID "=" "-" constant      { drv.make_variable($2, @2, $1, 1, -$5.value); }
       | varType ID "[" INTCONST "]"      { drv.make_variable($2, @2, $1, $4, 0); }    
       ;

varType: INT   { $$ = 1; }                
       | CHAR  { $$ = 2; }
       ;

funcDecl: varType ID { drv.push_scope(); }
          "(" params ")" "<" stmtList ">"  { drv.pop_scope(); }
        | VOID ID { drv.push_scope(); } "(" params ")" "<" stmtList ">" { drv.pop_scope(); }
        | INT MAIN { drv.push_scope(); } "(" <std::vector<Var>>{$$ = std::vector<Var>();} ")" "<" stmtList ">" { drv.pop_scope(); }
        ;

params: paramList                         { $$ = $1; }
      | %empty                            { $$ = std::vector<Var>(); }
      ;

paramList: paramList "," paramItem        { $1.push_back($3); $$ = $1; }
         | paramItem                      { $$ = std::vector<Var>(1, $1); }   
         ;

paramItem: varType ID                     { $$ = drv.make_variable($2, @2, $1, 1, 0); }
         ;

stmtList: varDecl "." stmtList
        | stmt  stmtList
        | %empty
        ;

stmt: expStmt
    | selectStmt
    | iterStmt
    | breakStmt
    | continueStmt
    | returnStmt
    ;

selectStmt: IF "(" exp ")" "<" stmtList ">";

iterStmt: whileStmt
        | forStmt
        ;

whileStmt: WHILE "(" exp ")" "<" stmtList ">"
         ;

forStmt: FOR "(" varDecl "." exp "." exp ")" "<" stmtList ">"
       ;

breakStmt: BREAK "."
         ;

continueStmt: CONTINUE "."
            ;

returnStmt: RETURN "."
          | RETURN exp "."
          ;



expStmt: exp "."                   { $$ = $1; }
       ;

exp: simpleExp                     { $$ = $1; }
   | mutable "=" simpleExp               { $$ = helpers::assign($1, $3); }
   ;

simpleExp: simpleExp "|" andExp    { $$ = helpers::binary_exp($1, "|", $3); }
         | andExp                  { $$ = $1; }
         ;

andExp: andExp "&" unaryRelExp     { $$ = helpers::binary_exp($1, "&", $3); }
      | unaryRelExp                { $$ = $1; }
      ;

unaryRelExp: "!" unaryRelExp       { $$ = helpers::unary_rel_exp($2); }
           | relExp                { $$ = $1; }
           ;

relExp: sumExp relop sumExp        { $$ = helpers::rel_exp($1, $2, $3); }
      | sumExp                     { $$ = $1; }
      ;
      
relop: "=="                        { $$ = "=="; }
     | "<="                        { $$ = "<="; }
     | ">="                        { $$ = ">="; }
     | "!="                        { $$ = "!="; }
     | "<"                         { $$ = "<"; }
     | ">"                         { $$ = ">"; }
     ;

sumExp: sumExp sumop mulExp        { $$ = helpers::sum_exp($1, $2, $3); }
      | mulExp                     { $$ = $1; }
      ;

sumop: "+"                         { $$ = 1; }
     | "-"                         { $$ = -1; }
     ;

mulExp: mulExp mulop unaryExp      { $$ = helpers::mul_exp($1, $2, $3);}
      | unaryExp                   { $$ = $1; }
      ;

mulop: "*"                         { $$ = 1; }
     | "/"                         { $$ = 2; }
     ;

unaryExp: unaryop unaryExp         { $$ = helpers::unary_exp($2, $1);}
        | factor                   { $$ = $1; }
        ;

unaryop: "+"                { $$ = 1; }
       | "-"                { $$ = -1; }
       ;

factor: immutable           { $$ = $1;} 
      | mutable             { $$ = helpers::extract_mutable($1); }
      ;

mutable: ID                 { $$ = helpers::make_mutable(drv, $1, @1, nullptr); }
       | ID "[" exp "]"     { $$ = helpers::make_mutable(drv, $1, @1, &$3); }
       ;

immutable: "(" exp ")"      { $$ = $2; }
         | call             { 
                              if ($1.type == Node::Type::VOID) {
                                     error(@1, "void type can not be used as immutable.");
                              }
                              $$ = $1; // TODO
                            }
         | constant         { $$ = $1; }
         ;

call: ID "(" args ")"       { $$ = helpers::make_mutable(drv, $1, @1, nullptr); // TODO: COMOLETE BULLSHIT
                            }
    ;

args: %empty
    | argList
    ;

argList: argList "," exp
       | exp
       ;

constant: INTCONST          { $$ = helpers::make_constant(drv.constants[$1]); }
        | CHARCONST         { $$ = helpers::make_constant(drv.constants[$1]); }
        ;


%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}