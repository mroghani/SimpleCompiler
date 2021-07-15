# ifndef Helpers_HH
# define Helpers_HH

#include "../types.hh"
#include "../driver.hh"

namespace helpers
{
    Node load_constant(const Constant& c);
    Node load_mutable(driver& drv, std::string id, yy::location & loc, Node *ind);
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

std::string stackmore(int amount);
std::string stackless(int amount);

// std::string stackpush(int value);
// std::string stackpush(int value, int offset);
std::string stackpop(int offset);
// std::string storerhs();
std::string li(int register_number, int value);
std::string sw(int register_number, std::string destination);
std::string lw(int register_number, std::string source);
std::string sp(int offset);
std::string fp(int offset);

#endif