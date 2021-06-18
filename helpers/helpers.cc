#include "helpers.hh"
#include "../parser.hh"
#include <sstream>

Node helpers::make_constant(const Constant& c) {
    Node node;
    
    if (c.type == Constant::Type::INT) {
        node.type = Node::Type::INT;
    } else {
        node.type = Node::Type::CHAR;
    }
    
    std::ostringstream text;
    text << "LI $v0 " << c.value;

    node.code.text = text.str();


    return node;
}

Node helpers::make_mutable(std::string id) {

    Node node;



    return node;
}