#include "shared_vars.hpp"
#include "typename.hpp"
#include <crails/logger.hpp>

using namespace std;

namespace Crails
{
  void log_cast_or_catch(const SharedVars& vars, const string& name, const type_info& expected_type)
  {
    logger << Logger::Error << "failed to cast `" << name << "` from type " << Typename(vars.at(name).type()) << " to " << Typename(expected_type) << Logger::endl;
  }

  string bad_any_cast_message(const string& varname, const type_info& provided_type, const type_info& expected_type)
  {
    string message;

    message = string("could not cast `")
            + varname
            + "` from `" + Typename(provided_type).data()
            + "` to `" + Typename(expected_type).data() + '`';
    return message;
  }
}
