# ifndef Node_HH
# define Node_HH

#include "Code.hh"

struct Node
{
    Code code;
    enum Type
    {
        VOID,
        INT,
        CHAR
    } type;
    int value;
};

#endif