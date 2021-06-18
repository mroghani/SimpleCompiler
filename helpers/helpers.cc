#include "helpers.hh"
#include "../parser.hh"
#include <sstream>
#include "../driver.hh"

Node helpers::make_constant(const Constant& c) {
    Node node;
    
    if (c.type == Constant::Type::INT) {
        node.type = Node::Type::INT;
    } else {
        node.type = Node::Type::CHAR;
    }
    

    // LI v0 {CONSTANT}
    std::ostringstream text;
    text << "LI $v0, " << c.value << std::endl;
    

    node.code.text = text.str();


    return node;
}


Node helpers::make_mutable(driver & drv, std::string id, yy::location & loc, Node *ind) {

    Node node;

    auto var = drv.get_variable(id, loc);


    // code gen:
    // find the address of mutable and put it in v1
    // if it's an array the index should be found in v0
    // v1 = sp + (offset * 4) + (v0 * 4)

    std::ostringstream text;
    if (ind != nullptr) {
        text << ind->code.text;
    }
    text << "ADDI $v1, $sp, " << var.offset * 4 << std::endl; // v1 = sp + offset * 4
    if (ind != nullptr) { // v1 = v1 + v0 * 4
        text << "SLL $v0, $v0, 2" << std::endl; // v0 = v0 * 4
        text << "ADD $v1, $v1, $v0" << std::endl; // v1 = v1 * v0
    }

    node.code.text = text.str();

    return node;
}


Node helpers::extract_mutable(Node & mu) {
    // v0 = (v1)

    Node node;

    std::ostringstream text;
    
    text << mu.code.text;
    text << "LW $v0, ($v1)" << std::endl;

    node.code.text = text.str();

    return node;
}


Node helpers::sum_exp(Node & left, int op, Node & right) {
    Node node;

    std::ostringstream text;
    
    text << right.code.text;
    text << "MOVE $v1, $v0" << std::endl;
    text << left.code.text;
    if (op == 1) {
        text << "ADD $v0, $v0, $v1" << std::endl;
    } else {
        text << "SUB $v0, $v0, $v1" << std::endl;
    }

    node.code.text = text.str();

    return node;
}


Node helpers::mul_exp(Node & left, int op, Node & right) {
    Node node;

    std::ostringstream text;
    
    text << right.code.text;
    text << "MOVE $v1, $v0" << std::endl;
    text << left.code.text;
    if (op == 1) {
        text << "MUL $v0, $v0, $v1" << std::endl;
    } else {
        text << "DIV $v0, $v1" << std::endl;
        text << "MFLO $v0" << std::endl;
    }

    node.code.text = text.str();

    return node;
}

Node helpers::unary_exp(Node & uexp, int op) {
    if (op == 1) {
        return uexp;
    }

    Node node;

    std::ostringstream text;
    
    text << uexp.code.text;
    text << "NEGU $v0, $v0" << std::endl;

    node.code.text = text.str();

    return node;
}