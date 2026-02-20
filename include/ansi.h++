#pragma once
#include <algorithm>
#include <array>
#include <cstdlib>
#include <format>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

namespace nutsloop {

class ansi {
  enum class ANSI_CODE {
    BLACK = 30,
    BRIGHT_BLACK = 90,
    BLACK_BACKGROUND = 40,
    BRIGHT_BLACK_BACKGROUND = 100,
    BLUE = 34,
    BRIGHT_BLUE = 94,
    BLUE_BACKGROUND = 44,
    BRIGHT_BLUE_BACKGROUND = 104,
    CYAN = 36,
    BRIGHT_CYAN = 96,
    CYAN_BACKGROUND = 46,
    BRIGHT_CYAN_BACKGROUND = 106,
    GREEN = 32,
    BRIGHT_GREEN = 92,
    GREEN_BACKGROUND = 42,
    BRIGHT_GREEN_BACKGROUND = 102,
    MAGENTA = 35,
    BRIGHT_MAGENTA = 95,
    MAGENTA_BACKGROUND = 45,
    BRIGHT_MAGENTA_BACKGROUND = 105,
    RED = 31,
    BRIGHT_RED = 91,
    RED_BACKGROUND = 41,
    BRIGHT_RED_BACKGROUND = 101,
    WHITE = 37,
    BRIGHT_WHITE = 97,
    WHITE_BACKGROUND = 47,
    BRIGHT_WHITE_BACKGROUND = 107,
    YELLOW = 33,
    BRIGHT_YELLOW = 93,
    YELLOW_BACKGROUND = 43,
    BRIGHT_YELLOW_BACKGROUND = 103,
    // styles
    BOLD = 1,
    BLINK = 5,
    DIM = 2,
    HIDDEN = 8,
    ITALIC = 3,
    OVERLINE = 53,
    REVERSE = 7,
    STRIKETHROUGH = 9,
    UNDERLINE = 4,
    DOUBLE_UNDERLINE = 21,
    // style resets
    NO_BOLD_DIM = 22,
    NO_ITALIC = 23,
    NO_UNDERLINE = 24,
    NO_BLINK = 25,
    NO_REVERSE = 27,
    NO_HIDDEN = 28,
    NO_STRIKETHROUGH = 29,
    NO_OVERLINE = 55,
  };

  // Extended underline styles (use SGR 4:N format)
  enum class UNDERLINE_STYLE {
    NONE = 0,
    SINGLE = 1,
    DOUBLE = 2,
    CURLY = 3,
    DOTTED = 4,
    DASHED = 5,
  };

  using ansi_vec = std::vector<ANSI_CODE>;

public:
  struct style {

    style &bold() {
      if (std::ranges::find(codes_, ANSI_CODE::BOLD) == codes_.end()) {
        codes_.push_back(ANSI_CODE::BOLD);
      }
      return *this;
    }

    style &blink() {
      if (std::ranges::find(codes_, ANSI_CODE::BLINK) == codes_.end()) {
        codes_.push_back(ANSI_CODE::BLINK);
      }
      return *this;
    }

    style &dim() {
      if (std::ranges::find(codes_, ANSI_CODE::DIM) == codes_.end()) {
        codes_.push_back(ANSI_CODE::DIM);
      }
      return *this;
    }

    style &hidden() {
      if (std::ranges::find(codes_, ANSI_CODE::HIDDEN) == codes_.end()) {
        codes_.push_back(ANSI_CODE::HIDDEN);
      }
      return *this;
    }

    style &italic() {
      if (std::ranges::find(codes_, ANSI_CODE::ITALIC) == codes_.end()) {
        codes_.push_back(ANSI_CODE::ITALIC);
      }
      return *this;
    }

    style &overline() {
      if (std::ranges::find(codes_, ANSI_CODE::OVERLINE) == codes_.end()) {
        codes_.push_back(ANSI_CODE::OVERLINE);
      }
      return *this;
    }

    style &reverse() {
      if (std::ranges::find(codes_, ANSI_CODE::REVERSE) == codes_.end()) {
        codes_.push_back(ANSI_CODE::REVERSE);
      }
      return *this;
    }

    style &strike_through() {
      if (std::ranges::find(codes_, ANSI_CODE::STRIKETHROUGH) == codes_.end()) {
        codes_.push_back(ANSI_CODE::STRIKETHROUGH);
      }
      return *this;
    }

    style &underline() {
      clear_underline_();
      codes_.push_back(ANSI_CODE::UNDERLINE);
      return *this;
    }

