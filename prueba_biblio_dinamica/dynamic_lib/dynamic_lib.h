#ifndef DYNAMIC_LIB_
#define DYNAMIC_LIB_

#include <string>
#include <dlfcn.h>

template <class INPUT, class OUTPUT>
class DynamicLib{
  void *lib;
 public:
  explicit DynamicLib(std::string lib_path) : lib(dlopen(lib_path.c_str(), RTLD_NOW)) {}

  OUTPUT run_fun(std::string fun, INPUT in) {
    OUTPUT (*fun_dl)(INPUT);
    *(void**) (&fun_dl) = dlsym(this->lib, fun.c_str());
    return fun_dl(in);
  }
  OUTPUT run_fun(std::string fun) {
    OUTPUT (*fun_dl)(void);
    *(void**) (&fun_dl) = dlsym(this->lib, fun.c_str());
    return fun_dl();
  }

  ~DynamicLib() {
    dlclose(this->lib);
  }
};
#endif  //  DYNAMIC_LIB_
