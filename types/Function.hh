# ifndef Function_HH
# define Function_HH

#include <string>

struct Function
{
    std::string id;

    int space_needed;
    int number_of_arguments;

    enum Type
    {
        INT,
        CHAR,
        VOID
    } type;    
};

#endif