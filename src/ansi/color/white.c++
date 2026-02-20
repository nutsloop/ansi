#include "../../../include/ansi.h++"

namespace nutsloop {

ansi::style ansi::white() const { return style{text_, {ANSI_CODE::WHITE}}; }

ansi::style ansi::bright_white() const { return style{text_, {ANSI_CODE::BRIGHT_WHITE}}; }

} // namespace nutsloop