#include <iostream>
#include <dlfcn.h>

typedef int (*func_pointer)(void);


int main(int argc, char *argv[]) {
  const char *err;
  void *shared_lib = dlopen("../gretting/build/libgretting.1.0.2.dylib", RTLD_NOW);
  err = dlerror();
  if (!shared_lib) {
      printf("dlopen failed: %s\n", err);
      return -1;
  }
  func_pointer by2;
  *(void**) (&by2) = dlsym(shared_lib, "say_one");

  std::cout << by2() << std::endl;
  dlclose(shared_lib);
}