#include "ansi.h++"
#include "unity.h"

#include <string>

TEST_SOURCE_FILE("src/ansi.c++")
TEST_SOURCE_FILE("src/ansi/str.c++")
TEST_SOURCE_FILE("src/ansi/stylish.c++")
TEST_SOURCE_FILE("src/ansi/color/black.c++")
TEST_SOURCE_FILE("src/ansi/color/blue.c++")
TEST_SOURCE_FILE("src/ansi/color/cyan.c++")
TEST_SOURCE_FILE("src/ansi/color/green.c++")
TEST_SOURCE_FILE("src/ansi/color/magenta.c++")
TEST_SOURCE_FILE("src/ansi/color/red.c++")
TEST_SOURCE_FILE("src/ansi/color/white.c++")
TEST_SOURCE_FILE("src/ansi/color/yellow.c++")
TEST_SOURCE_FILE("src/ansi/color/color256.c++")
TEST_SOURCE_FILE("src/ansi/color/rgb.c++")
TEST_SOURCE_FILE("src/ansi/color/hex.c++")

void setUp(void) {}
void tearDown(void) {}

// ---------------------------------------------------------------------------
// ansi -- constructors and str()
// ---------------------------------------------------------------------------

void test_ansi_default_constructor_returns_empty_str(void) {
  nutsloop::ansi a;
  TEST_ASSERT_EQUAL_STRING("", a.str().c_str());
}

void test_ansi_string_view_constructor_stores_text(void) {
  nutsloop::ansi a("hello");
  TEST_ASSERT_EQUAL_STRING("hello", a.str().c_str());
}

void test_ansi_format_constructor(void) {
  nutsloop::ansi a("{} {}", "hello", "world");
  TEST_ASSERT_EQUAL_STRING("hello world", a.str().c_str());
}

// ---------------------------------------------------------------------------
// ansi -- stylish (no foreground color, just styles)
// ---------------------------------------------------------------------------

void test_ansi_stylish_bold_str(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().bold().str();
  TEST_ASSERT_EQUAL_STRING("\033[1mtext\033[0m", result.c_str());
}

void test_ansi_stylish_italic_str(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().italic().str();
  TEST_ASSERT_EQUAL_STRING("\033[3mtext\033[0m", result.c_str());
}

void test_ansi_stylish_underline_str(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().underline().str();
  TEST_ASSERT_EQUAL_STRING("\033[4mtext\033[0m", result.c_str());
}

void test_ansi_stylish_no_codes_returns_plain_text(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().str();
  TEST_ASSERT_EQUAL_STRING("text", result.c_str());
}

// ---------------------------------------------------------------------------
// ansi -- named foreground colors
// ---------------------------------------------------------------------------

void test_ansi_red_str(void) {
  nutsloop::ansi a("err");
  std::string result = a.red().str();
  TEST_ASSERT_EQUAL_STRING("\033[31merr\033[0m", result.c_str());
}

void test_ansi_bright_red_str(void) {
  nutsloop::ansi a("err");
  std::string result = a.bright_red().str();
  TEST_ASSERT_EQUAL_STRING("\033[91merr\033[0m", result.c_str());
}

void test_ansi_green_str(void) {
  nutsloop::ansi a("ok");
  std::string result = a.green().str();
  TEST_ASSERT_EQUAL_STRING("\033[32mok\033[0m", result.c_str());
}

void test_ansi_blue_str(void) {
  nutsloop::ansi a("info");
  std::string result = a.blue().str();
  TEST_ASSERT_EQUAL_STRING("\033[34minfo\033[0m", result.c_str());
}

void test_ansi_yellow_str(void) {
  nutsloop::ansi a("warn");
  std::string result = a.yellow().str();
  TEST_ASSERT_EQUAL_STRING("\033[33mwarn\033[0m", result.c_str());
}

void test_ansi_cyan_str(void) {
  nutsloop::ansi a("note");
  std::string result = a.cyan().str();
  TEST_ASSERT_EQUAL_STRING("\033[36mnote\033[0m", result.c_str());
}

void test_ansi_magenta_str(void) {
  nutsloop::ansi a("magic");
  std::string result = a.magenta().str();
  TEST_ASSERT_EQUAL_STRING("\033[35mmagic\033[0m", result.c_str());
}

