#pragma once
#include <string_view>

namespace nutsloop {

template <int R, int G, int B> [[nodiscard]] ansi::style ansi::rgb() const {
  static_assert(0 <= R && R <= 255, "ansi::rgb<R,G,B> - R must be in [0,255]");
  static_assert(0 <= G && G <= 255, "ansi::rgb<R,G,B> - G must be in [0,255]");
  static_assert(0 <= B && B <= 255, "ansi::rgb<R,G,B> - B must be in [0,255]");
  return style{text_, std::array{R, G, B}};
}

} // namespace nutsloop