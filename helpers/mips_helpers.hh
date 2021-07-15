# ifndef MIPS_Helpers_HH
# define MIPS_Helpers_HH

#include <string>

namespace mips
{
    std::string stackmore(int amount=1);
    std::string stackless(int amount=1);

    std::string stackpush(int value);
    std::string stackpush(int value, int offset=0);
    std::string stackpop(int offset=0);
    // std::string storerhs();
};

#endif