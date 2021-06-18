#include <iostream>
#include "driver.hh"

int main (int argc, char *argv[])
{
  int res = 0;
  driver drv;
  if (argc == 1) {
      if (drv.parse ("-")) {
          res = 1;
      }
  } else if (argc == 2) {
  // std::cerr << "here0" << std::endl;
      if (drv.parse (argv[1])) {
          res = 1;
      }
  // std::cerr << "here4" << std::endl;
      
  } else {
      std::cout << "Too many arguments." << std::endl;
  }
  // std::cerr << "here4" << std::endl;
  
  return res;
}