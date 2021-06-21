#include "driver.hh"
#include "parser.hh"

driver::driver () {
  label_counter = 0;
  label_prefix = "Label_";
  curr_scope = -1;
  push_scope();
}

int driver::get_label () {
  return label_counter++;
}

void driver::push_scope () {
  curr_scope++;
  variables.push_back(std::map<std::string, Var>());
}

void driver::pop_scope () {
  curr_scope--;
  variables.pop_back();
}

Var driver::make_variable(std::string id, yy::location & loc, int type, int size, int initial_value) {
  if (has_variable_in_scope(id, curr_scope)) {
    throw yy::parser::syntax_error(loc, "multiple definitions for '" + id + "'");
  }

  // TODO: arrays.
  // TODO: Offsets should be with recpect to functions not scopes.

  std::cerr << id << curr_scope << std::endl;

  Var var;
  var.id = id;
  var.offset = variables.back().size();
  var.scope = curr_scope;
  var.type = type == 1 ? Var::Type::INT : Var::Type::CHAR; // int = 1, char = 2
  var.initial_value = initial_value;
  variables.back()[id] = var;
  return var;
}

Var driver::get_variable(std::string id, yy::location & loc) {

  for (int scope = curr_scope - 1; scope >= 0; scope--) {
    auto it = variables[scope].find(id);
    if (it != variables[scope].end()) {
      return it->second;
    }
  }
  throw yy::parser::syntax_error(loc, "undefined identifier " + id);
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