#pragma once
#include <string_view>

namespace nutsloop {

/**
 * @brief User-defined literal for creating an ansi instance from a string literal.
 *
 * This operator allows you to write a string literal with a trailing underscore
 * to directly construct a nutsloop::ansi object. The ansi object can then be styled
 * with the available member functions (e.g., red(), bold(), underline()).
 *
 * Example:
 * @code
 * using namespace nutsloop;
 * std::cout << "hello"_.red().bold() << "\n";
 * @endcode
 */
inline ansi operator""_(const char *str, const std::size_t len) {
  return ansi{std::string_view(str, len)};
}

} // namespace nutsloop