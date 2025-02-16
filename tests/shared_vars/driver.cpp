#include <crails/shared_vars.hpp>
#include <stdexcept>

#undef NODEBUG
#include <cassert>

int main()
{
  using namespace Crails;
  using namespace std;

  const SharedVars vars{
    {"valueA", "const char*"},
    {"valueB", std::string_view("string_view")},
    {"valueC", std::string("string")},
    {"valueD", 42}
  };

  assert(cast<const char*>(vars, "valueA") == "const char*");
  assert(cast<string_view>(vars, "valueB") == "string_view");
  assert(cast<string>(vars, "valueC") == "string");
  assert(cast<int>(vars, "valueD") == 42);


  // Crails::cast throw out_of_range when asked for non-existing key
  try
  {
    cast<string_view>(vars, "valueZ");
  }
  catch (std::out_of_range) {}
  catch (...) { assert(false); }

  // Crails::cast supports providing a default value
  assert(cast<string_view>(vars, "valueZ", "kek") == "kek");

  // Crails::cast throw runtime_error when asked for the wrong type
  try
  {
    cast<int>(vars, "valueA");
    assert(false);
  }
  catch (std::runtime_error) {}
  catch (...) { assert(false); }

  return 0;
}


