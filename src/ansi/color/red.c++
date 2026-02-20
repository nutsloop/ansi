#include "../../../include/ansi.h++"

namespace nutsloop {

ansi::style ansi::red() const { return style{text_, {ANSI_CODE::RED}}; }

ansi::style ansi::bright_red() const { return style{text_, {ANSI_CODE::BRIGHT_RED}}; }

} // namespace nutsloop