    // Individual style removal methods
    style &no_bold() {
      std::erase(codes_, ANSI_CODE::BOLD);
      std::erase(codes_, ANSI_CODE::DIM);
      if (std::ranges::find(codes_, ANSI_CODE::NO_BOLD_DIM) == codes_.end()) {
        codes_.push_back(ANSI_CODE::NO_BOLD_DIM);
      }
      return *this;
    }

    style &no_dim() {
      return no_bold(); // Same reset code (22) turns off both
    }

    style &no_italic() {
      std::erase(codes_, ANSI_CODE::ITALIC);
      if (std::ranges::find(codes_, ANSI_CODE::NO_ITALIC) == codes_.end()) {
        codes_.push_back(ANSI_CODE::NO_ITALIC);
      }
      return *this;
    }

    style &no_underline() {
      clear_underline_();
      underline_color_.reset();
      underline_color_256_.reset();
      if (std::ranges::find(codes_, ANSI_CODE::NO_UNDERLINE) == codes_.end()) {
        codes_.push_back(ANSI_CODE::NO_UNDERLINE);
      }
      return *this;
    }

    style &no_blink() {
      std::erase(codes_, ANSI_CODE::BLINK);
      if (std::ranges::find(codes_, ANSI_CODE::NO_BLINK) == codes_.end()) {
        codes_.push_back(ANSI_CODE::NO_BLINK);
      }
      return *this;
    }

    style &no_reverse() {
      std::erase(codes_, ANSI_CODE::REVERSE);
      if (std::ranges::find(codes_, ANSI_CODE::NO_REVERSE) == codes_.end()) {
        codes_.push_back(ANSI_CODE::NO_REVERSE);
      }
      return *this;
    }

    style &no_hidden() {
      std::erase(codes_, ANSI_CODE::HIDDEN);
      if (std::ranges::find(codes_, ANSI_CODE::NO_HIDDEN) == codes_.end()) {
        codes_.push_back(ANSI_CODE::NO_HIDDEN);
      }
      return *this;
    }

    style &no_strike_through() {
      std::erase(codes_, ANSI_CODE::STRIKETHROUGH);
      if (std::ranges::find(codes_, ANSI_CODE::NO_STRIKETHROUGH) == codes_.end()) {
        codes_.push_back(ANSI_CODE::NO_STRIKETHROUGH);
      }
      return *this;
    }

    style &no_overline() {
      std::erase(codes_, ANSI_CODE::OVERLINE);
      if (std::ranges::find(codes_, ANSI_CODE::NO_OVERLINE) == codes_.end()) {
        codes_.push_back(ANSI_CODE::NO_OVERLINE);
      }
      return *this;
    }

    style &double_underline() {
      clear_underline_();
      underline_style_ = UNDERLINE_STYLE::DOUBLE;
      return *this;
    }

    style &curly_underline() {
      clear_underline_();
      underline_style_ = UNDERLINE_STYLE::CURLY;
      return *this;
    }

    style &dotted_underline() {
      clear_underline_();
      underline_style_ = UNDERLINE_STYLE::DOTTED;
      return *this;
    }

    style &dashed_underline() {
      clear_underline_();
      underline_style_ = UNDERLINE_STYLE::DASHED;
      return *this;
    }

    // Underline color (RGB)
    style &underline_color(std::array<int, 3> rgb) {
      for (int &v : rgb) {
        if (v < 0) v = 0;
        else if (v > 255) v = 255;
      }
      underline_color_ = rgb;
      return *this;
    }

    template <int R, int G, int B> style &underline_color() {
      static_assert(0 <= R && R <= 255, "ansi::style::underline_color<R,G,B> - R must be in [0,255]");
      static_assert(0 <= G && G <= 255, "ansi::style::underline_color<R,G,B> - G must be in [0,255]");
      static_assert(0 <= B && B <= 255, "ansi::style::underline_color<R,G,B> - B must be in [0,255]");
      underline_color_ = std::array<int, 3>{R, G, B};
      return *this;
    }

    // Underline color (256-color)
    style &underline_color256(int color) {
      if (color < 0) color = 0;
      else if (color > 255) color = 255;
      underline_color_256_ = color;
      return *this;
    }

    template <int COLOR> style &underline_color256() {
      static_assert(0 <= COLOR && COLOR <= 255,
                    "ansi::style::underline_color256<COLOR> - COLOR must be in [0,255]");
      underline_color_256_ = COLOR;
      return *this;
    }

