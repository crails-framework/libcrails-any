#ifndef  SHARED_VARS_STRING_CAST_HPP
# define SHARED_VARS_STRING_CAST_HPP

# include <string_view>
# include <string>
# include <any>

# ifndef TWILIDOC

namespace Crails
{
  template<>
  struct Any<std::string>
  {
    static std::string cast(const std::any& var)
    {
      const std::type_info& type = var.type();

      if (type == typeid(const char*))
        return std::any_cast<const char*>(var);
      if (type == typeid(std::string_view))
        return std::any_cast<std::string_view>(var).data();
      if (type == typeid(const std::string))
        return std::any_cast<const std::string>(var);
      return std::any_cast<std::string>(var);
    }
  };

  template<>
  struct Any<const std::string>
  {
    static std::string cast(const std::any& var)
    {
      const std::type_info& type = var.type();

      if (type == typeid(const char*))
        return std::any_cast<const char*>(var);
      if (type == typeid(std::string_view))
        return std::any_cast<std::string_view>(var).data();
      if (type == typeid(std::string))
        return std::any_cast<const std::string>(var);
      return std::any_cast<const std::string>(var);
    }
  };

  template<>
  struct Any<std::string_view>
  {
    static std::string_view cast(const std::any& var)
    {
      const std::type_info& type = var.type();

      if (type == typeid(const char*))
        return std::any_cast<const char*>(var);
      if (type == typeid(std::string))
      {
        const std::string* ptr = std::any_cast<std::string>(&var);
        return std::string_view(ptr->c_str(), ptr->length());
      }
      if (type == typeid(const std::string))
      {
        const std::string* ptr = std::any_cast<const std::string>(&var);
        return std::string_view(ptr->c_str(), ptr->length());
      } 
      return std::any_cast<std::string_view>(var);
    }
  };

  template<>
  struct Any<const char*>
  {
    static const char* cast(const std::any& var)
    {
      const std::type_info& type = var.type();

      if (type == typeid(std::string_view))
        return std::any_cast<std::string_view>(var).data();
      if (type == typeid(std::string))
        return std::any_cast<std::string>(&var)->c_str();
      return std::any_cast<const char*>(var);
    }
  };
}

# endif
#endif
