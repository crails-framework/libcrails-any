#include <crails/shared_vars.hpp>
#include <stdexcept>

#undef NODEBUG
#include <cassert>

int main()
{
  using namespace Crails;
  using namespace std;

  // cast
  {
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
  }

  // cast_or
  {
    const SharedVars data{
      {"string", std::string("valueA")},
      {"string_view", std::string_view("valueB")},
      {"const char*", "valueC"},
      {"number", 42},
      {"float", 21.12},
      {"bool", true}
    };

    // Any string to std::string
    assert(Crails::cast_or<string>(data, "string", "kek") == "valueA");
    assert(Crails::cast_or<string>(data, "string_view", "kek") == "valueB");
    assert(Crails::cast_or<string>(data, "const char*", "kek") == "valueC");

    // Any string to std::string_view
    assert(Crails::cast_or<string_view>(data, "string", "kek") == "valueA");
    assert(Crails::cast_or<string_view>(data, "string_view", "kek") == "valueB");
    assert(Crails::cast_or<string_view>(data, "const char*", "kek") == "valueC");

    // Scalars
    assert(Crails::cast_or<int>(data, "number", 12) == 42);
    assert(Crails::cast_or<double>(data, "float", 12) == 21.12);
    assert(Crails::cast_or<bool>(data, "bool", false) == true);

    // Fallback to default value if cast type is wrong
    assert(Crails::cast_or<double>(data, "number", 42.24) == 42.24);

    // Fallback to default value if no matching variable found
    assert(Crails::cast_or<string>(data, "jagon", "sucer") == "sucer");
  }

  return 0;
}