    // Underline color (hex)
    style &underline_hex(std::string_view hex) {
      auto rgb = parse_hex_(hex);
      if (rgb) {
        underline_color_ = *rgb;
      }
      return *this;
    }

    style &clear_underline_color() {
      underline_color_.reset();
      underline_color_256_.reset();
      return *this;
    }

    style &hyperlink(std::string_view url) {
      hyperlink_ = std::string{url};
      return *this;
    }

    style &clear_hyperlink() {
      hyperlink_.reset();
      return *this;
    }

    // Named background colors
    style &black_background() {
      set_background_(ANSI_CODE::BLACK_BACKGROUND);
      return *this;
    }
    style &bright_black_background() {
      set_background_(ANSI_CODE::BRIGHT_BLACK_BACKGROUND);
      return *this;
    }

    style &blue_background() {
      set_background_(ANSI_CODE::BLUE_BACKGROUND);
      return *this;
    }
    style &bright_blue_background() {
      set_background_(ANSI_CODE::BRIGHT_BLUE_BACKGROUND);
      return *this;
    }

    style &cyan_background() {
      set_background_(ANSI_CODE::CYAN_BACKGROUND);
      return *this;
    }
    style &bright_cyan_background() {
      set_background_(ANSI_CODE::BRIGHT_CYAN_BACKGROUND);
      return *this;
    }

    style &green_background() {
      set_background_(ANSI_CODE::GREEN_BACKGROUND);
      return *this;
    }
    style &bright_green_background() {
      set_background_(ANSI_CODE::BRIGHT_GREEN_BACKGROUND);
      return *this;
    }

    style &magenta_background() {
      set_background_(ANSI_CODE::MAGENTA_BACKGROUND);
      return *this;
    }
    style &bright_magenta_background() {
      set_background_(ANSI_CODE::BRIGHT_MAGENTA_BACKGROUND);
      return *this;
    }
    style &red_background() {
      set_background_(ANSI_CODE::RED_BACKGROUND);
      return *this;
    }
    style &bright_red_background() {
      set_background_(ANSI_CODE::BRIGHT_RED_BACKGROUND);
      return *this;
    }

    style &white_background() {
      set_background_(ANSI_CODE::WHITE_BACKGROUND);
      return *this;
    }
    style &bright_white_background() {
      set_background_(ANSI_CODE::BRIGHT_WHITE_BACKGROUND);
      return *this;
    }

    style &yellow_background() {
      set_background_(ANSI_CODE::YELLOW_BACKGROUND);
      return *this;
    }
    style &bright_yellow_background() {
      set_background_(ANSI_CODE::BRIGHT_YELLOW_BACKGROUND);
      return *this;
    }

    style &color256_background(int color) {
      // Clear any existing background
      std::erase_if(codes_, is_background_);
      rgb_background_.reset();
      // Set new 256-color background
      if (color < 0)
        color = 0;
      else if (color > 255)
        color = 255;
      color_256_background_ = color;
      return *this;
    }

    template <int COLOR> style &color256_background() {
      static_assert(0 <= COLOR && COLOR <= 255,
                    "ansi::style::color256_background<COLOR> - COLOR must be in [0,255]");
      // Clear any existing background
      std::erase_if(codes_, is_background_);
      rgb_background_.reset();
      // Set new 256-color background
      color_256_background_ = COLOR;
      return *this;
    }

    style &rgb_background(std::array<int, 3> rgb) {
      // Clear any existing background
      std::erase_if(codes_, is_background_);
      color_256_background_.reset();
      // Set new RGB background
      for (int &v : rgb) {
        if (v < 0)
          v = 0;
        else if (v > 255)
          v = 255;
      }
      rgb_background_ = rgb;
      return *this;
    }

    template <int R, int G, int B> style &rgb_background() {
      static_assert(0 <= R && R <= 255, "ansi::style::rgb_background<R,G,B> - R must be in [0,255]");
      static_assert(0 <= G && G <= 255, "ansi::style::rgb_background<R,G,B> - G must be in [0,255]");
      static_assert(0 <= B && B <= 255, "ansi::style::rgb_background<R,G,B> - B must be in [0,255]");
      // Clear any existing background
      std::erase_if(codes_, is_background_);
      color_256_background_.reset();
      // Set new RGB background
      rgb_background_ = std::array<int, 3>{R, G, B};
      return *this;
    }

    style &hex_background(std::string_view hex) {
      auto rgb = parse_hex_(hex);
      if (rgb) {
        rgb_background(*rgb);
      }
      return *this;
    }

