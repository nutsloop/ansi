#include "../../../include/ansi.h++"

namespace nutsloop {

ansi::style ansi::hex(std::string_view hex_str) const {
  auto parsed = style::parse_hex_(hex_str);
  if (parsed) {
    return style{text_, *parsed};
  }
  // Return unstyled if invalid hex
  return style{text_};
}

} // namespace nutsloop
