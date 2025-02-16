#include "any_cast.hpp"
#include "shared_vars.hpp"

namespace Crails
{
  std::string any_cast(const std::any& val)
  {
    return Any<std::string>::cast(val);
  }
}
