#include <iostream>
#include "gretting.h"

int main(int argc, char *argv[]) {
  Gretting gretting = Gretting();
  std::cout << gretting.say_hello() << std::endl;
  std::cout << gretting.say_goodbye() << std::endl;
}