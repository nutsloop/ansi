#include "../../../include/ansi.h++"

namespace nutsloop {

ansi::style ansi::blue() const { return style{text_, {ANSI_CODE::BLUE}}; }

ansi::style ansi::bright_blue() const { return style{text_, {ANSI_CODE::BRIGHT_BLUE}}; }

} // namespace nutsloop