void test_ansi_white_str(void) {
  nutsloop::ansi a("bright");
  std::string result = a.white().str();
  TEST_ASSERT_EQUAL_STRING("\033[37mbright\033[0m", result.c_str());
}

void test_ansi_black_str(void) {
  nutsloop::ansi a("dark");
  std::string result = a.black().str();
  TEST_ASSERT_EQUAL_STRING("\033[30mdark\033[0m", result.c_str());
}

// ---------------------------------------------------------------------------
// ansi -- 256 color
// ---------------------------------------------------------------------------

void test_ansi_color256_str(void) {
  nutsloop::ansi a("color");
  std::string result = a.color256(42).str();
  TEST_ASSERT_EQUAL_STRING("\033[38;5;42mcolor\033[0m", result.c_str());
}

void test_ansi_color256_clamps_negative(void) {
  nutsloop::ansi a("color");
  std::string result = a.color256(-10).str();
  TEST_ASSERT_EQUAL_STRING("\033[38;5;0mcolor\033[0m", result.c_str());
}

void test_ansi_color256_clamps_above_255(void) {
  nutsloop::ansi a("color");
  std::string result = a.color256(999).str();
  TEST_ASSERT_EQUAL_STRING("\033[38;5;255mcolor\033[0m", result.c_str());
}

// ---------------------------------------------------------------------------
// ansi -- RGB color
// ---------------------------------------------------------------------------

void test_ansi_rgb_str(void) {
  nutsloop::ansi a("color");
  std::string result = a.rgb({128, 0, 255}).str();
  TEST_ASSERT_EQUAL_STRING("\033[38;2;128;0;255mcolor\033[0m", result.c_str());
}

// ---------------------------------------------------------------------------
// ansi -- hex color
// ---------------------------------------------------------------------------

void test_ansi_hex_6_digit_str(void) {
  nutsloop::ansi a("color");
  std::string result = a.hex("#ff8000").str();
  TEST_ASSERT_EQUAL_STRING("\033[38;2;255;128;0mcolor\033[0m", result.c_str());
}

void test_ansi_hex_3_digit_str(void) {
  nutsloop::ansi a("color");
  // #f80 expands to #ff8800 -> rgb(255, 136, 0)
  std::string result = a.hex("#f80").str();
  TEST_ASSERT_EQUAL_STRING("\033[38;2;255;136;0mcolor\033[0m", result.c_str());
}

void test_ansi_hex_without_hash(void) {
  nutsloop::ansi a("color");
  std::string result = a.hex("00ff00").str();
  TEST_ASSERT_EQUAL_STRING("\033[38;2;0;255;0mcolor\033[0m", result.c_str());
}

// ---------------------------------------------------------------------------
// style -- chaining (color + style)
// ---------------------------------------------------------------------------

void test_ansi_red_bold_str(void) {
  nutsloop::ansi a("error");
  std::string result = a.red().bold().str();
  TEST_ASSERT_EQUAL_STRING("\033[31;1merror\033[0m", result.c_str());
}

void test_ansi_green_bold_italic_str(void) {
  nutsloop::ansi a("done");
  std::string result = a.green().bold().italic().str();
  TEST_ASSERT_EQUAL_STRING("\033[32;1;3mdone\033[0m", result.c_str());
}

// ---------------------------------------------------------------------------
// style -- background colors
// ---------------------------------------------------------------------------

void test_ansi_red_on_white_background(void) {
  nutsloop::ansi a("text");
  std::string result = a.red().white_background().str();
  TEST_ASSERT_EQUAL_STRING("\033[31;47mtext\033[0m", result.c_str());
}

void test_ansi_color256_background(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().color256_background(200).str();
  TEST_ASSERT_EQUAL_STRING("\033[48;5;200mtext\033[0m", result.c_str());
}

void test_ansi_rgb_background(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().rgb_background({10, 20, 30}).str();
  TEST_ASSERT_EQUAL_STRING("\033[48;2;10;20;30mtext\033[0m", result.c_str());
}

// ---------------------------------------------------------------------------
// style -- str_no_reset
// ---------------------------------------------------------------------------

