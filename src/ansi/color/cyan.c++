#include "../../../include/ansi.h++"

namespace nutsloop {

ansi::style ansi::cyan() const { return style{text_, {ANSI_CODE::CYAN}}; }

ansi::style ansi::bright_cyan() const { return style{text_, {ANSI_CODE::BRIGHT_CYAN}}; }

} // namespace nutsloop