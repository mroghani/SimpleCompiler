#include "helpers.hh"
#include "../parser.hh"
#include <sstream>
#include "../driver.hh"
#include "debug.hh"

// Increases stack size and allocates more memory.
// amount > 0
std::string stackmore(int amount = 1)
{
    // return "SUBI $sp, " + std::to_string(-4*amount) + "\n";
    return "addiu $sp, $sp, " + std::to_string(-4 * amount) + "\n";
}
// Decreases stack size and deallocates memory.
// amount > 0
std::string stackless(int amount = 1)
{
    // return "ADDI $sp, " + std::to_string(4*amount) + "\n";
    return "addiu $sp, $sp, " + std::to_string(4 * amount) + "\n";
}
// Loads a number into a register.
std::string li(int register_number, int value)
{
    return "li $" + std::to_string(register_number) + ", " + std::to_string(value) + "\n";
}
// Loads a number into a register.
std::string li(std::string register_name, int value)
{
    return "li $" + register_name + ", " + std::to_string(value) + "\n";
}
// Stores value of a register in an address (destination) .
std::string sw(int register_number, std::string destination)
{
    return "sw $" + std::to_string(register_number) + ", " + destination + "\n";
}
// Stores value of a register in an address (destination) .
std::string sw(std::string register_name, std::string destination)
{
    return "sw $" + register_name + ", " + destination + "\n";
}
// Loads value of an address (destination) into a register.
std::string lw(int register_number, std::string source)
{
    return "lw $" + std::to_string(register_number) + ", " + (source[0] == '$' ? "" : "$") + source + "\n";
}
// Loads value of an address (destination) in another address or register.
std::string lw(std::string destination, std::string source)
{
    return std::string("lw ") + (destination[0] == '$' ? "" : "$") + destination + ", " + (source[0] == '$' ? "" : "$") + source + "\n";
}
// Copies the contents of source (arg #2) to destination (arg #1).
std::string move(std::string destination, std::string source)
{
    return "move " + destination + ", " + source + "\n";
}
// Jumps to the instruction pointed to by $31.
std::string ret()
{
    return "j $31";
}
// Returns "?($sp)" or "$sp"
std::string sp(int offset = 0)
{
    if (offset)
        return std::to_string(4 * offset) + "($sp)";
    else
        return "$sp";
}
// Returns "?($fp)" or "$fp"
std::string fp(int offset = 0)
{
    if (offset)
        return std::to_string(4 * offset) + "($fp)";
    else
        return "$fp";
}
// Returns "?($reg)" or "$reg"
std::string reg_offset(std::string reg, int offset)
{
    if (offset)
        return std::to_string(4 * offset) + "($" + reg + ")";
    else
        return "$" + reg;
}
// Adds two registers and stores the result in the destination register.
std::string addregisters(std::string destination, std::string source1, std::string source2)
{
    return "ADDU $" + destination + ", $" + source1 + ", $" + source2 + "\n";
}
// Subs two registers and stores the result in the destination register.
std::string subregisters(std::string destination, std::string source1, std::string source2)
{
    return "SUBU $" + destination + ", $" + source1 + ", $" + source2 + "\n";
}
// Adds an immediate value to a register and stores the result in the destination register.
std::string addimmediate(std::string destination, std::string source, int amount)
{
    return "ADDIU $" + destination + ", $" + source + ", " + std::to_string(amount) + "\n";
}

Node helpers::load_constant(const Constant &c) // DONE
{
    Node node;
    ddd &&std::cout << "[helpers]=> make_constant\t val=\t" << c.value << "\t type:\t" << c.type << std::endl;

    // Push the constant value on stack.
    std::ostringstream text;
    text << stackmore(1) << li("t0", c.value) << sw("t0", sp(0));
    node.code.text = text.str();

    return node;
}

Node helpers::load_mutable(driver &drv, std::string id, yy::location &loc, Node *ind) // DONE
{

    Node node;

    auto var = drv.get_variable(id, loc);
    ddd &&std::cout << "[helpers]=> load_mutable:\tid:\t" << id << "\t" << std::endl;

    // code gen:

    std::ostringstream text;

    // find base reg
    std::string base_reg = (var.scope == 0 ? "s0" : "s1");

    // fp is set by scope helper.
    if (ind == nullptr)
    { // variable
        // text << stackmore(1) << lw("t0", reg_offset(base_reg, var.offset)) << sw("t0", sp(0));
        text << addimmediate("t0", base_reg, -4 * var.offset)
             << stackmore(1)
             << sw("t0", sp(0));
    }
    else
    {
        // array
        text << ind->code.text // index is on top of stack.
             << addimmediate("t0", base_reg, -4 * var.offset)
             << lw("t1", sp(0))
             << addregisters("t0", "t0", "t1")
             << sw("t0", sp(0));
    }

    node.code.text = text.str();

    return node;
}

Node helpers::load_mutable_value(Node &mu) // DONE
{
    Node node;

    std::ostringstream text;

    text << lw("t0", sp(0))
         << lw("t0", "t0") // At first, "t0" holds the address, after this instruction it holds the contents of the address.
         << sw("t0", sp(0));
    
    node.code.text = text.str();
    
    return node;
}

