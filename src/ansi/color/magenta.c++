#include "../../../include/ansi.h++"

namespace nutsloop {

ansi::style ansi::magenta() const { return style{text_, {ANSI_CODE::MAGENTA}}; }

ansi::style ansi::bright_magenta() const { return style{text_, {ANSI_CODE::BRIGHT_MAGENTA}}; }

} // namespace nutsloop