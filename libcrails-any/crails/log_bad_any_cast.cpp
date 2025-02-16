#include <crails/logger.hpp>
#include "shared_vars.hpp"

#ifdef __GNUG__
# include <cstdlib>
# include <memory>
# include <cxxabi.h>
#endif

using namespace std;

namespace Crails
{
  string bad_any_cast_message(const string& varname, const type_info& provided_type, const type_info& expected_type)
  {
    string message;
#ifdef __GNUG__
    int status;
    char* expected = abi::__cxa_demangle(expected_type.name(), 0, 0, &status);
    char* provided = abi::__cxa_demangle(provided_type.name(), 0, 0, &status);
#else
    const char* expected = expected_type.name();
    const char* provided = provided_type.name();
#endif

    message = string("could not cast `")
            + varname
            + "` from `" + provided
            + "` to `" + expected + '`';
#ifdef __GNUG__
    free(expected);
    free(provided);
#endif
    return message;
  }

  void log_bad_any_cast(const SharedVars& a, const string& k, const type_info& expected_type)
  {
    SharedVars::const_iterator it = a.find(k);

    if (it != a.end())
    {
      std::any value = it->second;

      logger << Logger::Error
             << bad_any_cast_message(k, value.type(), expected_type)
             << Logger::endl;
    }
  }
}
