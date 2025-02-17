#pragma once
#include <string_view>
#include <typeinfo>

namespace Crails
{
  class Typename : public std::string_view
  {
    bool ownership = true;
  public:
    Typename(const std::type_info& input);
    Typename(const Typename&) = delete;
    Typename(Typename&& src);
    ~Typename();
  };
}
