# ifndef Code_HH
# define Code_HH

#include <string>

struct Code
{
    std::string text;
    // std::string continue_label;
    // std::string break_label;
    // std::string case_label;
    std::string start_label;
    std::string end_label;

    /**
     *  start_label:   LI $s0, 12
     *                 ST $s0, ($t1)
     *  end_label:
     * */

};

#endif