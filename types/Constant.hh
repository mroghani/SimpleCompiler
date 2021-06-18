# ifndef Constant_HH
# define Constant_HH

struct Constant
{
    int value;

    enum Type
    {
        INT,
        CHAR
    } type;
};

#endif