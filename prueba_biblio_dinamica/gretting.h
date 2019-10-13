#ifndef GRETTING_H_
#define GRETTING_H_

#include <string>

class Gretting {
  std::string hello;
  std::string goodbye;
 public:
  Gretting();
  std::string say_hello();
  std::string say_goodbye();
  ~Gretting();
};

#endif  //  GRETTING_H_
