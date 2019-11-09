#include <iostream>
#include "./dynamic_lib/dynamic_lib.h"

int main(int argc, char *argv[]) {
  DynamicLib<int, int> myLib("/home/facundotorraca/Documents/Taller de Programacion/TallerDeProgramacion-TP4/cmake-build-debug/prueba_biblio_dinamica/count/libcount.so");
  std::cout << myLib.run_fun("say_one") << std::endl;
}