Node helpers::sum_exp(Node &left, int op, Node &right) // DONE
{
    Node node;

    std::ostringstream text;

    text << left.code.text
         << right.code.text
         << lw("t0", sp(0))
         << lw("t1", sp(1));

    if (op == 1)
    {
        text << addregisters("t0", "t0", "t1");
    }
    else
    {
        text << subregisters("t0", "t0", "t1");
    }

    text << stackless(1) << sw("t0", sp(0));

    node.code.text = text.str();

    return node;
}

Node helpers::mul_exp(Node &left, int op, Node &right) // DONE
{
    Node node;

    std::ostringstream text;

    text << left.code.text
         << right.code.text
         << lw("t0", sp(0))
         << lw("t1", sp(1));

    if (op == 1)
    { // if "*"
        text << "MUL $t0, $t0, $t1" << std::endl;
    }
    else
    { // if "/"
        text << "DIV $t0, $t1" << std::endl;
        text << "MFLO $t0" << std::endl;
    }

    text << stackless(1) << sw("t0", sp(0));

    node.code.text = text.str();

    return node;
}

Node helpers::rel_exp(Node &left, std::string op, Node &right) // DONE
{
    Node node;

    std::ostringstream text;

    text << left.code.text
         << right.code.text
         << lw("t0", sp(0))
         << lw("t1", sp(1));

    if (op == "<")
    {
        text << "SLT $t0, $t0, $t1" << std::endl;
    }
    else if (op == ">")
    {
        text << "SLT $t0, $t1, $t0" << std::endl;
    }
    else if (op == "<=")
    {
        text << "SLT $t0, $t1, $t0" << std::endl;
        text << "XORI $t0, $t0, 0x1" << std::endl;
    }
    else if (op == ">=")
    {
        text << "SLT $t0, $t0, $t1" << std::endl;
        text << "XORI $t0, $t0, 0x1" << std::endl;
    }
    else if (op == "!=")
    {
        text << "XOR $t0, $t0, $t1" << std::endl;
        text << "SLTU $t0, $0, $t0" << std::endl;
    }
    else
    {
        // "=="
        text << "XOR $t0, $t0, $t1" << std::endl;
        text << "SLTIU $t0, $t0, 1" << std::endl;
    }

    text << stackless(1) << sw("t0", sp(0));

    node.code.text = text.str();

    return node;
}

Node helpers::binary_exp(Node &left, std::string op, Node &right) // DONE
{
    Node node;

    std::ostringstream text;

    text << left.code.text
         << right.code.text
         << lw("t0", sp(0))
         << lw("t1", sp(1));

    if (op == "&")
    {
        text << "AND $t0, $t0, $t1" << std::endl;
    }
    else
    {
        // "|"
        text << "OR $t0, $t0, $t1" << std::endl;
    }

    text << stackless(1) << sw("t0", sp(0));

    node.code.text = text.str();

    return node;
}

Node helpers::unary_exp(Node &uexp, int op) // DONE
{
    if (op == 1)
    {
        return uexp;
    }

    Node node;

    std::ostringstream text;

    text << uexp.code.text << lw("t0", sp(0))
         << "NEGU $t0, $t0" << sw("t0", sp(0));

    node.code.text = text.str();

    return node;
}

Node helpers::unary_rel_exp(Node &uexp) // DONE
{
    Node node;

    std::ostringstream text;

    text << uexp.code.text << lw("t0", sp(0))
         << "NOT $t0, $t0" << sw("t0", sp(0));

    node.code.text = text.str();

    return node;
}

Node helpers::assign(Node &mu, Node &exp) // DONE
{

    Node node;

    std::ostringstream text;

    text << exp.code.text << mu.code.text << lw("t1", sp(1)) << lw("t0", sp(0)) << sw("t1", "t0") << stackless(2);
    node.code.text = text.str();

    return node;
}

Node helpers::merge_nodes(Node &left, Node &right)
{
    Node node;
    node.code.text = left.code.text + right.code.text;
    return node;
}


Node helpers::return_stmt(driver &drv, yy::location &loc, Node * exp) {
    Node node;

    std::ostringstream text;


    if (exp == nullptr) { // if returns nothing
        if (drv.Functions[drv.curr_function].type != Function::Type::VOID) {
            throw yy::parser::syntax_error(loc, "return type is not compatible.");
        }
    } else { // if returns int or char
        if (drv.Functions[drv.curr_function].type == Function::Type::VOID) {
            throw yy::parser::syntax_error(loc, "return type is not compatible.");
        }

        text << exp->code.text;

        text << lw("v0", "sp");

    }

    text << lw("s0", reg_offset("s0", 1))
            << lw("ra", reg_offset("s0", 2))
            << lw("sp", "s0")
            << stackless(2)
            << "JR $ra\n";
    
    node.code.text = text.str();

    return node;
}


Node helpers::create_function(Function func, Node & stmts) {
    Node node;

    std::ostringstream text;

    // Store important registers
    text << func.id << ":\n"
         << stackmore(3)
         << sw("ra", sp(2))
         << sw("s0", sp(1))
         << lw("s0", sp(0));

    if (func.number_of_arguments > 0)
        text << stackmore(func.number_of_arguments);
        
    // Load args
    for (int i = 0; i < func.number_of_arguments; i++) {
        std::string rname = "a0";
        rname[1] = '0' + i; 
        text << sw(rname, reg_offset("s0", -i));
    }


    text << stmts.code.text;


    node.code.text = text.str();

    return node;
}