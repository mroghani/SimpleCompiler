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
    

    // LI t0 {CONSTANT}
    std::ostringstream text;
    text << "LI $t0, " << c.value << std::endl;
    

    node.code.text = text.str();


    return node;
}


Node helpers::make_mutable(driver & drv, std::string id, yy::location & loc, Node *ind) {

    Node node;

    auto var = drv.get_variable(id, loc);


    // code gen:
    // find the address of mutable and put it in t1
    // if it's an array the index should be found in t0
    // t2 = sp + (offset * 4) + (t0 * 4)

    std::ostringstream text;
    if (ind != nullptr) {
        text << ind->code.text;
    }
    text << "ADDI $t2, $sp, " << var.offset * 4 << std::endl; // t2 = sp + offset * 4
    if (ind != nullptr) { // t2 = t2 + t0 * 4
        text << "SLL $t0, $t0, 2" << std::endl; // t0 = t0 * 4
        text << "ADD $t2, $t2, $t0" << std::endl; // t1 = t1 * t0
    }

    node.code.text = text.str();

    return node;
}


Node helpers::extract_mutable(Node & mu) {
    // t0 = (t2)

    Node node;

    std::ostringstream text;
    
    text << mu.code.text;
    text << "LW $t0, ($t2)" << std::endl;

    node.code.text = text.str();

    return node;
}


Node helpers::sum_exp(Node & left, int op, Node & right) {
    Node node;

    std::ostringstream text;
    
    text << right.code.text;
    text << "MOVE $t1, $t0" << std::endl;
    text << left.code.text;
    if (op == 1) {
        text << "ADD $t0, $t0, $t1" << std::endl;
    } else {
        text << "SUB $t0, $t0, $t1" << std::endl;
    }

    node.code.text = text.str();

    return node;
}


Node helpers::mul_exp(Node & left, int op, Node & right) {
    Node node;

    std::ostringstream text;
    
    text << right.code.text;
    text << "MOVE $t1, $t0" << std::endl;
    text << left.code.text;
    if (op == 1) {
        text << "MUL $t0, $t0, $t1" << std::endl;
    } else {
        text << "DIV $t0, $t1" << std::endl;
        text << "MFLO $t0" << std::endl;
    }

    node.code.text = text.str();

    return node;
}


Node helpers::rel_exp(Node & left, std::string op, Node & right) {
    Node node;

    std::ostringstream text;
    
    text << right.code.text;
    text << "MOVE $t1, $t0" << std::endl;
    text << left.code.text;
    
    if(op == "<") {
        text << "SLT $t0, $t0, $t1" << std::endl;
	} else if(op == ">") {
        text << "SLT $t0, $t1, $t0" << std::endl;
	} else if(op == "<=") {
        text << "SLT $t0, $t1, $t0" << std::endl;
        text << "XORI $t0, $t0, 0x1" << std::endl;
	} else if(op == ">=") {
	    text << "SLT $t0, $t0, $t1" << std::endl;
        text << "XORI $t0, $t0, 0x1" << std::endl;
	} else if(op == "!=") {
	    text << "XOR $t0, $t0, $t1" << std::endl;
	    text << "SLTU $t0, $0, $t0" << std::endl;
	} else {
        // "=="
        text << "XOR $t0, $t0, $t1" << std::endl;
	    text << "SLTIU $t0, $t0, 1" << std::endl;    
    }

    node.code.text = text.str();

    return node;
}


Node helpers::binary_exp(Node & left, std::string op, Node & right) {
    Node node;

    std::ostringstream text;
    
    text << right.code.text;
    text << "MOVE $t1, $t0" << std::endl;
    text << left.code.text;
    
    if(op == "&") {
        text << "AND $t0, $t0, $t1" << std::endl;
	} else {
        // "|"   
        text << "OR $t0, $t0, $t1" << std::endl;
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
    text << "NEGU $t0, $t0" << std::endl;

    node.code.text = text.str();

    return node;
}


Node helpers::unary_rel_exp(Node & uexp) {
    Node node;

    std::ostringstream text;
    
    text << uexp.code.text;
    text << "NOT $t0, $t0" << std::endl;

    node.code.text = text.str();

    return node;
}

Node helpers::assign(Node & mu, Node & exp) {

    Node node;

    std::ostringstream text;
    
    text << mu.code.text; // t2 = mutable address
    text << "MOVE $t3, $t2" << std::endl; // t3 = t2 = mutable address 
    text << exp.code.text; // t0 = exp
    text << "SW $t0, ($t3)" << std::endl; // mu = t0 = exp

    node.code.text = text.str();

    return node;
}


Node helpers::merge_nodes(Node & left, Node & right) {
    Node node;
    node.code.text = left.code.text + right.code.text;
    return node;
}