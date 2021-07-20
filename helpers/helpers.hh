#ifndef Helpers_HH
#define Helpers_HH

#include "../types.hh"
#include "../driver.hh"

namespace helpers
{
    Node load_constant(const Constant &c);
    Node load_mutable(driver &drv, std::string id, yy::location &loc, Node *ind);
    Node load_mutable_value(Node &mu);
    Node sum_exp(Node &left, int op, Node &right);
    Node mul_exp(Node &left, int op, Node &right);
    Node unary_exp(Node &uexp, int op);
    Node rel_exp(Node &left, std::string op, Node &right);
    Node unary_rel_exp(Node &uexp);
    Node binary_exp(Node &left, std::string op, Node &right);
    Node assign(Node &mu, Node &exp);
    Node merge_nodes(Node &left, Node &right);

    Node create_function(Function func, Node & stmts);

    Node return_stmt(driver &drv, yy::location &loc, Node * exp);
};

std::string stackmore(int amount);
std::string stackless(int amount);
std::string li(int register_number, int value);
std::string li(std::string register_name, int value);
std::string sw(int register_number, std::string destination);
std::string sw(std::string register_name, std::string destination);
std::string lw(int register_number, std::string source);
std::string lw(std::string destination, std::string source);
std::string move(std::string destination, std::string source);
std::string ret();
std::string sp(int offset);
std::string fp(int offset);
std::string reg_offset(std::string reg, int offset);

std::string addregisters(std::string destination, std::string source1, std::string source2);
std::string subregisters(std::string destination, std::string source1, std::string source2);
std::string addimmediate(std::string destination, std::string source, int amount);

#endif