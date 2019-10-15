#include <iostream>
#include "./dynamic_lib/dynamic_lib.h"

typedef int (*func_pointer)(void);


int main(int argc, char *argv[]) {
  DynamicLib<int, int> myLib("../count/build/libcount.1.0.2.dylib");
  std::cout << myLib.run_fun("say_one") << std::endl;
}
