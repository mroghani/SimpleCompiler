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
    return "\t\taddiu\t$sp,\t$sp,\t" + std::to_string(-4 * amount) + "\n";
}
// Decreases stack size and deallocates memory.
// amount > 0
std::string stackless(int amount = 1)
{
    // return "ADDI $sp, " + std::to_string(4*amount) + "\n";
    return "\t\taddiu\t$sp,\t$sp,\t" + std::to_string(4 * amount) + "\n";
}
// Loads a number into a register.
std::string li(int register_number, int value)
{
    return "\t\tli\t\t$" + std::to_string(register_number) + ",\t" + std::to_string(value) + "\n";
}
// Loads a number into a register.
std::string li(std::string register_name, int value)
{
    return "\t\tli\t\t$" + register_name + ",\t" + std::to_string(value) + "\n";
}
// Stores value of a register in an address (destination) .
std::string sw(int register_number, std::string destination)
{
    return "\t\tsw\t\t$" + std::to_string(register_number) + ",\t" + destination + "\n";
}
// Stores value of a register in an address (destination) .
std::string sw(std::string register_name, std::string destination)
{
    return "\t\tsw\t\t$" + register_name + ",\t" + destination + "\n";
}
// Loads value of an address (destination) into a register.
std::string lw(int register_number, std::string source)
{
    return "\t\tlw\t\t$" + std::to_string(register_number) + ",\t" + (source[0] == '$' ? "" : "$") + source + "\n";
}
// Loads value of an address (destination) in another address or register.
std::string lw(std::string destination, std::string source)
{
    return std::string("\t\tlw\t\t") + (destination[0] == '$' ? "" : "$") + destination + ",\t" + (source[0] == '$' ? "" : "$") + source + "\n";
}
// Copies the contents of source (arg #2) to destination (arg #1).
std::string move(std::string destination, std::string source)
{
    return "\t\tmove\t" + destination + ",\t" + source + "\n";
}
// Jumps to the instruction pointed to by $31.
std::string ret()
{
    return "\t\tj\t\t$31";
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
    return "\t\tADDU\t$" + destination + ",\t$" + source1 + ",\t$" + source2 + "\n";
}
// Subs two registers and stores the result in the destination register.
std::string subregisters(std::string destination, std::string source1, std::string source2)
{
    return "\t\tSUBU\t$" + destination + ",\t$" + source1 + ",\t$" + source2 + "\n";
}
// Adds an immediate value to a register and stores the result in the destination register.
std::string addimmediate(std::string destination, std::string source, int amount)
{
    return "\t\tADDIU\t$" + destination + ",\t$" + source + ",\t" + std::to_string(amount) + "\n";
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
        text << "\t\tMUL\t$t0,\t$t0,\t$t1" << std::endl;
    }
    else
    { // if "/"
        text << "\t\tDIV\t$t0,\t$t1" << std::endl;
        text << "\t\tMFLO\t$t0" << std::endl;
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
        text << "\t\tSLT\t\t$t0,\t$t0,\t$t1" << std::endl;
    }
    else if (op == ">")
    {
        text << "\t\tSLT\t\t$t0,\t$t1,\t$t0" << std::endl;
    }
    else if (op == "<=")
    {
        text << "\t\tSLT\t\t$t0,\t$t1,\t$t0" << std::endl;
        text << "\t\tXORI\t$t0,\t$t0,\t1" << std::endl;
    }
    else if (op == ">=")
    {
        text << "\t\tSLT\t\t$t0,\t$t0,\t$t1" << std::endl;
        text << "\t\tXORI\t$t0,\t$t0,\t1" << std::endl;
    }
    else if (op == "!=")
    {
        text << "\t\tXOR\t\t$t0,\t$t0,\t$t1" << std::endl;
        text << "\t\tSLTU\t$t0,\t$0,\t$t0" << std::endl;
    }
    else
    {
        // "=="
        text << "\t\tXOR\t\t$t0,\t$t0,\t$t1" << std::endl;
        text << "\t\tSLTIU\t$t0,\t$t0,\t1" << std::endl;
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
        text << "\t\tAND\t$t0,\t$t0,\t$t1" << std::endl;
    }
    else
    {
        // "|"
        text << "\t\tOR\t$t0,\t$t0,\t$t1" << std::endl;
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
         << "\t\tNEGU\t$t0,\t$t0" << sw("t0", sp(0));

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

Node helpers::merge_nodes(Node &left, Node &right) // DONE
{
    Node node;
    node.code.text = left.code.text + right.code.text;
    return node;
}


Node helpers::return_stmt(driver &drv, yy::location &loc, Node * exp) // DONE
{
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

    if (drv.is_in_main) {
        text << move("a0", "v0")
             << "\t\tli\t\t$v0,\t4" << std::endl
             << "\t\tsyscall" << std::endl;
    } else {
        text << lw("s1", reg_offset("s1", 1))
                << lw("ra", reg_offset("s1", 2))
                << move("sp", "s1")
                << stackless(2)
                << "\t\tJR\t\t$ra\n";
    }

    node.code.text = text.str();

    return node;
}


Node helpers::create_function(Function func, Node & stmts) // DONE
 {
    Node node;

    std::ostringstream text;

    // Store important registers
    text << func.id << ":\n"
         << stackmore(3)
         << sw("ra", sp(2))
         << sw("s1", sp(1))
         << lw("s1", sp(0));

    if (func.number_of_arguments > 0)
        text << stackmore(func.number_of_arguments);
        
    // Load args
    for (int i = 0; i < func.number_of_arguments; i++) {
        text << sw("a" + std::to_string(i), reg_offset("s1", -i));
    }


    text << stmts.code.text;

    node.code.text = text.str();

    return node;
}

Node helpers::call_function(driver &drv, std::string id, yy::location &loc, std::vector<Node> args)// DONE
{
    
    Function func = drv.get_function(id, loc);

    if (func.number_of_arguments > args.size()) {
            throw yy::parser::syntax_error(loc, "Too few arguments, expected " + std::to_string(args.size()) + " arguments.");
    } 
    if (func.number_of_arguments < args.size()) {
            throw yy::parser::syntax_error(loc, "Too many arguments, expected " + std::to_string(args.size()) + " arguments.");
    } 
    
    Node node;
    // find fucntion, find out number of args and space needed, import args from registers, import the code in 'text', 
    std::ostringstream text;

    
    for(auto arg : args) {
        text << arg.code.text;
    }

    for (int i = 0; i < args.size(); i++) {
        text << lw("a" + std::to_string(i), sp(args.size() - i - 1));
    }

    text << stackless(args.size() - 1);

    text << "\t\tJAL\t\t" << func.id << "\n";

    text << sw("v0", sp(0));

    node.code.text = text.str();

    return node;
}


Node helpers::make_if_stmt(driver &drv, Node& condition, Node& stmts, Node& elifclause, std::string endLabel, bool printEndLabel) // DONE
{
    Node node;
    std::ostringstream text;

    std::string falseLabel = drv.get_label();
    // std::string endLabel = drv.get_label();
    
    text << condition.code.text
         << lw("t0", sp(0))
         << stackless()
         << "\t\tBEQZ\t$t0,\t" << falseLabel << std::endl
         << stmts.code.text
         << "\t\tB\t\t" << endLabel << std::endl
         << falseLabel << ":" << std::endl
         << elifclause.code.text;

    if (printEndLabel)
        text << endLabel << ":" << std::endl;


    node.code.text = text.str();

    return node;
}


Node helpers::make_while(driver &drv, Node& condition, Node& stmts) // DONE
 {
    Node node;
    std::ostringstream text;

    std::string loop_label = drv.loop_labels_stack.back()["loop"]; // 'condition' label
    std::string end_label = drv.loop_labels_stack.back()["end"]; // 'after' label

    text << loop_label << ":" << std::endl
         << condition.code.text
         << lw("t0", sp(0))
         << stackless()
         << "\t\tBEQZ\t$t0,\t" << end_label << std::endl
         << stmts.code.text
         << "\t\tB\t\t" << loop_label << std::endl
         << end_label << ":" << std::endl;



    node.code.text = text.str();

    return node;
}

Node helpers::make_for(driver &drv, Node& init, Node& condition, Node& eachIter, Node& stmts) // DONE
 {
    Node node;
    std::ostringstream text;


    std::string cond_label = drv.get_label(); // 'condition' label
    std::string loop_label = drv.loop_labels_stack.back()["loop"]; // 'each iter' label
    std::string end_label = drv.loop_labels_stack.back()["end"]; // 'after' label

    text << init.code.text
         << "\t\tB\t\t" << cond_label << std::endl
         << loop_label << ":" << std::endl
         << eachIter.code.text
         << cond_label << ":" << std::endl
         << condition.code.text
         << lw("t0", sp(0))
         << stackless()
         << "\t\tBEQZ\t$t0,\t" << end_label << std::endl
         << stmts.code.text
         << "\t\tB\t\t" << loop_label << std::endl
         << end_label << ":" << std::endl;
         


    node.code.text = text.str();

    return node;
}

Node helpers::make_break(driver &drv, yy::location &loc)
{

    if (drv.loop_labels_stack.size() == 0) {
        throw yy::parser::syntax_error(loc, "Unexpected break.");
    }

    Node node;
    std::ostringstream text;


    std::string end_label = drv.loop_labels_stack.back()["end"];

    text << "\t\tB\t\t" << end_label << std::endl;

    node.code.text = text.str();

    return node;
}

Node helpers::make_continue(driver &drv, yy::location &loc)
{
    if (drv.loop_labels_stack.size() == 0) {
        throw yy::parser::syntax_error(loc, "Unexpected continue.");
    }

    Node node;
    std::ostringstream text;


    std::string loop_label = drv.loop_labels_stack.back()["loop"];

    text << "\t\tB\t\t" << loop_label << std::endl;

    node.code.text = text.str();

    return node;
}


Node helpers::var_init(Var & var, bool do_init) {
    Node node;
    std::ostringstream text;


    text << stackmore(var.size * 4);

    if (do_init) {
        text << li("t0", var.initial_value)
             << sw("t0", sp(0));
    }

    node.code.text = text.str();

    return node;
}
