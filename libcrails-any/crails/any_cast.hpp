#ifndef  CRAILS_ANY_CAST_HPP
# define CRAILS_ANY_CAST_HPP

# include <any>
# include <string>

namespace Crails
{
  template<typename T>
  struct Any
  {
    static T cast(const std::any& var)
    {
      return std::any_cast<T>(var);
    }
  };

  std::string any_cast(const std::any& val);
}

# include "any_string_cast.hpp"
#endif