    style &clear_background() {
      std::erase_if(codes_, is_background_);
      rgb_background_.reset();
      color_256_background_.reset();
      return *this;
    }

    style &clear_foreground() {
      std::erase_if(codes_, is_foreground_);
      rgb_.reset();
      color_256_.reset();
      return *this;
    }

    style &clear_styles() {
      std::erase_if(codes_, is_style_);
      underline_style_.reset();
      return *this;
    }

    style &clear_all() {
      codes_.clear();
      rgb_.reset();
      rgb_background_.reset();
      color_256_.reset();
      color_256_background_.reset();
      underline_style_.reset();
      underline_color_.reset();
      underline_color_256_.reset();
      hyperlink_.reset();
      return *this;
    }

    [[nodiscard]] std::string codes() const {
      bool has_codes = !codes_.empty() || color_256_ || rgb_ ||
                       color_256_background_ || rgb_background_ || underline_style_ ||
                       underline_color_ || underline_color_256_;
      if (!has_codes) {
        return {};
      }

      std::string result;
      result.reserve(32);
      result += "\033[";

      bool first = true;

      // Write style codes (bold, underline...)
      for (auto code : codes_) {
        if (!first) result += ';';
        result += std::to_string(static_cast<int>(code));
        first = false;
      }

      // Write extended underline style: 4:N (curly, dotted, dashed, double)
      if (underline_style_) {
        if (!first) result += ';';
        result += "4:";
        result += std::to_string(static_cast<int>(*underline_style_));
        first = false;
      }

      // Write 256-color foreground if present: 38;5;N
      if (color_256_ && !rgb_) {
        if (!first) result += ';';
        result += "38;5;";
        result += std::to_string(*color_256_);
        first = false;
      }

      // Write 256-color background if present: 48;5;N
      if (color_256_background_ && !rgb_background_) {
        if (!first) result += ';';
        result += "48;5;";
        result += std::to_string(*color_256_background_);
        first = false;
      }

      // Write RGB foreground if present: 38;2;R;G;B
      if (rgb_) {
        if (!first) result += ';';
        result += "38;2;";
        result += std::to_string((*rgb_)[0]);
        result += ';';
        result += std::to_string((*rgb_)[1]);
        result += ';';
        result += std::to_string((*rgb_)[2]);
        first = false;
      }

      // Write RGB background if present: 48;2;R;G;B
      if (rgb_background_) {
        if (!first) result += ';';
        result += "48;2;";
        result += std::to_string((*rgb_background_)[0]);
        result += ';';
        result += std::to_string((*rgb_background_)[1]);
        result += ';';
        result += std::to_string((*rgb_background_)[2]);
        first = false;
      }

      // Write underline color (256-color): 58:5:N
      if (underline_color_256_ && !underline_color_) {
        if (!first) result += ';';
        result += "58:5:";
        result += std::to_string(*underline_color_256_);
        first = false;
      }

      // Write underline color (RGB): 58:2:R:G:B
      if (underline_color_) {
        if (!first) result += ';';
        result += "58:2:";
        result += std::to_string((*underline_color_)[0]);
        result += ':';
        result += std::to_string((*underline_color_)[1]);
        result += ':';
        result += std::to_string((*underline_color_)[2]);
      }

      result += 'm';
      return result;
    }

    [[nodiscard]] std::string str() const {
      std::string escape = codes();
      std::string result;
      result.reserve(escape.size() + text_.size() + 32);

      if (hyperlink_) {
        result += "\033]8;;";
        result += *hyperlink_;
        result += "\033\\";
      }

      result += escape;
      result += text_;

      if (!escape.empty()) {
        result += "\033[0m";
      }

      if (hyperlink_) {
        result += "\033]8;;\033\\";
      }

      return result;
    }

    [[nodiscard]] std::string str(const style &restore) const {
      std::string escape = codes();
      std::string restore_codes = restore.codes();
      std::string result;
      result.reserve(escape.size() + text_.size() + restore_codes.size() + 32);

      if (hyperlink_) {
        result += "\033]8;;";
        result += *hyperlink_;
        result += "\033\\";
      }

      result += escape;
      result += text_;
      result += restore_codes;

      if (hyperlink_) {
        result += "\033]8;;\033\\";
      }

      return result;
    }

    [[nodiscard]] std::string str_no_reset() const {
      std::string escape = codes();
      std::string result;
      result.reserve(escape.size() + text_.size() + 32);

      if (hyperlink_) {
        result += "\033]8;;";
        result += *hyperlink_;
        result += "\033\\";
      }

      result += escape;
      result += text_;

      // Note: hyperlink is NOT closed in no_reset mode
      return result;
    }

