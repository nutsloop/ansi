#include "../../include/ansi.h++"

namespace nutsloop {

ansi::style ansi::stylish() const { return style{text_}; }

} // namespace nutsloop