void test_ansi_str_no_reset(void) {
  nutsloop::ansi a("text");
  std::string result = a.red().str_no_reset();
  TEST_ASSERT_EQUAL_STRING("\033[31mtext", result.c_str());
}

// ---------------------------------------------------------------------------
// style -- clear methods
// ---------------------------------------------------------------------------

void test_ansi_clear_all_returns_plain(void) {
  nutsloop::ansi a("text");
  std::string result = a.red().bold().clear_all().str();
  TEST_ASSERT_EQUAL_STRING("text", result.c_str());
}

void test_ansi_clear_foreground_keeps_style(void) {
  nutsloop::ansi a("text");
  std::string result = a.red().bold().clear_foreground().str();
  TEST_ASSERT_EQUAL_STRING("\033[1mtext\033[0m", result.c_str());
}

void test_ansi_clear_styles_keeps_color(void) {
  nutsloop::ansi a("text");
  std::string result = a.red().bold().italic().clear_styles().str();
  TEST_ASSERT_EQUAL_STRING("\033[31mtext\033[0m", result.c_str());
}

// ---------------------------------------------------------------------------
// style -- hyperlink
// ---------------------------------------------------------------------------

void test_ansi_hyperlink_wraps_text(void) {
  nutsloop::ansi a("click");
  std::string result = a.blue().hyperlink("https://example.com").str();
  std::string expected = "\033]8;;https://example.com\033\\\033[34mclick\033[0m\033]8;;\033\\";
  TEST_ASSERT_EQUAL_STRING(expected.c_str(), result.c_str());
}

// ---------------------------------------------------------------------------
// style -- extended underline styles
// ---------------------------------------------------------------------------

void test_ansi_curly_underline(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().curly_underline().str();
  // curly underline = 4:3
  TEST_ASSERT_EQUAL_STRING("\033[4:3mtext\033[0m", result.c_str());
}

void test_ansi_dashed_underline(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().dashed_underline().str();
  TEST_ASSERT_EQUAL_STRING("\033[4:5mtext\033[0m", result.c_str());
}

void test_ansi_dotted_underline(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().dotted_underline().str();
  TEST_ASSERT_EQUAL_STRING("\033[4:4mtext\033[0m", result.c_str());
}

void test_ansi_double_underline(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().double_underline().str();
  TEST_ASSERT_EQUAL_STRING("\033[4:2mtext\033[0m", result.c_str());
}

// ---------------------------------------------------------------------------
// style -- underline color
// ---------------------------------------------------------------------------

void test_ansi_underline_color_rgb(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().underline().underline_color({255, 0, 0}).str();
  // underline (4) + underline color rgb (58:2:R:G:B)
  TEST_ASSERT_EQUAL_STRING("\033[4;58:2:255:0:0mtext\033[0m", result.c_str());
}

void test_ansi_underline_color_256(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().underline().underline_color256(196).str();
  // underline (4) + underline color 256 (58:5:N)
  TEST_ASSERT_EQUAL_STRING("\033[4;58:5:196mtext\033[0m", result.c_str());
}

// ---------------------------------------------------------------------------
// style -- duplicate style prevention
// ---------------------------------------------------------------------------

void test_ansi_bold_called_twice_produces_single_code(void) {
  nutsloop::ansi a("text");
  std::string result = a.stylish().bold().bold().str();
  TEST_ASSERT_EQUAL_STRING("\033[1mtext\033[0m", result.c_str());
}

// ---------------------------------------------------------------------------
// style -- explicit string conversion
// ---------------------------------------------------------------------------

void test_ansi_style_explicit_string_cast(void) {
  nutsloop::ansi a("text");
  std::string result = static_cast<std::string>(a.red());
  TEST_ASSERT_EQUAL_STRING("\033[31mtext\033[0m", result.c_str());
}

// ---------------------------------------------------------------------------
// ansi -- operator() (reuse with new text)
// ---------------------------------------------------------------------------

void test_ansi_call_operator_produces_new_instance(void) {
  nutsloop::ansi a("first");
  nutsloop::ansi b = a("{} {}", "second", "text");
  TEST_ASSERT_EQUAL_STRING("second text", b.str().c_str());
  TEST_ASSERT_EQUAL_STRING("first", a.str().c_str());
}
