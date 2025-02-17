#include <crails/any_cast.hpp>

#undef NODEBUG
#include <cassert>

int main()
{
  using namespace Crails;
  using namespace std;

  // indiscriminately casts std::string, std::string_view and const char* to std::string
  {
    const string_view a("coucou");
    const string b("coucou");

    any constchar_value = "coucou";
    any stringview_value = string_view("coucou");
    any string_value = string("coucou");
    any const_stringview_value = a;
    any const_string_value = b;

    assert(Any<string>::cast(constchar_value) == "coucou");
    assert(Any<string>::cast(stringview_value) == "coucou");
    assert(Any<string>::cast(string_value) == "coucou");
    assert(Any<string>::cast(const_stringview_value) == "coucou");
    assert(Any<string>::cast(const_string_value) == "coucou");

    assert(Any<string_view>::cast(constchar_value) == "coucou");
    assert(Any<string_view>::cast(stringview_value) == "coucou");
    assert(Any<string_view>::cast(string_value) == "coucou");
    assert(Any<string_view>::cast(const_stringview_value) == "coucou");
    assert(Any<string_view>::cast(const_string_value) == "coucou");

    assert(Any<const char*>::cast(constchar_value) == "coucou");
    assert(Any<const char*>::cast(stringview_value) == "coucou");
    assert(Any<const char*>::cast(string_value) == "coucou");
    assert(Any<const char*>::cast(const_stringview_value) == "coucou");
    assert(Any<const char*>::cast(const_string_value) == "coucou");
  }

  return 0;
}

