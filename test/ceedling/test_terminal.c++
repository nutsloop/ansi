#include "terminal.h++"
#include "unity.h"

TEST_SOURCE_FILE("src/terminal.c++")

void setUp(void) {
  nutsloop::terminal::reset_color_support();
}

void tearDown(void) {
  nutsloop::terminal::reset_color_support();
}

// ---------------------------------------------------------------------------
// terminal -- force_color_support / detect_color_support
// ---------------------------------------------------------------------------

void test_terminal_force_none(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::NONE);
  TEST_ASSERT_EQUAL_INT(
      static_cast<int>(nutsloop::terminal::color_support::NONE),
      static_cast<int>(nutsloop::terminal::detect_color_support()));
}

void test_terminal_force_basic(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::BASIC);
  TEST_ASSERT_EQUAL_INT(
      static_cast<int>(nutsloop::terminal::color_support::BASIC),
      static_cast<int>(nutsloop::terminal::detect_color_support()));
}

void test_terminal_force_256(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::COLOR_256);
  TEST_ASSERT_EQUAL_INT(
      static_cast<int>(nutsloop::terminal::color_support::COLOR_256),
      static_cast<int>(nutsloop::terminal::detect_color_support()));
}

void test_terminal_force_true_color(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::TRUE_COLOR);
  TEST_ASSERT_EQUAL_INT(
      static_cast<int>(nutsloop::terminal::color_support::TRUE_COLOR),
      static_cast<int>(nutsloop::terminal::detect_color_support()));
}

// ---------------------------------------------------------------------------
// terminal -- supports_color
// ---------------------------------------------------------------------------

void test_terminal_supports_color_when_forced_basic(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::BASIC);
  TEST_ASSERT_TRUE(nutsloop::terminal::supports_color());
}

void test_terminal_no_color_when_forced_none(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::NONE);
  TEST_ASSERT_FALSE(nutsloop::terminal::supports_color());
}

// ---------------------------------------------------------------------------
// terminal -- supports_256_colors
// ---------------------------------------------------------------------------

void test_terminal_supports_256_when_forced_256(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::COLOR_256);
  TEST_ASSERT_TRUE(nutsloop::terminal::supports_256_colors());
}

void test_terminal_no_256_when_forced_basic(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::BASIC);
  TEST_ASSERT_FALSE(nutsloop::terminal::supports_256_colors());
}

// ---------------------------------------------------------------------------
// terminal -- supports_true_color
// ---------------------------------------------------------------------------

void test_terminal_supports_true_color_when_forced(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::TRUE_COLOR);
  TEST_ASSERT_TRUE(nutsloop::terminal::supports_true_color());
}

void test_terminal_no_true_color_when_forced_256(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::COLOR_256);
  TEST_ASSERT_FALSE(nutsloop::terminal::supports_true_color());
}

// ---------------------------------------------------------------------------
// terminal -- reset_color_support
// ---------------------------------------------------------------------------

void test_terminal_reset_clears_forced_mode(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::NONE);
  TEST_ASSERT_FALSE(nutsloop::terminal::supports_color());

  nutsloop::terminal::reset_color_support();
  // After reset, detection runs from environment.
  // We cannot predict the result, but it should not throw.
  nutsloop::terminal::detect_color_support();
}

// ---------------------------------------------------------------------------
// terminal -- hierarchy: TRUE_COLOR >= COLOR_256 >= BASIC
// ---------------------------------------------------------------------------

void test_terminal_true_color_implies_256(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::TRUE_COLOR);
  TEST_ASSERT_TRUE(nutsloop::terminal::supports_256_colors());
}

void test_terminal_true_color_implies_basic(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::TRUE_COLOR);
  TEST_ASSERT_TRUE(nutsloop::terminal::supports_color());
}

void test_terminal_256_implies_basic(void) {
  nutsloop::terminal::force_color_support(
      nutsloop::terminal::color_support::COLOR_256);
  TEST_ASSERT_TRUE(nutsloop::terminal::supports_color());
}
