#ifndef Node_HH
#define Node_HH

#include "Code.hh"
#include <map>
struct Node
{
    Code code;

    std::map<std::string, std::string> labels;

    // std::string start_label;
    // std::string end_label;
    // std::string continue_label;
    // std::string break_label;
    // std::string case_label;
    // std::string true_label;
    // std::string false_label;

    enum Type
    {
        VOID,
        INT,
        CHAR
    } type;
    int value;
};

#endif