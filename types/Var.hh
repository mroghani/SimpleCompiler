# ifndef Var_HH
# define Var_HH

#include <string>

struct Var
{
    int offset;
    std::string id;
    int scope;
    int initial_value;

    enum Type
    {
        INT,
        CHAR
    } type;
};

#endif