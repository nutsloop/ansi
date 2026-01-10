#pragma once
#include <cstdlib>
#include <string>
#include <string_view>

namespace nutsloop {

class terminal {
public:
  enum class color_support {
    NONE,       // No color support
    BASIC,      // 8/16 colors
    COLOR_256,  // 256 colors
    TRUE_COLOR, // 24-bit RGB
  };

  // Detect terminal capabilities (cached after first call)
  static color_support detect_color_support();

  // Check specific capabilities
  static bool supports_color();
  static bool supports_256_colors();
  static bool supports_true_color();
  static bool supports_hyperlinks();

  // Force a specific color mode (for testing or user preference)
  static void force_color_support(color_support level);
  static void reset_color_support();

  // Get environment variable (wrapper for testability)
  static std::string_view get_env(const char* name);

private:
  static color_support detect_();
  static bool detect_hyperlinks_();

  static inline color_support cached_support_ = color_support::NONE;
  static inline bool support_detected_ = false;
  static inline bool support_forced_ = false;

  static inline bool hyperlinks_detected_ = false;
  static inline bool hyperlinks_supported_ = false;
};

} // namespace nutsloop
