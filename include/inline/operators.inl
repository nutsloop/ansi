#pragma once
#include <format>

namespace nutsloop {

template <typename... Args>
[[nodiscard]] ansi ansi::operator()(std::format_string<Args...> fmt, Args &&...args) {
  return ansi(std::vformat(fmt.get(), std::make_format_args(args...)));
}

// static_cast<std::string>(ansi) or std::string(ansi).
inline ansi::operator std::string() const { return text_; }

inline std::ostream &operator<<(std::ostream &os, const ansi &a) {
  os << a.text_;
  return os;
}

} // namespace nutsloop