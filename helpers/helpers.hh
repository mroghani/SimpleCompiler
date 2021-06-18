# ifndef Helpers_HH
# define Helpers_HH

#include "../types.hh"

namespace helpers
{
    Node make_constant(const Constant& c);
    Node make_mutable(std::string id);
};

#endif