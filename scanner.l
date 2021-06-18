%{ /* -*- C++ -*- */
# include <string>
# include <climits>
# include "driver.hh"
# include "parser.hh"
%}

%option noyywrap nounput noinput batch

%{
  yy::parser::symbol_type make_NUMBER (const std::string &s, std::vector<Constant>& constants, const yy::parser::location_type& loc);
  yy::parser::symbol_type make_CHARCONST (const std::string &s, std::vector<Constant>& constants, const yy::parser::location_type& loc);
%}


id    [a-zA-Z_][a-zA-Z_0-9]*
int   [0-9]+
char  "'"."'"
blank [ \t\r]


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

{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();

"if"          return yy::parser::make_IF                (loc);
"else"        return yy::parser::make_ELSE              (loc);
"elseif"      return yy::parser::make_ELSE_IF           (loc);
"while"       return yy::parser::make_WHILE             (loc);
"continue"    return yy::parser::make_CONTINUE          (loc);
"break"       return yy::parser::make_BREAK             (loc);
"for"         return yy::parser::make_FOR               (loc);
"return"      return yy::parser::make_RETURN            (loc);
"main"        return yy::parser::make_MAIN              (loc);

"int"        return yy::parser::make_INT                (loc);
"char"       return yy::parser::make_CHAR               (loc);
"void"       return yy::parser::make_VOID               (loc);


"="           return yy::parser::make_ASSIGN            (loc);
"-"           return yy::parser::make_MINUS             (loc);
"+"           return yy::parser::make_PLUS              (loc);
"*"           return yy::parser::make_STAR              (loc);
"/"           return yy::parser::make_SLASH             (loc);
"||"          return yy::parser::make_LOR               (loc);
"&&"          return yy::parser::make_LAND              (loc);
"&"           return yy::parser::make_AND               (loc);
"|"           return yy::parser::make_OR                (loc);
"^"           return yy::parser::make_XOR               (loc);
"!"           return yy::parser::make_NOT               (loc);
"<"           return yy::parser::make_LESSTHAN          (loc);
"<="          return yy::parser::make_LESSTHANEQUAL     (loc);
"=="          return yy::parser::make_EQUAL             (loc);
"!="          return yy::parser::make_NOTEQUAL          (loc);
">"           return yy::parser::make_GREATERTHAN       (loc);
">="          return yy::parser::make_GREATERTHANEQUAL  (loc);


"("           return yy::parser::make_LPAREN            (loc);
")"           return yy::parser::make_RPAREN            (loc);
"["           return yy::parser::make_LBRACK            (loc);
"]"           return yy::parser::make_RBRACK            (loc);
"{"           return yy::parser::make_LCBRACK           (loc);
"}"           return yy::parser::make_RCBRACK           (loc);
","           return yy::parser::make_COMMA             (loc);
"."           return yy::parser::make_DOT               (loc);


{int}         return make_NUMBER(yytext, constants, loc);
{char}        return make_CHARCONST(yytext, constants, loc);
{id}          return yy::parser::make_ID(yytext, loc);



.             {
                throw yy::parser::syntax_error (loc, "invalid character: " + std::string(yytext));
              }

<<EOF>>     return yy::parser::make_YYEOF(loc);

%%


yy::parser::symbol_type
make_NUMBER (const std::string &s, std::vector<Constant>& constants, const yy::parser::location_type& loc)
{
  errno = 0;
  long n = strtol (s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "integer is out of range: " + s);

  int idx = constants.size();
  Constant c;
  c.value = n;
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