#include "driver.hh"
#include "parser.hh"

driver::driver () {
  label_counter = 0;
  label_prefix = "Label_";
  curr_scope = -1;
  global_offset = 0;
  function_offset = 0;
  push_scope();
  
  in_loop = 0;
  in_switch = 0;
}

std::string driver::get_label () {
  std::string label = label_prefix;
  label_counter++;
  label = label + std::to_string(label_counter);
  return label;
}

void driver::push_scope () {
  curr_scope++;
  variables.push_back(std::map<std::string, Var>());
}

void driver::pop_scope () {
  curr_scope--;
  if (curr_scope == 0) {
    function_offset = 0;
  }
  variables.pop_back();
}

Var driver::make_variable(std::string id, yy::location & loc, int type, int size, int initial_value) {
  if (has_variable_in_scope(id, curr_scope)) {
    throw yy::parser::syntax_error(loc, "multiple definitions for '" + id + "'");
  }

  // std::cerr << id << curr_scope << std::endl;

  Var var;
  var.size = size;
  var.id = id;
  if (curr_scope == 0) {
    var.offset = global_offset;
    global_offset += size;
  } else {
    var.offset = function_offset;
    function_offset += size;
  }
  var.scope = curr_scope;
  var.type = type == 1 ? Var::Type::INT : Var::Type::CHAR; // int = 1, char = 2
  var.initial_value = initial_value;
  variables.back()[id] = var;

  // ! test
  // std::cerr << variables.size() << std::endl;
  // for (auto p : variables.back()) {
  //   std::cerr << p.first << ": " << p.second.scope << " " << p.second.offset << std::endl;
  // }

  return var;
}

Var driver::get_variable(std::string id, yy::location & loc) {

  for (int scope = curr_scope; scope >= 0; scope--) {
    auto it = variables[scope].find(id);
    if (it != variables[scope].end()) {
      return it->second;
    }
  }
  throw yy::parser::syntax_error(loc, "undefined identifier " + id);
}

Function driver::get_function(std::string id, yy::location & loc) {
  auto it = Functions.find(id);
  if (it != Functions.end()) {
    return it->second;
  }
  throw yy::parser::syntax_error(loc, "undefined identifier " + id);
}

void driver::make_func(std::string id, int type) {
  curr_function = id;
  Functions[curr_function] = Function();
  Functions[curr_function].id = id;
  Functions[curr_function].type = (Function::Type)(type - 1);

}

void driver::add_args_to_func(std::vector<Var> &vars, yy::location & loc) {
  if (vars.size() > 4) {
    throw yy::parser::syntax_error(loc, "Too many arguments");
  }
  Functions[curr_function].number_of_arguments = vars.size();


}


bool driver::has_variable_in_scope(std::string id, int scope) {
  // auto it = variables[scope].find(id);
  // if (it == variables[scope].end()) {
  //   return false;
  // }
  // return true;
  return variables[scope].find(id) != variables[scope].end();
}

int driver::parse (const std::string &f)
{
  file = f;
  location.initialize (&file);
  scan_begin ();
  yy::parser parse (*this);
  // parse.set_debug_level (false);
  // std::cerr << "here" << std::endl;
  int res = parse();
  // std::cerr << "here2" << std::endl;
  scan_end ();
  // std::cerr << "here3" << std::endl;
  return res;
}

void driver::pop_loop() {
  loop_labels_stack.pop_back();
}

void driver::push_loop() {
  loop_labels_stack.push_back(std::map<std::string, std::string>());
  loop_labels_stack.back()["loop"] = get_label();
  loop_labels_stack.back()["end"] = get_label();
}

void driver::make_output(Node & node) {
  std::ofstream out(file + ".out");
  out << ".text" << std::endl;

  out << "\t\tMOVE\t$s0,\t$sp" << std::endl;
  // out << "\t\taddiu\t$sp,\t$sp,\t" + std::to_string(-4 * global_offset) << std::endl;
  for (auto v : variables[0]) {
    auto var = v.second;
    out << "\t\tli\t\t$t0,\t" + std::to_string(var.initial_value) + "\n"
        << "\t\tsw\t\t$t0,\t$sp\n";
  }
  out << "\t\tB\tmain" << std::endl;

  out << node.code.text;
}