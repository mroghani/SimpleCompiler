# ifndef DRIVER_HH
# define DRIVER_HH
# include <string>
# include <map>
# include <set>
# include <fstream>
# include "types.hh"
# include "parser.hh"
#include "helpers/helpers.hh"


// Give Flex the prototype of yylex we want ...
# define YY_DECL \
  yy::parser::symbol_type yylex (driver& drv)
// ... and declare it for the parser's sake.
YY_DECL;


// Conducting the whole scanning and parsing of Calc++.
class driver {
public:
    driver ();

    // ====> LABEL
    std::string label_prefix;
    int label_counter;
    std::string get_label();


    // ====> SCOPE
    int curr_scope;

    void push_scope();
    void pop_scope();

    int in_loop;
    int in_switch;
    
    // ====> FUNCTIONS

    std::map<std::string, Function> Functions;

    Function get_function(std::string id, yy::location & loc);
    void make_func(std::string id, int type);
    void add_args_to_func(std::vector<Var> &vars, yy::location & loc);

    std::string curr_function;

    // ====> VARIABLES
    int global_offset;
    int function_offset;
    std::vector<std::map<std::string, Var>> variables;

    Var get_variable(std::string id, yy::location & loc);
    Var make_variable(std::string id, yy::location & loc, int type, int size, int initial_value);
    bool has_variable_in_scope(std::string id, int scope);


    // ====> CONSTANTS
    std::vector<Constant> constants;

    // ====> OUTPUT

    void make_output(Node & node) {
      std::ofstream out(file + ".out");
      out << node.code.text;
    }


    // ====> FILE
    // Run the parser on file F.  Return 0 on success.
    int parse (const std::string& f);
    // The name of the file being parsed.
    std::string file;


    // ====> SCANNER
    // Handling the scanner.
    void scan_begin ();
    void scan_end ();

    // Whether to generate scanner debug traces.
    yy::location location;
};

#endif // ! DRIVER_HH