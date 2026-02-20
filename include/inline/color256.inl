#pragma once

namespace nutsloop {

template <int COLOR> [[nodiscard]] ansi::style ansi::color256() const {
  static_assert(0 <= COLOR && COLOR <= 255, "ansi::color256<COLOR> - COLOR must be in [0,255]");

  return style{text_, COLOR};
}

} // namespace nutsloop