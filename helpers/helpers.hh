# ifndef Helpers_HH
# define Helpers_HH

#include "../types.hh"
#include "../driver.hh"

namespace helpers
{
    Node make_constant(const Constant& c);
    // Node make_mutable(driver& drv, std::string id);
    Node make_mutable(driver& drv, std::string id, yy::location & loc, Node *ind);
};

#endif