#include "typename.hpp"
#ifdef __GNUG__
# include <cstdlib>
# include <memory>
# include <cxxabi.h>
#endif

using namespace Crails;
using namespace std;

static const char* get_demangled_name(const type_info& input)
{
#ifdef __GNUG__
  int status;
  return abi::__cxa_demangle(input.name(), 0, 0, &status);
#else
  return input.name();
#endif
}

Typename::Typename(const type_info& input)
  : string_view(get_demangled_name(input))
{
}

Typename::Typename(Typename&& src)
  : string_view(*this)
{
  ownership = src.ownership;
  src.ownership = false;
}

Typename::~Typename()
{
#ifdef __GNUG__
  if (ownership)
    free(const_cast<char*>(data()));
#endif
}

