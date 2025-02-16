# libcrails-any - A C++ library

The `libcrails-any` C++ library provides simple tools for casting `std::any`
with commonly needed features:

- Fallback to a default value,
- Safe casting of multiple string type to another (std::string, std::string_view, const char),
- Logging or throwing exception on cast failure, with type information to help in debugging the issue.
