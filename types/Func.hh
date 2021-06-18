# ifndef Func_HH
# define Func_HH

#include "Var.hh"

#include <string>
#include <vector>

struct Func
{
    enum Type
    {
        INT,
        CHAR,
        VOID
    } type;

    std::string id;
    std::vector<Var> args;
    Type return_type;

};

#endif