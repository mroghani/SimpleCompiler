#include "helpers.hh"
#include "../parser.hh"
#include <sstream>
#include "../driver.hh"
#include "debug.hh"



Node helpers::load_constant(const Constant& c) {
    Node node;
    ddd&&std::cout << "[helpers]=> make_constant\t val=\t" << c.value << "\t type:\t" << c.type << std::endl;
    // if (c.type == Constant::Type::INT) {
    //     node.type = Node::Type::INT;
    // } else {
    //     node.type = Node::Type::CHAR;
    // }


    // Push the constant value on stack.
    std::ostringstream text;
    text << "LI $sp, " << c.value << std::endl;
    text << "SUBI $sp, " << 4 << std::endl;


    node.code.text = text.str();


    return node;
}


Node helpers::load_mutable(driver & drv, std::string id, yy::location & loc, Node *ind) {

    Node node;

    auto var = drv.get_variable(id, loc);
    ddd&&std::cout << "[helpers]=> load_mutable:\tid:\t" << id << "\t" << std::endl;

    // code gen:

    std::ostringstream text;
    
    // find offset
    
    // pushing the offset to stack.
    text << "LI $sp, " << var.offset * 4 << std::endl;
    text << "SUBI $sp, " << 4 << std::endl;
    
    // if it is an array we push the index to stack as well. and then add it to offset.
    if (ind != nullptr) {
        text << ind->code.text; // index is on top of stack.
        //loading offset and index into registers.
        text << "LW $t0, 4($sp)" << std::endl;
        text << "LW $t1, ($sp)" << std::endl; 
        // adding them together and modifying the sp.
        text << "ADD $t0, $t0, $t1" << std::endl;
        text << "ADDI $sp, 4" << std::endl;
        text << "SW $t0, ($sp)" << std::endl;
    }
    // load (base + offset) ==> sp

    // load variable
    
    // load base
    if (var.scope == 0) {
        // if var is global
        text << "LW $t1, ($s0)" << std::endl; // load base
    } else {
        // if var is local
        text << "LW $t1, ($s1)" << std::endl; // load base
    }
    
    text << "LW $t0, ($sp)" << std::endl; // load offset 
    text << "ADD $t0, $t0, $t1" << std::endl; // $t0 = base + offset
    text << "SW $t0, ($sp)" << std::endl; // store the mutable address in stack



    node.code.text = text.str();

    return node;
}


Node helpers::extract_mutable(Node & mu) {

    Node node;

    std::ostringstream text;

    text << mu.code.text; // get mutable address.
    text << "LW $t0, ($sp)" << std::endl; // load variable value in $t0
    text << "SW $t0, ($sp)" << std::endl; // put it in stack.

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