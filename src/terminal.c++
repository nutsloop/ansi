#include "../include/terminal.h++"
#include <algorithm>
#include <array>

namespace nutsloop {

std::string_view terminal::get_env(const char* name) {
  const char* value = std::getenv(name);
  return value ? std::string_view{value} : std::string_view{};
}

terminal::color_support terminal::detect_color_support() {
  if (support_forced_) {
    return cached_support_;
  }
  if (!support_detected_) {
    cached_support_ = detect_();
    support_detected_ = true;
  }
  return cached_support_;
}

bool terminal::supports_color() {
  return detect_color_support() >= color_support::BASIC;
}

bool terminal::supports_256_colors() {
  return detect_color_support() >= color_support::COLOR_256;
}

bool terminal::supports_true_color() {
  return detect_color_support() >= color_support::TRUE_COLOR;
}

bool terminal::supports_hyperlinks() {
  if (!hyperlinks_detected_) {
    hyperlinks_supported_ = detect_hyperlinks_();
    hyperlinks_detected_ = true;
  }
  return hyperlinks_supported_;
}

void terminal::force_color_support(color_support level) {
  cached_support_ = level;
  support_forced_ = true;
}

void terminal::reset_color_support() {
  support_forced_ = false;
  support_detected_ = false;
}

terminal::color_support terminal::detect_() {
  // Check NO_COLOR first (https://no-color.org/)
  if (!get_env("NO_COLOR").empty()) {
    return color_support::NONE;
  }

  // Check FORCE_COLOR
  auto force_color = get_env("FORCE_COLOR");
  if (!force_color.empty()) {
    if (force_color == "0") return color_support::NONE;
    if (force_color == "1") return color_support::BASIC;
    if (force_color == "2") return color_support::COLOR_256;
    if (force_color == "3") return color_support::TRUE_COLOR;
    return color_support::TRUE_COLOR; // Any truthy value
  }

  // Check COLORTERM for true color
  auto colorterm = get_env("COLORTERM");
  if (colorterm == "truecolor" || colorterm == "24bit") {
    return color_support::TRUE_COLOR;
  }

  // Check specific terminal programs known to support true color
  auto term_program = get_env("TERM_PROGRAM");
  static constexpr std::array truecolor_terminals = {
    std::string_view{"iTerm.app"},
    std::string_view{"Apple_Terminal"},
    std::string_view{"Hyper"},
    std::string_view{"vscode"},
  };
  for (auto term : truecolor_terminals) {
    if (term_program == term) {
      return color_support::TRUE_COLOR;
    }
  }

  // Check Windows Terminal
  if (!get_env("WT_SESSION").empty()) {
    return color_support::TRUE_COLOR;
  }

  // Check TERM variable
  auto term = get_env("TERM");
  if (term.empty() || term == "dumb") {
    return color_support::NONE;
  }

  // Check for 256-color or truecolor in TERM
  if (term.find("256color") != std::string_view::npos ||
      term.find("256") != std::string_view::npos) {
    return color_support::COLOR_256;
  }

  if (term.find("truecolor") != std::string_view::npos ||
      term.find("24bit") != std::string_view::npos ||
      term.find("direct") != std::string_view::npos) {
    return color_support::TRUE_COLOR;
  }

  // Known terminals that support at least 256 colors
  static constexpr std::array color256_terms = {
    std::string_view{"xterm"},
    std::string_view{"screen"},
    std::string_view{"tmux"},
    std::string_view{"rxvt"},
    std::string_view{"linux"},
    std::string_view{"cygwin"},
    std::string_view{"ansi"},
    std::string_view{"vt100"},
    std::string_view{"vt220"},
  };

  for (auto t : color256_terms) {
    if (term.find(t) != std::string_view::npos) {
      return color_support::COLOR_256;
    }
  }

  // Default to basic color if TERM is set to something
  return color_support::BASIC;
}

bool terminal::detect_hyperlinks_() {
  // Most modern terminals support OSC 8 hyperlinks
  // Check for known supporting terminals

  auto term_program = get_env("TERM_PROGRAM");
  static constexpr std::array hyperlink_terminals = {
    std::string_view{"iTerm.app"},
    std::string_view{"Hyper"},
    std::string_view{"vscode"},
  };

  for (auto term : hyperlink_terminals) {
    if (term_program == term) {
      return true;
    }
  }

  // Windows Terminal supports hyperlinks
  if (!get_env("WT_SESSION").empty()) {
    return true;
  }

  // VTE-based terminals (GNOME Terminal, Tilix, etc.)
  if (!get_env("VTE_VERSION").empty()) {
    return true;
  }

  // Kitty terminal
  if (!get_env("KITTY_WINDOW_ID").empty()) {
    return true;
  }

  // WezTerm
  if (!get_env("WEZTERM_PANE").empty()) {
    return true;
  }

  // Konsole
  if (!get_env("KONSOLE_VERSION").empty()) {
    return true;
  }

  // Default: assume hyperlinks work if we have true color support
  // (most modern terminals that support true color also support hyperlinks)
  return detect_color_support() >= color_support::TRUE_COLOR;
}

} // namespace nutsloop
