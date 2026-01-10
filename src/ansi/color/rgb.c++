#include "../../../include/ansi.h++"

namespace nutsloop {

ansi::style ansi::rgb(std::array<int, 3> rgb) const {
  // Clamp to [0,255] to avoid invalid escape sequences
  for (int &v : rgb) {
    if (v < 0)
      v = 0;
    else if (v > 255)
      v = 255;
  }
  return style{text_, rgb};
}

} // namespace nutsloop