    explicit operator std::string() const { return str(); }

    friend std::ostream &operator<<(std::ostream &os, const style &s) {
      os << s.str();
      return os;
    }

  private:
    // Only ansi can construct styles; users receive them from ansi methods.
    friend class ansi;

    explicit style(std::string text) noexcept : text_{std::move(text)}, codes_{} {}
    style(std::string text, ansi_vec codes) : text_{std::move(text)}, codes_{std::move(codes)} {}
    style(std::string text, std::array<int, 3> rgb) : text_{std::move(text)}, codes_{}, rgb_{rgb} {}
    style(std::string text, int color) : text_{std::move(text)}, codes_{} {
      if (color < 0)
        color = 0;
      else if (color > 255)
        color = 255;
      color_256_ = color;
    }

    std::string text_{};
    ansi_vec codes_{};
    std::optional<std::array<int, 3>> rgb_{};
    std::optional<std::array<int, 3>> rgb_background_{};
    std::optional<int> color_256_{};
    std::optional<int> color_256_background_{};
    std::optional<UNDERLINE_STYLE> underline_style_{};
    std::optional<std::array<int, 3>> underline_color_{};
    std::optional<int> underline_color_256_{};
    std::optional<std::string> hyperlink_{};

    void clear_underline_() {
      std::erase_if(codes_, [](ANSI_CODE c) {
        return c == ANSI_CODE::UNDERLINE || c == ANSI_CODE::DOUBLE_UNDERLINE;
      });
      underline_style_.reset();
    }

    void set_background_(const ANSI_CODE code) {
      // Remove any previously set background (named, 256, or RGB)
      std::erase_if(codes_, is_background_);
      rgb_background_.reset();
      color_256_background_.reset();
      // Set the requested background
      codes_.push_back(code);
    }

    static bool is_background_(const ANSI_CODE c) {
      switch (c) {
      case ANSI_CODE::BLACK_BACKGROUND:
      case ANSI_CODE::BRIGHT_BLACK_BACKGROUND:
      case ANSI_CODE::BLUE_BACKGROUND:
      case ANSI_CODE::BRIGHT_BLUE_BACKGROUND:
      case ANSI_CODE::CYAN_BACKGROUND:
      case ANSI_CODE::BRIGHT_CYAN_BACKGROUND:
      case ANSI_CODE::GREEN_BACKGROUND:
      case ANSI_CODE::BRIGHT_GREEN_BACKGROUND:
      case ANSI_CODE::MAGENTA_BACKGROUND:
      case ANSI_CODE::BRIGHT_MAGENTA_BACKGROUND:
      case ANSI_CODE::RED_BACKGROUND:
      case ANSI_CODE::BRIGHT_RED_BACKGROUND:
      case ANSI_CODE::WHITE_BACKGROUND:
      case ANSI_CODE::BRIGHT_WHITE_BACKGROUND:
      case ANSI_CODE::YELLOW_BACKGROUND:
      case ANSI_CODE::BRIGHT_YELLOW_BACKGROUND:
        return true;
      default:
        return false;
      }
    }

    static bool is_foreground_(const ANSI_CODE c) {
      switch (c) {
      case ANSI_CODE::BLACK:
      case ANSI_CODE::BRIGHT_BLACK:
      case ANSI_CODE::BLUE:
      case ANSI_CODE::BRIGHT_BLUE:
      case ANSI_CODE::CYAN:
      case ANSI_CODE::BRIGHT_CYAN:
      case ANSI_CODE::GREEN:
      case ANSI_CODE::BRIGHT_GREEN:
      case ANSI_CODE::MAGENTA:
      case ANSI_CODE::BRIGHT_MAGENTA:
      case ANSI_CODE::RED:
      case ANSI_CODE::BRIGHT_RED:
      case ANSI_CODE::WHITE:
      case ANSI_CODE::BRIGHT_WHITE:
      case ANSI_CODE::YELLOW:
      case ANSI_CODE::BRIGHT_YELLOW:
        return true;
      default:
        return false;
      }
    }

