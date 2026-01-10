#pragma once

namespace nutsloop {

template <typename... Args> ansi::ansi(std::format_string<Args...> fmt, Args &&...args) {
  text_ = std::vformat(fmt.get(), std::make_format_args(args...));
}

} // namespace nutsloop