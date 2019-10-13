#include "gretting.h"

Gretting::Gretting() : hello("HELLO WORD"), goodbye("GOODBYE WORLD") {}

std::string Gretting::say_hello() { return this->hello; }

std::string Gretting::say_goodbye() {return this->goodbye; }

Gretting::~Gretting() {}
