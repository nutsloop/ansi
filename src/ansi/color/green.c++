#include "../../../include/ansi.h++"

namespace nutsloop {

ansi::style ansi::green() const { return style{text_, {ANSI_CODE::GREEN}}; }

ansi::style ansi::bright_green() const { return style{text_, {ANSI_CODE::BRIGHT_GREEN}}; }

} // namespace nutsloop