#include "ansi.h++"
#include "terminal.h++"
#include <iostream>

using namespace nutsloop;

int main() {
  // Terminal capability detection
  std::cout << "=== Terminal Capabilities ===" << std::endl;
  std::cout << "Color support: ";
  switch (terminal::detect_color_support()) {
  case terminal::color_support::NONE:
    std::cout << "none";
    break;
  case terminal::color_support::BASIC:
    std::cout << "basic (8/16)";
    break;
  case terminal::color_support::COLOR_256:
    std::cout << "256 colors";
    break;
  case terminal::color_support::TRUE_COLOR:
    std::cout << "true color (24-bit)";
    break;
  }
  std::cout << std::endl;
  std::cout << "Hyperlinks: " << (terminal::supports_hyperlinks() ? "yes" : "no") << std::endl;
  std::cout << std::endl;

  // Create parent style first, then use str(parent) to restore after embedded colors
  std::cout << "=== Parent Style Restoration ===" << std::endl;
  auto parent = ""_.black().rgb_background({255, 255, 255});
  std::string text_green = "green"_.green().str(parent);
  std::string text_blue = "blue"_.blue().str(parent);
  ansi hello_world("hello world {} {}!!!", text_green, text_blue);
  std::cout << hello_world.black().rgb_background({255, 255, 255}) << std::endl;
  std::cout << std::endl;

  // Basic colors
  std::cout << "=== Basic Colors ===" << std::endl;
  std::cout << "hello_world"_.blue() << std::endl;
  std::cout << "hello_world"_.bright_blue() << std::endl;
  std::cout << "hello_world"_.green() << std::endl;
  std::cout << "hello_world"_.cyan() << std::endl;
  std::cout << std::endl;

  // Hex colors (new!)
  std::cout << "=== Hex Colors ===" << std::endl;
  std::cout << "hello"_.hex("#FF5500").bold() << " (#FF5500)" << std::endl;
  std::cout << "hello"_.hex("#0AF").italic() << " (#0AF short form)" << std::endl;
  std::cout << "hello"_.green().hex_background("#333333") << " (hex background)" << std::endl;
  std::cout << std::endl;

  // Underline styles
  std::cout << "=== Underline Styles ===" << std::endl;
  std::cout << "single underline"_.red().underline() << std::endl;
  std::cout << "double underline"_.green().double_underline() << std::endl;
  std::cout << "curly underline"_.blue().curly_underline() << std::endl;
  std::cout << "dotted underline"_.magenta().dotted_underline() << std::endl;
  std::cout << "dashed underline"_.cyan().dashed_underline() << std::endl;
  std::cout << std::endl;

  // Underline colors
  std::cout << "=== Underline Colors ===" << std::endl;
  std::cout << "red underline"_.white().underline().underline_color({255, 0, 0}) << std::endl;
  std::cout << "green curly"_.white().curly_underline().underline_color<0, 255, 0>() << std::endl;
  std::cout << "hex underline"_.white().underline().underline_hex("#FF00FF") << std::endl;
  std::cout << "256 underline"_.white().underline().underline_color256(208) << std::endl;
  std::cout << std::endl;

  // Individual style removal
  std::cout << "=== Style Removal ===" << std::endl;
  std::cout << "bold then no_bold: " << "text"_.red().bold().no_bold() << std::endl;
  std::cout << "italic then no_italic: " << "text"_.green().italic().no_italic() << std::endl;
  std::cout << "underline then no_underline: " << "text"_.blue().underline().no_underline()
            << std::endl;
  std::cout << std::endl;

  // Hyperlinks (new!)
  std::cout << "=== Hyperlinks ===" << std::endl;
  std::cout << "Click me"_.blue().underline().hyperlink("https://github.com") << std::endl;
  std::cout << "Anthropic"_.bright_cyan().bold().hyperlink("https://anthropic.com") << std::endl;
  std::cout << std::endl;

  // Combined styles
  std::cout << "=== Combined Styles ===" << std::endl;
  std::cout << "hello"_.hex("#FF6600").curly_underline().bold().hyperlink("https://example.com")
            << std::endl;
  std::cout << ansi{"styled"}.red().rgb_background({0, 0, 255}).bold().double_underline() << std::endl;
  std::cout << std::endl;

  // Other styles
  std::cout << "=== Other Styles ===" << std::endl;
  std::cout << "hello"_.color256<238>().blue_background().strike_through() << std::endl;
  std::cout << "hello"_.color256<238>().blue_background().overline() << std::endl;
  std::cout << "hello"_.color256<238>().blue_background().reverse() << std::endl;
  std::cout << "hello"_.color256<35>().white_background().blink() << std::endl;

  return 0;
}
