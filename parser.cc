// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hh"


// Unqualified %code blocks.
#line 26 "parser.yy"

# include "driver.hh"

#line 50 "parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 142 "parser.cc"

  /// Build a parser object.
  parser::parser (driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_programm: // programm
      case symbol_kind::S_declLists: // declLists
      case symbol_kind::S_decl: // decl
      case symbol_kind::S_varDecl: // varDecl
      case symbol_kind::S_funcDecl: // funcDecl
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_simpleExp: // simpleExp
      case symbol_kind::S_andExp: // andExp
      case symbol_kind::S_unaryRelExp: // unaryRelExp
      case symbol_kind::S_relExp: // relExp
      case symbol_kind::S_sumExp: // sumExp
      case symbol_kind::S_mulExp: // mulExp
      case symbol_kind::S_unaryExp: // unaryExp
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_mutable: // mutable
      case symbol_kind::S_immutable: // immutable
      case symbol_kind::S_call: // call
      case symbol_kind::S_constant: // constant
        value.YY_MOVE_OR_COPY< Node > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_paramItem: // paramItem
        value.YY_MOVE_OR_COPY< Var > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTCONST: // "int constant"
      case symbol_kind::S_CHARCONST: // "char constant"
      case symbol_kind::S_varType: // varType
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // "identifier"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_54_4: // @4
      case symbol_kind::S_params: // params
      case symbol_kind::S_paramList: // paramList
        value.YY_MOVE_OR_COPY< std::vector<Var> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_programm: // programm
      case symbol_kind::S_declLists: // declLists
      case symbol_kind::S_decl: // decl
      case symbol_kind::S_varDecl: // varDecl
      case symbol_kind::S_funcDecl: // funcDecl
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_simpleExp: // simpleExp
      case symbol_kind::S_andExp: // andExp
      case symbol_kind::S_unaryRelExp: // unaryRelExp
      case symbol_kind::S_relExp: // relExp
      case symbol_kind::S_sumExp: // sumExp
      case symbol_kind::S_mulExp: // mulExp
      case symbol_kind::S_unaryExp: // unaryExp
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_mutable: // mutable
      case symbol_kind::S_immutable: // immutable
      case symbol_kind::S_call: // call
      case symbol_kind::S_constant: // constant
        value.move< Node > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_paramItem: // paramItem
        value.move< Var > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTCONST: // "int constant"
      case symbol_kind::S_CHARCONST: // "char constant"
      case symbol_kind::S_varType: // varType
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // "identifier"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_54_4: // @4
      case symbol_kind::S_params: // params
      case symbol_kind::S_paramList: // paramList
        value.move< std::vector<Var> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_programm: // programm
      case symbol_kind::S_declLists: // declLists
      case symbol_kind::S_decl: // decl
      case symbol_kind::S_varDecl: // varDecl
      case symbol_kind::S_funcDecl: // funcDecl
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_simpleExp: // simpleExp
      case symbol_kind::S_andExp: // andExp
      case symbol_kind::S_unaryRelExp: // unaryRelExp
      case symbol_kind::S_relExp: // relExp
      case symbol_kind::S_sumExp: // sumExp
      case symbol_kind::S_mulExp: // mulExp
      case symbol_kind::S_unaryExp: // unaryExp
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_mutable: // mutable
      case symbol_kind::S_immutable: // immutable
      case symbol_kind::S_call: // call
      case symbol_kind::S_constant: // constant
        value.copy< Node > (that.value);
        break;

      case symbol_kind::S_paramItem: // paramItem
        value.copy< Var > (that.value);
        break;

      case symbol_kind::S_INTCONST: // "int constant"
      case symbol_kind::S_CHARCONST: // "char constant"
      case symbol_kind::S_varType: // varType
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_ID: // "identifier"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_54_4: // @4
      case symbol_kind::S_params: // params
      case symbol_kind::S_paramList: // paramList
        value.copy< std::vector<Var> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_programm: // programm
      case symbol_kind::S_declLists: // declLists
      case symbol_kind::S_decl: // decl
      case symbol_kind::S_varDecl: // varDecl
      case symbol_kind::S_funcDecl: // funcDecl
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_simpleExp: // simpleExp
      case symbol_kind::S_andExp: // andExp
      case symbol_kind::S_unaryRelExp: // unaryRelExp
      case symbol_kind::S_relExp: // relExp
      case symbol_kind::S_sumExp: // sumExp
      case symbol_kind::S_mulExp: // mulExp
      case symbol_kind::S_unaryExp: // unaryExp
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_mutable: // mutable
      case symbol_kind::S_immutable: // immutable
      case symbol_kind::S_call: // call
      case symbol_kind::S_constant: // constant
        value.move< Node > (that.value);
        break;

      case symbol_kind::S_paramItem: // paramItem
        value.move< Var > (that.value);
        break;

      case symbol_kind::S_INTCONST: // "int constant"
      case symbol_kind::S_CHARCONST: // "char constant"
      case symbol_kind::S_varType: // varType
        value.move< int > (that.value);
        break;

      case symbol_kind::S_ID: // "identifier"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_54_4: // @4
      case symbol_kind::S_params: // params
      case symbol_kind::S_paramList: // paramList
        value.move< std::vector<Var> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    /// Discard the LAC context in case there still is one left from a
    /// previous invocation.
    yy_lac_discard_ ("init");

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        if (!yy_lac_establish_ (yyla.kind ()))
           goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
           goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_programm: // programm
      case symbol_kind::S_declLists: // declLists
      case symbol_kind::S_decl: // decl
      case symbol_kind::S_varDecl: // varDecl
      case symbol_kind::S_funcDecl: // funcDecl
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_simpleExp: // simpleExp
      case symbol_kind::S_andExp: // andExp
      case symbol_kind::S_unaryRelExp: // unaryRelExp
      case symbol_kind::S_relExp: // relExp
      case symbol_kind::S_sumExp: // sumExp
      case symbol_kind::S_mulExp: // mulExp
      case symbol_kind::S_unaryExp: // unaryExp
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_mutable: // mutable
      case symbol_kind::S_immutable: // immutable
      case symbol_kind::S_call: // call
      case symbol_kind::S_constant: // constant
        yylhs.value.emplace< Node > ();
        break;

      case symbol_kind::S_paramItem: // paramItem
        yylhs.value.emplace< Var > ();
        break;

      case symbol_kind::S_INTCONST: // "int constant"
      case symbol_kind::S_CHARCONST: // "char constant"
      case symbol_kind::S_varType: // varType
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_ID: // "identifier"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_54_4: // @4
      case symbol_kind::S_params: // params
      case symbol_kind::S_paramList: // paramList
        yylhs.value.emplace< std::vector<Var> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // unit: programm $end
#line 103 "parser.yy"
                                          { std::cout << "goodbye" << std::endl; }
#line 752 "parser.cc"
    break;

  case 3: // programm: declLists
#line 106 "parser.yy"
                                          { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 758 "parser.cc"
    break;

  case 4: // declLists: %empty
#line 109 "parser.yy"
                                          { yylhs.value.as < Node > () = Node(); }
#line 764 "parser.cc"
    break;

  case 5: // declLists: declLists decl
#line 110 "parser.yy"
                                          { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 770 "parser.cc"
    break;

  case 6: // decl: varDecl "."
#line 113 "parser.yy"
                                          { yylhs.value.as < Node > () = yystack_[1].value.as < Node > (); }
#line 776 "parser.cc"
    break;

  case 7: // decl: funcDecl
#line 114 "parser.yy"
                                          { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 782 "parser.cc"
    break;

  case 8: // varDecl: varType "identifier"
#line 117 "parser.yy"
                                          { drv.make_variable(yystack_[0].value.as < std::string > (), yystack_[0].location, yystack_[1].value.as < int > (), 0, 0); yylhs.value.as < Node > () = Node(); }
#line 788 "parser.cc"
    break;

  case 9: // varDecl: varType "identifier" "=" constant
#line 118 "parser.yy"
                                          { drv.make_variable(yystack_[2].value.as < std::string > (), yystack_[2].location, yystack_[3].value.as < int > (), 0, yystack_[0].value.as < Node > ().value); yylhs.value.as < Node > () = Node(); }
#line 794 "parser.cc"
    break;

  case 10: // varDecl: varType "identifier" "[" "int constant" "]"
#line 119 "parser.yy"
                                          { drv.make_variable(yystack_[3].value.as < std::string > (), yystack_[3].location, yystack_[4].value.as < int > (), yystack_[1].value.as < int > (), 0); yylhs.value.as < Node > () = Node(); }
#line 800 "parser.cc"
    break;

  case 11: // varType: "int"
#line 122 "parser.yy"
               { yylhs.value.as < int > () = 1; }
#line 806 "parser.cc"
    break;

  case 12: // varType: "char"
#line 123 "parser.yy"
               { yylhs.value.as < int > () = 2; }
#line 812 "parser.cc"
    break;

  case 13: // $@1: %empty
#line 126 "parser.yy"
                     { drv.push_scope(); }
#line 818 "parser.cc"
    break;

  case 14: // funcDecl: varType "identifier" $@1 "(" params ")" "<" stmtList ">"
#line 127 "parser.yy"
                                           { drv.pop_scope(); }
#line 824 "parser.cc"
    break;

  case 15: // $@2: %empty
#line 128 "parser.yy"
                  { drv.push_scope(); }
#line 830 "parser.cc"
    break;

  case 16: // funcDecl: "void" "identifier" $@2 "(" params ")" "<" stmtList ">"
#line 128 "parser.yy"
                                                                        { drv.pop_scope(); }
#line 836 "parser.cc"
    break;

  case 17: // $@3: %empty
#line 129 "parser.yy"
                   { drv.push_scope(); }
#line 842 "parser.cc"
    break;

  case 18: // @4: %empty
#line 129 "parser.yy"
                                                               {yylhs.value.as < std::vector<Var> > () = std::vector<Var>();}
#line 848 "parser.cc"
    break;

  case 19: // funcDecl: "int" "main" $@3 "(" @4 ")" "<" stmtList ">"
#line 129 "parser.yy"
                                                                                                               { drv.pop_scope(); }
#line 854 "parser.cc"
    break;

  case 20: // params: paramList
#line 132 "parser.yy"
                                          { yylhs.value.as < std::vector<Var> > () = yystack_[0].value.as < std::vector<Var> > (); }
#line 860 "parser.cc"
    break;

  case 21: // params: %empty
#line 133 "parser.yy"
                                          { yylhs.value.as < std::vector<Var> > () = std::vector<Var>(); }
#line 866 "parser.cc"
    break;

  case 22: // paramList: paramList "," paramItem
#line 136 "parser.yy"
                                          { yystack_[2].value.as < std::vector<Var> > ().push_back(yystack_[0].value.as < Var > ()); yylhs.value.as < std::vector<Var> > () = yystack_[2].value.as < std::vector<Var> > (); }
#line 872 "parser.cc"
    break;

  case 23: // paramList: paramItem
#line 137 "parser.yy"
                                          { yylhs.value.as < std::vector<Var> > () = std::vector<Var>(1, yystack_[0].value.as < Var > ()); }
#line 878 "parser.cc"
    break;

  case 24: // paramItem: varType "identifier"
#line 140 "parser.yy"
                                          { yylhs.value.as < Var > () = drv.make_variable(yystack_[0].value.as < std::string > (), yystack_[0].location, yystack_[1].value.as < int > (), 0, 0); }
#line 884 "parser.cc"
    break;

  case 44: // exp: simpleExp
#line 183 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 890 "parser.cc"
    break;

  case 45: // exp: mutable "=" exp
#line 184 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 896 "parser.cc"
    break;

  case 46: // simpleExp: simpleExp "|" andExp
#line 187 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[2].value.as < Node > (); }
#line 902 "parser.cc"
    break;

  case 47: // simpleExp: andExp
#line 188 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 908 "parser.cc"
    break;

  case 48: // andExp: andExp "&" unaryRelExp
#line 191 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[2].value.as < Node > (); }
#line 914 "parser.cc"
    break;

  case 49: // andExp: unaryRelExp
#line 192 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 920 "parser.cc"
    break;

  case 50: // unaryRelExp: "!" unaryRelExp
#line 195 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 926 "parser.cc"
    break;

  case 51: // unaryRelExp: relExp
#line 196 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 932 "parser.cc"
    break;

  case 52: // relExp: sumExp relop sumExp
#line 199 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[2].value.as < Node > (); }
#line 938 "parser.cc"
    break;

  case 53: // relExp: sumExp
#line 200 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 944 "parser.cc"
    break;

  case 60: // sumExp: sumExp sumop mulExp
#line 211 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[2].value.as < Node > (); }
#line 950 "parser.cc"
    break;

  case 61: // sumExp: mulExp
#line 212 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 956 "parser.cc"
    break;

  case 64: // mulExp: mulExp mulop unaryExp
#line 219 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[2].value.as < Node > (); }
#line 962 "parser.cc"
    break;

  case 65: // mulExp: unaryExp
#line 220 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 968 "parser.cc"
    break;

  case 68: // unaryExp: unaryop unaryExp
#line 227 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 974 "parser.cc"
    break;

  case 69: // unaryExp: factor
#line 228 "parser.yy"
                                   { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 980 "parser.cc"
    break;

  case 72: // factor: immutable
#line 236 "parser.yy"
                            { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 986 "parser.cc"
    break;

  case 73: // factor: mutable
#line 237 "parser.yy"
                            { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 992 "parser.cc"
    break;

  case 74: // mutable: "identifier"
#line 240 "parser.yy"
                            { yylhs.value.as < Node > () = helpers::make_mutable(yystack_[0].value.as < std::string > ()); }
#line 998 "parser.cc"
    break;

  case 75: // mutable: "identifier" "[" exp "]"
#line 241 "parser.yy"
                            { yylhs.value.as < Node > () = helpers::make_mutable(yystack_[3].value.as < std::string > ()); }
#line 1004 "parser.cc"
    break;

  case 76: // immutable: "(" exp ")"
#line 244 "parser.yy"
                            { yylhs.value.as < Node > () = yystack_[1].value.as < Node > (); }
#line 1010 "parser.cc"
    break;

  case 77: // immutable: call
#line 245 "parser.yy"
                            { 
                              if (yystack_[0].value.as < Node > ().type == Node::Type::VOID) {
                                     error(yystack_[0].location, "void type can not be used as immutable.");
                              }
                              yylhs.value.as < Node > () = yystack_[0].value.as < Node > ();
                            }
#line 1021 "parser.cc"
    break;

  case 78: // immutable: constant
#line 251 "parser.yy"
                            { yylhs.value.as < Node > () = yystack_[0].value.as < Node > (); }
#line 1027 "parser.cc"
    break;

  case 79: // call: "identifier" "(" args ")"
#line 254 "parser.yy"
                            { yylhs.value.as < Node > () = helpers::make_mutable(yystack_[3].value.as < std::string > ()); }
#line 1033 "parser.cc"
    break;

  case 84: // constant: "int constant"
#line 265 "parser.yy"
                            { yylhs.value.as < Node > () = helpers::make_constant(drv.constants[yystack_[0].value.as < int > ()]); }
#line 1039 "parser.cc"
    break;

  case 85: // constant: "char constant"
#line 266 "parser.yy"
                            { yylhs.value.as < Node > () = helpers::make_constant(drv.constants[yystack_[0].value.as < int > ()]); }
#line 1045 "parser.cc"
    break;


#line 1049 "parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      yy_lac_discard_ ("error recovery");
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "if", "else", "elseif",
  "while", "continue", "break", "for", "return", "main", "=", "-", "+",
  "*", "/", "||", "&&", "&", "|", "^", "!", "<", "<=", "==", "!=", ">",
  ">=", "(", ")", "[", "]", "{", "}", ",", ".", "int", "char", "void",
  "int constant", "char constant", "identifier", "$accept", "unit",
  "programm", "declLists", "decl", "varDecl", "varType", "funcDecl", "$@1",
  "$@2", "$@3", "@4", "params", "paramList", "paramItem", "stmtList",
  "stmt", "selectStmt", "iterStmt", "whileStmt", "forStmt", "breakStmt",
  "continueStmt", "returnStmt", "expStmt", "exp", "simpleExp", "andExp",
  "unaryRelExp", "relExp", "relop", "sumExp", "sumop", "mulExp", "mulop",
  "unaryExp", "unaryop", "factor", "mutable", "immutable", "call", "args",
  "argList", "constant", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if YYDEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }


  bool
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if YYDEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (!yy_lac_established_)
      {
#if YYDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
    return true;
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* evt)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << evt << '\n';
        yy_lac_established_ = false;
      }
  }

  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -68;

  const signed char parser::yytable_ninf_ = -14;

  const signed char
  parser::yypact_[] =
  {
     -68,     7,    19,   -23,   -68,   -68,    20,   -68,   -10,   -68,
      -2,    11,   -68,   -68,   -68,   -68,    -4,    30,    31,   -29,
      -1,    35,   -68,   -16,   -68,   -68,   -68,    37,   -16,    40,
     -68,    25,    47,    48,   -68,   -68,    58,    69,   -68,    70,
     -16,    72,    34,    34,   -68,    34,    67,    75,    62,    82,
      90,    44,   -68,   -68,    65,    65,   -11,    84,    79,    95,
      34,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,    87,
     104,   106,   -68,   -68,    89,     8,   -68,    68,   -68,   114,
     -68,   -68,   -68,   100,   101,    65,    65,   -68,   -68,   -16,
     -68,    93,   -68,   -68,   102,    65,    65,    34,    -3,   -68,
     -68,   -68,    65,    65,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,    68,    68,   -68,   -68,    68,   -68,    65,   -68,
     -68,   103,   105,    94,   -68,   -68,   -68,   107,    96,   108,
     -68,   106,   -68,    16,     8,   -68,   -68,   111,   113,    65,
     -68,    65,   -68,    34,    34,   109,   -68,   112,   115,    65,
     -68,   -68,   116,   118,    34,   117,   -68
  };

  const signed char
  parser::yydefact_[] =
  {
       4,     0,     0,     3,     1,     2,    11,    12,     0,     5,
       0,     0,     7,    17,    15,     6,     8,     0,     0,     0,
       0,     0,    18,    21,    84,    85,     9,     0,    21,     0,
      11,     0,     0,    20,    23,    10,     0,     0,    24,     0,
       0,     0,    27,    27,    22,    27,     0,     0,     0,     0,
       0,     0,    71,    70,     0,     0,    74,     0,     0,     0,
      27,    29,    30,    35,    36,    31,    32,    33,    28,     0,
      44,    47,    49,    51,    53,    61,    65,     0,    69,    73,
      72,    77,    78,     0,     0,     0,     0,    40,    39,     0,
      41,     0,    50,    73,     0,    80,     0,    27,     8,    19,
      26,    43,     0,     0,    63,    62,    58,    55,    54,    57,
      59,    56,     0,     0,    66,    67,     0,    68,     0,    16,
      14,     0,     0,     0,    42,    76,    83,     0,    81,     0,
      25,    46,    48,    52,    60,    64,    45,     0,     0,     0,
      79,     0,    75,    27,    27,     0,    82,     0,     0,     0,
      34,    37,     0,     0,    27,     0,    38
  };

  const short
  parser::yypgoto_[] =
  {
     -68,   -68,   -68,   -68,   -68,     1,    10,   -68,   -68,   -68,
     -68,   -68,   110,   -68,   119,   -43,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -50,   -68,    41,   -48,   -68,
     -68,    36,   -68,    38,   -68,   -67,   -68,   -68,   -51,   -68,
     -68,   -68,   -68,   128
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     1,     2,     3,     9,    57,    58,    12,    21,    18,
      17,    29,    32,    33,    34,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
     112,    74,   113,    75,   116,    76,    77,    78,    79,    80,
      81,   127,   128,    82
  };

  const short
  parser::yytable_[] =
  {
      83,    91,    84,    93,    10,    94,    92,     4,    19,    19,
     117,    24,    25,    11,     6,     7,     8,   100,    95,     5,
      96,    30,     7,   114,   115,   -13,    93,    20,    20,   104,
     105,    13,    14,    31,    15,   121,   122,    46,    31,    27,
      47,    48,    49,    50,    51,   126,   129,    52,    53,   135,
      31,    93,    93,    16,   130,   132,    54,    52,    53,    22,
      23,    93,    93,    55,    28,    93,    54,    38,   136,    35,
      37,    30,     7,    55,    24,    25,    56,    39,    52,    53,
      90,    52,    53,    40,    24,    25,    56,    54,    41,   145,
     123,   146,    42,    43,    55,    45,    85,    55,    87,   152,
     147,   148,   104,   105,    86,    24,    25,    56,    24,    25,
      56,   155,   106,   107,   108,   109,   110,   111,    88,    89,
      97,    98,    99,   101,   102,   103,   118,   119,   120,   124,
     139,   141,   125,   137,   143,   138,   144,   140,    36,   150,
     142,   154,   151,   131,   156,   149,   153,    26,   133,     0,
       0,   134,     0,     0,     0,     0,     0,     0,     0,    44
  };

  const short
  parser::yycheck_[] =
  {
      43,    51,    45,    54,     3,    55,    54,     0,    12,    12,
      77,    40,    41,     3,    37,    38,    39,    60,    29,     0,
      31,    37,    38,    15,    16,    29,    77,    31,    31,    13,
      14,    11,    42,    23,    36,    85,    86,     3,    28,    40,
       6,     7,     8,     9,    10,    95,    96,    13,    14,   116,
      40,   102,   103,    42,    97,   103,    22,    13,    14,    29,
      29,   112,   113,    29,    29,   116,    22,    42,   118,    32,
      30,    37,    38,    29,    40,    41,    42,    30,    13,    14,
      36,    13,    14,    35,    40,    41,    42,    22,    30,   139,
      89,   141,    23,    23,    29,    23,    29,    29,    36,   149,
     143,   144,    13,    14,    29,    40,    41,    42,    40,    41,
      42,   154,    23,    24,    25,    26,    27,    28,    36,    29,
      36,    42,    27,    36,    20,    19,    12,    27,    27,    36,
      36,    35,    30,    30,    23,    30,    23,    30,    28,    27,
      32,    23,    27,   102,    27,    36,    30,    19,   112,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40
  };

  const signed char
  parser::yystos_[] =
  {
       0,    44,    45,    46,     0,     0,    37,    38,    39,    47,
      48,    49,    50,    11,    42,    36,    42,    53,    52,    12,
      31,    51,    29,    29,    40,    41,    86,    40,    29,    54,
      37,    49,    55,    56,    57,    32,    55,    30,    42,    30,
      35,    30,    23,    23,    57,    23,     3,     6,     7,     8,
       9,    10,    13,    14,    22,    29,    42,    48,    49,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    74,    76,    78,    79,    80,    81,
      82,    83,    86,    58,    58,    29,    29,    36,    36,    29,
      36,    68,    71,    81,    68,    29,    31,    36,    42,    27,
      58,    36,    20,    19,    13,    14,    23,    24,    25,    26,
      27,    28,    73,    75,    15,    16,    77,    78,    12,    27,
      27,    68,    68,    48,    36,    30,    68,    84,    85,    68,
      58,    70,    71,    74,    76,    78,    68,    30,    30,    36,
      30,    35,    32,    23,    23,    68,    68,    58,    58,    36,
      27,    27,    68,    30,    23,    58,    27
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    43,    44,    45,    46,    46,    47,    47,    48,    48,
      48,    49,    49,    51,    50,    52,    50,    53,    54,    50,
      55,    55,    56,    56,    57,    58,    58,    58,    59,    59,
      59,    59,    59,    59,    60,    61,    61,    62,    63,    64,
      65,    66,    66,    67,    68,    68,    69,    69,    70,    70,
      71,    71,    72,    72,    73,    73,    73,    73,    73,    73,
      74,    74,    75,    75,    76,    76,    77,    77,    78,    78,
      79,    79,    80,    80,    81,    81,    82,    82,    82,    83,
      84,    84,    85,    85,    86,    86
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     1,     0,     2,     2,     1,     2,     4,
       5,     1,     1,     0,     9,     0,     9,     0,     0,     9,
       1,     0,     3,     1,     2,     3,     2,     0,     1,     1,
       1,     1,     1,     1,     7,     1,     1,     7,    11,     2,
       2,     2,     3,     2,     1,     3,     3,     1,     3,     1,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     4,     3,     1,     1,     4,
       0,     1,     3,     1,     1,     1
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   103,   103,   106,   109,   110,   113,   114,   117,   118,
     119,   122,   123,   126,   126,   128,   128,   129,   129,   129,
     132,   133,   136,   137,   140,   143,   144,   145,   148,   149,
     150,   151,   152,   153,   156,   158,   159,   162,   165,   168,
     171,   174,   175,   180,   183,   184,   187,   188,   191,   192,
     195,   196,   199,   200,   203,   204,   205,   206,   207,   208,
     211,   212,   215,   216,   219,   220,   223,   224,   227,   228,
     231,   232,   236,   237,   240,   241,   244,   245,   251,   254,
     257,   258,   261,   262,   265,   266
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1713 "parser.cc"

#line 270 "parser.yy"


void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
