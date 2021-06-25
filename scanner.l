%{ /* -*- C++ -*- */
# include <string>
# include <climits>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
# include "driver.hh"
# include "parser.hh"
# include "helpers/debug.hh"
%}

%option noyywrap nounput noinput batch

%{
  yy::parser::symbol_type make_INTCONST (const std::string &s, std::vector<Constant>& constants, const yy::parser::location_type& loc);
  yy::parser::symbol_type make_CHARCONST (const std::string &s, std::vector<Constant>& constants, const yy::parser::location_type& loc);
  void token_to_file (std::string s);
  void token_to_file (std::string s, std::string text);
  bool cleared = false;
%}


id    [a-zA-Z_][a-zA-Z_0-9]*
int   [0-9]+
char  "'"."'"
blank [ \t\r]
comment  (($\*([^*]|[\r\n]|(\*+([^*$]|[\r\n])))*\*+$)|($$.*))

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}



%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = drv.location;

  // Code run each time yylex is called.
  loc.step ();

  std::vector<Constant>& constants = drv.constants;


%}

{comment}     token_to_file("COMMENT"); loc.lines (std::count(yytext, yytext+yyleng, '\n')); loc.step ();
{blank}+      loc.step ();
\n+           loc.lines (yyleng); loc.step ();

"if"          token_to_file("IF"); return yy::parser::make_IF                (loc);
"else"        token_to_file("ELSE"); return yy::parser::make_ELSE              (loc);
"elseif"      token_to_file("ELSEIF"); return yy::parser::make_ELSE_IF           (loc);
"while"       token_to_file("WHILE"); return yy::parser::make_WHILE             (loc);
"continue"    token_to_file("CONTINUE"); return yy::parser::make_CONTINUE          (loc);
"break"       token_to_file("BREAK"); return yy::parser::make_BREAK             (loc);
"for"         token_to_file("FOR"); return yy::parser::make_FOR               (loc);
"return"      token_to_file("RETURN"); return yy::parser::make_RETURN            (loc);
"main"        token_to_file("MAIN"); return yy::parser::make_MAIN              (loc);
"switch"      token_to_file("SWITCH"); return yy::parser::make_SWITCH             (loc);
"case"        token_to_file("CASE"); return yy::parser::make_CASE              (loc);
"default"     token_to_file("DEFAULT"); return yy::parser::make_DEFAULT              (loc);


"int"         token_to_file("INT", std::string(yytext)); return yy::parser::make_INT               (loc);
"char"        token_to_file("CHAR"); return yy::parser::make_CHAR              (loc);
"void"        token_to_file("VOID"); return yy::parser::make_VOID              (loc);


"="           token_to_file("ASSIGNMENT"); return yy::parser::make_ASSIGN            (loc);
"-"           token_to_file("MINUS"); return yy::parser::make_MINUS             (loc);
"+"           token_to_file("PLUS"); return yy::parser::make_PLUS              (loc);
"*"           token_to_file("MULTIPLICATION"); return yy::parser::make_MULT              (loc);
"/"           token_to_file("DIVISION"); return yy::parser::make_DIV               (loc);
"||"          token_to_file("LOGICALOR"); return yy::parser::make_LOR               (loc);
"&&"          token_to_file("LOGICALAND"); return yy::parser::make_LAND              (loc);
"&"           token_to_file("AND"); return yy::parser::make_AND               (loc);
"|"           token_to_file("OR"); return yy::parser::make_OR                (loc);
"^"           token_to_file("XOR"); return yy::parser::make_XOR               (loc);
"!"           token_to_file("NOT"); return yy::parser::make_NOT               (loc);
"<"           token_to_file("LESSTHAN"); return yy::parser::make_LESSTHAN          (loc);
"<="          token_to_file("LESSTHANEQUAL"); return yy::parser::make_LESSTHANEQUAL     (loc);
"=="          token_to_file("EQUAL"); return yy::parser::make_EQUAL             (loc);
"!="          token_to_file("NOTEQUAL"); return yy::parser::make_NOTEQUAL          (loc);
">"           token_to_file("GREATERTHAN"); return yy::parser::make_GREATERTHAN       (loc);
">="          token_to_file("GREATERTHANEQUAL"); return yy::parser::make_GREATERTHANEQUAL  (loc);


"("           token_to_file("LEFTPARENTHESIS"); return yy::parser::make_LPAREN            (loc);
")"           token_to_file("RIGHTPARENTHESIS"); return yy::parser::make_RPAREN            (loc);
"["           token_to_file("LEFTBRACKET"); return yy::parser::make_LBRACK            (loc);
"]"           token_to_file("RIGHTBRACKET"); return yy::parser::make_RBRACK            (loc);
"{"           token_to_file("LEFTCURLYBRACKET"); return yy::parser::make_LCBRACK           (loc);
"}"           token_to_file("RIGHTCURLYBRACKET"); return yy::parser::make_RCBRACK           (loc);
","           token_to_file("COMMA"); return yy::parser::make_COMMA             (loc);
"."           token_to_file("DOT"); return yy::parser::make_DOT               (loc);


{int}         token_to_file("INT", std::string(yytext)); return make_INTCONST(yytext, constants, loc);
{char}        token_to_file("CHAR"); return make_CHARCONST(yytext, constants, loc);
{id}          token_to_file("ID"); return yy::parser::make_ID(yytext, loc);



.             {
                throw yy::parser::syntax_error (loc, "invalid character: " + std::string(yytext));
              }

<<EOF>>     return yy::parser::make_YYEOF(loc);

%%


yy::parser::symbol_type
make_INTCONST (const std::string &s, std::vector<Constant>& constants, const yy::parser::location_type& loc)
{
  errno = 0;
  long number = strtol (s.c_str(), NULL, 10);
  if (! (INT_MIN <= number && number <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "integer is out of range: " + s);

  int idx = constants.size();
  Constant c;
  c.value = number;
  c.type = Constant::Type::INT;
  constants.push_back(c);
  return yy::parser::make_INTCONST (idx, loc);
}

yy::parser::symbol_type
make_CHARCONST (const std::string &s, std::vector<Constant>& constants, const yy::parser::location_type& loc)
{
  char ch = s[1];
  int idx = constants.size();
  Constant c;
  c.value = ch;
  c.type = Constant::Type::CHAR;
  constants.push_back(c);
  return yy::parser::make_CHARCONST (idx, loc);
}

void token_to_file (std::string s){
  ofstream tokenFile;
  if (!cleared) {tokenFile.open("TOKEN.txt", ios::trunc); cleared = true;}
  else tokenFile.open("TOKEN.txt", ios::app);
  tokenFile << "TOKEN_" << s << "\n";
  tokenFile.close();
}

void token_to_file (std::string s, std::string text){
  ofstream tokenFile;
  if (!cleared) {tokenFile.open("TOKEN.txt", ios::trunc); cleared = true;}
  else tokenFile.open("TOKEN.txt", ios::app);
  tokenFile << "TOKEN_" << s << "\t= " << text << "\n";
  tokenFile.close();
}

void
driver::scan_begin ()
{
  yy_flex_debug = false;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      std::cerr << "cannot open " << file << ": " << strerror (errno) << '\n';
      exit (EXIT_FAILURE);
    }
}

void
driver::scan_end ()
{
  fclose (yyin);
}