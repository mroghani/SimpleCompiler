# ifndef Helpers_HH
# define Helpers_HH

#include "../types.hh"
#include "../driver.hh"

namespace helpers
{
    Node make_constant(const Constant& c);
    Node make_mutable(driver& drv, std::string id, yy::location & loc, Node *ind);
    Node extract_mutable(Node & mu);
    Node sum_exp(Node & left, int op, Node & right);
    Node mul_exp(Node & left, int op, Node & right);
    Node unary_exp(Node & uexp, int op);
    Node rel_exp(Node & left, std::string op, Node & right);
    Node unary_rel_exp(Node & uexp);
    Node binary_exp(Node & left, std::string op, Node & right);
    Node assign(Node & mu, Node & exp);
    Node merge_nodes(Node & left, Node & right);
};

#endif