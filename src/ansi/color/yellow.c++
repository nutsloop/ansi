#include "../../../include/ansi.h++"

namespace nutsloop {

ansi::style ansi::yellow() const { return style{text_, {ANSI_CODE::YELLOW}}; }

ansi::style ansi::bright_yellow() const { return style{text_, {ANSI_CODE::BRIGHT_YELLOW}}; }

} // namespace nutsloop