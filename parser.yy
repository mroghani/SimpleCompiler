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
# include "helpers/debug.hh"
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
  SWITCH            "switch"
  CASE              "case"
  DEFAULT           "default"
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
%nterm <std::vector<Var>>                 params paramList;
%nterm <Var>                              paramItem;

%nterm <int>                unaryop sumop mulop;
%nterm <std::string>        relop;

%nterm <Constant>       constant;

%nterm <Node>           immutable mutable exp call unaryExp factor;
%nterm <Node>           simpleExp andExp unaryRelExp relExp sumExp mulExp;
%nterm <Node>           programm declLists decl funcDecl expStmt;
%nterm <Node>           returnStmt;
%nterm <Node>           stmt stmtList;
%nterm <Node>           selectStmt elseifclause;
%nterm <Node>           varDecl forStmt whileStmt iterStmt breakStmt continueStmt;

%nterm <std::vector<Node>> argList args;





// %nterm <Node>           cases;

// grammar
%%
%start unit;

unit: programm YYEOF                      { drv.make_output($1); std::cout << "goodbye" << std::endl; }


programm: declLists                       { $$ = $1; }
        ;

declLists: %empty                         { $$ = Node(); }
         | declLists decl                 { $$ = helpers::merge_nodes($1, $2); }
         ;

decl: varDecl "."                         { $$ = Node(); }
    | funcDecl                            { $$ = $1; }
    ;

varDecl: varType ID                       { auto var = drv.make_variable($2, @2, $1, 1, 0); $$ = helpers::var_init(var, false);}
       | varType ID "=" constant          { auto var = drv.make_variable($2, @2, $1, 1, $4.value); $$ = helpers::var_init(var, true); }
       | varType ID "=" "-" constant      { auto var = drv.make_variable($2, @2, $1, 1, -$5.value); $$ = helpers::var_init(var, true);}
       | varType ID "[" INTCONST "]"      { auto var = drv.make_variable($2, @2, $1, $4, 0); $$ = helpers::var_init(var, false);}
       ;

varType: INT   { $$ = 1; }
       | CHAR  { $$ = 2; }
       ;

funcDecl: varType ID               { drv.push_scope(); drv.make_func($2, $1); }
          "(" params ")"           { drv.add_args_to_func($5, @5); }
          "<" stmtList ">"         { $$ = helpers::create_function(drv.Functions[$2], $9); drv.pop_scope(); }

        | VOID ID                  { drv.push_scope(); drv.make_func($2, 3); }
         "(" params ")"            { drv.add_args_to_func($5, @5); }
         "<" stmtList ">"          { $$ = helpers::create_function(drv.Functions[$2], $9); drv.pop_scope(); }

        | INT MAIN                 { drv.push_scope(); drv.make_func("main", 1);  drv.is_in_main = true; }
          "("                      <std::vector<Var>>{$$ = std::vector<Var>();} ")" 
          "<" stmtList ">"         { $$ = helpers::create_function(drv.Functions["main"], $8); drv.pop_scope();  drv.is_in_main = false;  }
        ;

params: paramList                         { $$ = $1; }
      | %empty                            { $$ = std::vector<Var>(); }
      ;

paramList: paramList "," paramItem        { $1.push_back($3); $$ = $1; }
         | paramItem                      { $$ = std::vector<Var>(1, $1); }
         ;

paramItem: varType ID                     { $$ = drv.make_variable($2, @2, $1, 1, 0); }
         ;

stmtList: varDecl "." stmtList     { $$ = helpers::merge_nodes($1, $3); ; }
        | stmt  stmtList           { $$ = helpers::merge_nodes($1, $2); }
        | %empty                   { $$ = Node(); }
        ;

stmt: expStmt                      { $$ = $1; }
    | returnStmt                   { $$ = $1; }
    | selectStmt                   { $$ = $1; }
    | iterStmt                     { $$ = $1; }
    | breakStmt                    { $$ = $1; }
    | continueStmt                 { $$ = $1; }
    ;

    
selectStmt: IF "(" simpleExp ")" <std::string>{ $$ = drv.get_label(); } "<" stmtList ">" elseifclause        { $$ = helpers::make_if_stmt(drv, $3, $7, $9, $5, true); }
          | SWITCH "(" factor ")" "<" cases ">"                 { $$ = Node(); } // TODO
          ;

elseifclause: ELSE_IF "(" simpleExp ")" <std::string>{ $$ = $<std::string>-3; } "<" stmtList ">" elseifclause  { $$ = helpers::make_if_stmt(drv, $3, $7, $9, $5, false); }
            | ELSE "<" stmtList ">"                             { $$ = $3; }
            | %empty                                            { $$ = Node(); }
            ;
       
cases: cases case
     | %empty
     ;

case: CASE simpleExp ":" stmtList
    | DEFAULT ":" stmtList
    ;

iterStmt: whileStmt                { $$ = $1; }
        | forStmt                  { $$ = $1; }
        ;

whileStmt: WHILE { drv.push_loop(); } "(" simpleExp ")" "<" stmtList ">"                   { $$ = helpers::make_while(drv, $4, $7); drv.pop_loop(); }
         ;

forStmt: FOR  { drv.push_loop(); } "(" varDecl "." simpleExp "." exp ")" "<" stmtList ">"  { $$ = helpers::make_for(drv, $4, $6, $8, $11); drv.pop_loop(); }
       ;

breakStmt: BREAK "."                      { $$ = helpers::make_break(drv, @1); }
         ;

continueStmt: CONTINUE "."                { $$ = helpers::make_continue(drv, @1); }
            ;

returnStmt: RETURN "."                    { $$ = helpers::return_stmt(drv, @1, nullptr); }
          | RETURN simpleExp "."          { $$ = helpers::return_stmt(drv, @1, &$2); }
          ;



expStmt: exp "."                   { $$ = $1; }
       ;

exp: simpleExp                     { $$ = $1; }
   | mutable "=" simpleExp         { $$ = helpers::assign($1, $3); } // TODO assignment chain
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

factor: immutable           { ddd&&printf("[parser]=> immutable found\n"); $$ = $1;}
      | mutable             { ddd&&printf("[parser]=> mutable found\n"); $$ = helpers::load_mutable_value($1); }
      ;

mutable: ID                 { $$ = helpers::load_mutable(drv, $1, @1, nullptr); }
       | ID "[" exp "]"     { $$ = helpers::load_mutable(drv, $1, @1, &$3); }
       ;

immutable: "(" exp ")"      { $$ = $2; }
         | call             {
                              if ($1.type == Node::Type::VOID) {
                                     error(@1, "void type can not be used as immutable.");
                              }
                              $$ = $1;
                            }
         | constant         { $$ = helpers::load_constant($1); }
         ;

call: ID "(" args ")"       { $$ = helpers::call_function(drv, $1, @1, $3); $$.type = (Node::Type)drv.Functions[$1].type; }
    ;

args: %empty                { $$ = std::vector<Node>(); }
    | argList               { $$ = $1; }
    ;

argList: argList "," exp    { $1.push_back($3); $$ = $1;}
       | exp                { $$ = std::vector<Node>(); $$.push_back($1); }
       ;

constant: INTCONST          { $$ = drv.constants[$1]; }
        | CHARCONST         { $$ = drv.constants[$1]; }
        ;


%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}