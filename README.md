# ansi

A modern C++23 library for beautiful terminal styling.

```cpp
#include "ansi.h++"
using namespace nutsloop;

std::cout << "Hello"_.red().bold() << " " << "World"_.green().underline() << std::endl;
```

## Features

- **Zero dependencies** — Pure C++ standard library
- **Fluent API** — Chain methods naturally: `.red().bold().underline()`
- **User-defined literals** — Write `"text"_` instead of `ansi{"text"}`
- **Complete color support** — 8/16, 256, RGB, and hex colors
- **All text styles** — Bold, italic, underline variants, strikethrough, and more
- **Hyperlinks** — Clickable terminal links (OSC 8)
- **Terminal detection** — Auto-detect color capabilities
- **Modern C++** — Requires C++23, uses `std::format`

## Installation

### Meson (recommended)

```meson
ansi_dep = dependency('ansi', fallback: ['ansi', 'ansi_dep'])
```

### Manual

```bash
meson setup build
meson compile -C build
meson install -C build
```

## Quick Start

```cpp
#include "ansi.h++"
#include <iostream>

using namespace nutsloop;

int main() {
  // Using literals (recommended)
  std::cout << "Error: "_.red().bold() << "Something went wrong" << std::endl;
  std::cout << "Success"_.green() << std::endl;

  // Using constructor
  std::cout << ansi{"Warning"}.yellow().italic() << std::endl;

  // With std::format
  ansi message("Status: {} items processed", 42);
  std::cout << message.cyan() << std::endl;
}
```

## Demo executable

The `bin/` target is a demo and is not installed by default. Enable it explicitly:

```bash
meson setup build -Dbuild_demo=true
meson compile -C build
./build/bin/ansi_
```

## Colors

### Named Colors (8/16)

```cpp
"text"_.black()          "text"_.bright_black()
"text"_.red()            "text"_.bright_red()
"text"_.green()          "text"_.bright_green()
"text"_.yellow()         "text"_.bright_yellow()
"text"_.blue()           "text"_.bright_blue()
"text"_.magenta()        "text"_.bright_magenta()
"text"_.cyan()           "text"_.bright_cyan()
"text"_.white()          "text"_.bright_white()
```

### 256 Colors

```cpp
"text"_.color256(208)        // Runtime value
"text"_.color256<208>()      // Compile-time (validated)
```

### RGB (True Color)

```cpp
"text"_.rgb({255, 128, 0})       // Runtime
"text"_.rgb<255, 128, 0>()       // Compile-time
```

### Hex Colors

```cpp
"text"_.hex("#FF8000")       // 6-digit
"text"_.hex("#F80")          // 3-digit shorthand
```

## Backgrounds

All color methods have background equivalents:

```cpp
"text"_.red().white_background()
"text"_.green().rgb_background({30, 30, 30})
"text"_.blue().hex_background("#1a1a1a")
"text"_.cyan().color256_background(236)
```

## Text Styles

### Basic Styles

```cpp
"text"_.red().bold()
"text"_.red().dim()
"text"_.red().italic()
"text"_.red().blink()
"text"_.red().reverse()
"text"_.red().hidden()
"text"_.red().strike_through()
"text"_.red().overline()
```

### Underline Variants

```cpp
"text"_.red().underline()           // Single
"text"_.red().double_underline()    // Double
"text"_.red().curly_underline()     // Wavy/curly
"text"_.red().dotted_underline()    // Dotted
"text"_.red().dashed_underline()    // Dashed
```

### Underline Colors

```cpp
"text"_.white().underline().underline_color({255, 0, 0})
"text"_.white().curly_underline().underline_color<255, 0, 0>()
"text"_.white().underline().underline_hex("#FF0000")
"text"_.white().underline().underline_color256(196)
```

### Style Removal

Remove individual styles without full reset:

```cpp
"text"_.red().bold().italic().no_bold()    // Keeps italic
"text"_.red().underline().no_underline()
"text"_.red().italic().no_italic()
// Also: no_dim, no_blink, no_reverse, no_hidden, no_strike_through, no_overline
```

## Hyperlinks

Create clickable links in supported terminals:

```cpp
"Click here"_.blue().underline().hyperlink("https://github.com")
"Documentation"_.cyan().hyperlink("https://docs.example.com")
```

## Advanced Usage

### No Color (Plain Text)

```cpp
"text"_.stylish().bold()    // Bold without foreground color
```

### Get ANSI Codes Only

```cpp
auto style = "text"_.red().bold();
std::string codes = style.codes();  // "\033[31;1m"
```

### Output Without Reset

```cpp
std::string no_reset = "red text"_.red().str_no_reset();
// Color continues until explicit reset
```

### Parent Style Restoration

Restore parent styling after embedded colored text:

```cpp
auto parent = ""_.black().rgb_background({255, 255, 255});
std::string inner = "colored"_.red().str(parent);  // Restores to parent after

ansi message("Hello {} world", inner);
std::cout << message.black().rgb_background({255, 255, 255}) << std::endl;
```

### Clear Methods

```cpp
style.clear_foreground()      // Remove foreground color
style.clear_background()      // Remove background color
style.clear_styles()          // Remove bold, italic, etc.
style.clear_underline_color() // Remove underline color
style.clear_hyperlink()       // Remove hyperlink
style.clear_all()             // Remove everything
```

## Terminal Detection

Detect terminal capabilities at runtime:

```cpp
#include "terminal.h++"
using namespace nutsloop;

// Check color support level
switch (terminal::detect_color_support()) {
  case terminal::color_support::NONE:       /* No colors */       break;
  case terminal::color_support::BASIC:      /* 8/16 colors */     break;
  case terminal::color_support::COLOR_256:  /* 256 colors */      break;
  case terminal::color_support::TRUE_COLOR: /* 24-bit RGB */      break;
}

// Convenience checks
if (terminal::supports_true_color()) {
  std::cout << "logo"_.rgb<255, 100, 0>() << std::endl;
} else {
  std::cout << "logo"_.yellow() << std::endl;
}

// Hyperlink support
if (terminal::supports_hyperlinks()) {
  std::cout << "link"_.blue().hyperlink("https://...") << std::endl;
}

// Force specific mode (for testing)
terminal::force_color_support(terminal::color_support::BASIC);
terminal::reset_color_support();  // Back to auto-detect
```

### Environment Variables

The library respects standard conventions:

| Variable | Effect |
|----------|--------|
| `NO_COLOR` | Disables all colors |
| `FORCE_COLOR=1/2/3` | Force basic/256/truecolor |
| `COLORTERM=truecolor` | Enable true color |
| `TERM` | Terminal type detection |

## Requirements

- C++23 compiler (Clang 17+, GCC 13+, MSVC 19.36+)
- Meson build system (optional)

## License

Apache License 2.0

---

<p align="center">
  <code>"Made with"_.white() << " " << "love"_.red().bold()</code>
</p>
