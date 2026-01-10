#include "../../../include/ansi.h++"

namespace nutsloop {

ansi::style ansi::black() const { return style{text_, {ANSI_CODE::BLACK}}; }

ansi::style ansi::bright_black() const { return style{text_, {ANSI_CODE::BRIGHT_BLACK}}; }

} // namespace nutsloop