    static bool is_style_(const ANSI_CODE c) {
      switch (c) {
      case ANSI_CODE::BOLD:
      case ANSI_CODE::DIM:
      case ANSI_CODE::ITALIC:
      case ANSI_CODE::UNDERLINE:
      case ANSI_CODE::DOUBLE_UNDERLINE:
      case ANSI_CODE::BLINK:
      case ANSI_CODE::REVERSE:
      case ANSI_CODE::HIDDEN:
      case ANSI_CODE::STRIKETHROUGH:
      case ANSI_CODE::OVERLINE:
      case ANSI_CODE::NO_BOLD_DIM:
      case ANSI_CODE::NO_ITALIC:
      case ANSI_CODE::NO_UNDERLINE:
      case ANSI_CODE::NO_BLINK:
      case ANSI_CODE::NO_REVERSE:
      case ANSI_CODE::NO_HIDDEN:
      case ANSI_CODE::NO_STRIKETHROUGH:
      case ANSI_CODE::NO_OVERLINE:
        return true;
      default:
        return false;
      }
    }

    static std::optional<std::array<int, 3>> parse_hex_(std::string_view hex) {
      if (hex.empty()) return std::nullopt;
      if (hex[0] == '#') hex.remove_prefix(1);

      if (hex.size() == 3) {
        // #RGB -> #RRGGBB
        int r = hex_char_to_int_(hex[0]);
        int g = hex_char_to_int_(hex[1]);
        int b = hex_char_to_int_(hex[2]);
        if (r < 0 || g < 0 || b < 0) return std::nullopt;
        return std::array<int, 3>{r * 17, g * 17, b * 17};
      } else if (hex.size() == 6) {
        // #RRGGBB
        int r = (hex_char_to_int_(hex[0]) << 4) | hex_char_to_int_(hex[1]);
        int g = (hex_char_to_int_(hex[2]) << 4) | hex_char_to_int_(hex[3]);
        int b = (hex_char_to_int_(hex[4]) << 4) | hex_char_to_int_(hex[5]);
        if (r < 0 || g < 0 || b < 0) return std::nullopt;
        return std::array<int, 3>{r, g, b};
      }
      return std::nullopt;
    }

    static int hex_char_to_int_(char c) {
      if (c >= '0' && c <= '9') return c - '0';
      if (c >= 'a' && c <= 'f') return c - 'a' + 10;
      if (c >= 'A' && c <= 'F') return c - 'A' + 10;
      return -1;
    }
  };

public:
  // MARK: (ansi) destructors
  ~ansi() = default;
  // MARK: (ansi) constructors
  ansi() = default;
  explicit ansi(std::string_view str);
  template <typename... Args> explicit ansi(std::format_string<Args...> fmt, Args &&...args);

  // no foreground color just jump to styles
  [[nodiscard]] style stylish() const;

  // return the no styled string
  [[nodiscard]] std::string str() const;

  // MARK: (ansi) operators
  template <typename... Args>
  [[nodiscard]] ansi operator()(std::format_string<Args...> fmt, Args &&...args);
  explicit operator std::string() const;
  friend std::ostream &operator<<(std::ostream &os, const ansi &a);

  // MARK: color methods
  // MARK: BLACK
  [[nodiscard]] style black() const;
  [[nodiscard]] style bright_black() const;

  // MARK: BLUE
  [[nodiscard]] style blue() const;
  [[nodiscard]] style bright_blue() const;

  // MARK: CYAN
  [[nodiscard]] style cyan() const;
  [[nodiscard]] style bright_cyan() const;

  // MARK: GREEN
  [[nodiscard]] style green() const;
  [[nodiscard]] style bright_green() const;

  // MARK: MAGENTA
  [[nodiscard]] style magenta() const;
  [[nodiscard]] style bright_magenta() const;

  // MARK: RED
  [[nodiscard]] style red() const;
  [[nodiscard]] style bright_red() const;

  // MARK: WHITE
  [[nodiscard]] style white() const;
  [[nodiscard]] style bright_white() const;

  // MARK: YELLOW
  [[nodiscard]] style yellow() const;
  [[nodiscard]] style bright_yellow() const;

  // MARK: 256 COLOR
  [[nodiscard]] style color256(int color) const;
  template <int COLOR> [[nodiscard]] style color256() const;

  // MARK: RGB COLOR
  template <int R, int G, int B> [[nodiscard]] style rgb() const;
  [[nodiscard]] style rgb(std::array<int, 3> rgb) const;

  // MARK: HEX COLOR
  [[nodiscard]] style hex(std::string_view hex) const;

private:
  std::string text_{};
};

} // namespace nutsloop

#include "inline/ansi.inl"
#include "inline/color256.inl"
#include "inline/literals.inl"
#include "inline/operators.inl"
#include "inline/rgb.inl"