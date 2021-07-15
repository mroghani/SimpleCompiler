#include "mips_helpers.hh"



std::string mips::stackmore(int amount=1){
    // return "SUBI $sp, " + std::to_string(-4*amount) + std::endl;
    return "addiu $sp, $sp, " + std::to_string(-4*amount) + std::endl;
}
std::string mips::stackless(int amount=1){
    // return "ADDI $sp, " + std::to_string(4*amount) + std::endl;
    return "addiu $sp, $sp, " + std::to_string(4*amount) + std::endl;
}
std::string mips::stackpush(int value){
    return "li $sp, " + std::to_string(value) << std::endl;
}
std::string mips::stackpush(int value, int offset=0){
    return "li " + std::to_string(4*value) + "($sp), " + std::to_string(value) + std::endl;
}
std::string mips::stackpop(std::string destination, int offset=0){
    return "lw "+ destination + ", " + std::to_string(-4*offset) + "($sp)" + std::endl;
}