# ifndef Code_HH
# define Code_HH

#include <string>

struct Code
{
    std::string text;
    // int continue_label;
    // int break_label;
    // int case_label;
    int start_label;
    int end_label;

    /**
     *  start_label:   LI $s0, 12
     *                 ST $s0, ($t1)
     *  end_label:
     * */

};

#endif