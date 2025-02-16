#ifndef SHARED_VARS_HPP
# define SHARED_VARS_HPP

# include "any_cast.hpp"
# include <string>
# include <map>

namespace Crails
{
  typedef std::map<std::string, std::any> SharedVars;

  SharedVars merge(SharedVars, const SharedVars&);

  void throw_cast_failure(const std::string& varname, const std::type_info& provided, const std::type_info& expected);
  void throw_out_of_range_failure(const SharedVars& vars, const std::string& varname);
  void log_bad_any_cast(const SharedVars& a, const std::string& k, const std::type_info& expected_type);

  template<typename T>
  T cast(const SharedVars& vars, const std::string& name)
  {
    SharedVars::const_iterator var = vars.find(name);

    if (var == vars.end())
    {
      throw_out_of_range_failure(vars, name);
    }
    try
    {
      return Any<T>::cast(var->second);
    }
    catch (std::bad_any_cast)
    {
      throw_cast_failure(name, var->second.type(), typeid(T));
    }
    return Any<T>::cast(var->second); // unreachable, but prevents return-type warnings
  }

  template<typename T>
  T cast(const SharedVars& vars, const std::string& name, T default_value)
  {
    SharedVars::const_iterator var = vars.find(name);

    try
    {
      if (var != vars.end())
        return Any<T>::cast(var->second);
    }
    catch (std::bad_any_cast)
    {
      throw_cast_failure(name, var->second.type(), typeid(T));
    }
    return default_value;
  }

  // deprecate ?
  template<typename T>
  T defaults_to(const SharedVars& vars, const std::string& name, const T default_value) noexcept
  {
    SharedVars::const_iterator var = vars.find(name);

    try
    {
      if (var != vars.end())
        return Any<T>::cast(var->second);
    }
    catch (std::bad_any_cast)
    {
      log_bad_any_cast(vars, name, typeid(T));
    }
    return default_value;
  }
}

#endif
