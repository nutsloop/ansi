#include "../../../include/ansi.h++"

namespace nutsloop {

[[nodiscard]] ansi::style ansi::color256(int color) const {
  if (color < 0)
    color = 0;
  else if (color > 255)
    color = 255;
  return style{text_, color};
}

} // namespace nutsloop