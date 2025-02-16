#include "shared_vars.hpp"
#include <crails/utils/backtrace.hpp> 
#include <crails/logger.hpp>
#include <sstream>
#include <functional>
#include <typeinfo>

using namespace std;

namespace Crails
{
  SharedVars merge(SharedVars vars, const SharedVars& second)
  {
    for (const auto& var : second)
    {
      if (vars.find(var.first) == vars.end())
        vars.emplace(var.first, var.second);
    }
    return vars;
  }

  string output_vars_list(const SharedVars& vars)
  {
    ostringstream stream;

    stream << "Debugging available SharedVars:" << std::endl;
    for (const auto& var : vars)
      stream << "- " << var.first << " (" << var.second.type().name() << ')' << std::endl;
    return stream.str();
  }

  void throw_out_of_range_failure(const SharedVars& vars, const string& varname)
  {
    string message = "cannot find shared variable `" + varname + '`';

    logger << Logger::Debug << std::bind(&output_vars_list, vars) << Logger::endl;
    throw boost_ext::out_of_range(message.c_str());
  }

  string bad_any_cast_message(const string& varname, const type_info& provided, const type_info& expected);

  void throw_cast_failure(const string& varname, const type_info& provided, const type_info& expected)
  {
    throw boost_ext::runtime_error(
      bad_any_cast_message(varname, provided, expected)
    );
  }
}
