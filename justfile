# justfile for nutsloop/ansi -- C++23 ANSI styling library
# Build system: Meson + Ninja

# ---------------------------------------------------------------------------
# Settings
# ---------------------------------------------------------------------------

set shell         := ["zsh", "-cu"]
set dotenv-load   := false

# ---------------------------------------------------------------------------
# Variables
# ---------------------------------------------------------------------------

build_dir := "build"

version := `grep -m1 "version" meson.build | grep -oE "[0-9]+\.[0-9]+\.[0-9]+"`

# ---------------------------------------------------------------------------
# Default
# ---------------------------------------------------------------------------

# Show available recipes
[default]
default:
  @just --list --justfile {{justfile()}}

# ---------------------------------------------------------------------------
# Setup
# ---------------------------------------------------------------------------

# Run meson setup for the library build
[group('setup')]
setup:
  meson setup {{build_dir}}

# Reconfigure the build directory
[group('setup')]
reconfigure dir=build_dir:
  meson setup --reconfigure {{dir}}

# ---------------------------------------------------------------------------
# Build
# ---------------------------------------------------------------------------

# Compile the library (sets up first if needed)
[group('build')]
build: setup
  meson compile -C {{build_dir}}

# Clean, reconfigure, and recompile the standard build
[group('build')]
rebuild:
  -rm -rf {{build_dir}}
  meson setup {{build_dir}}
  meson compile -C {{build_dir}}

# ---------------------------------------------------------------------------
# Test
# ---------------------------------------------------------------------------

# Run all ceedling unit tests
[group('test')]
ceedling-test:
  ceedling test:all

# Run a single ceedling test file (e.g. just ceedling-test-file test_ansi)
[group('test')]
ceedling-test-file name:
  ceedling test:{{name}}

# ---------------------------------------------------------------------------
# Coverage
# ---------------------------------------------------------------------------

# Run ceedling gcov and generate HTML coverage report
[group('coverage')]
gcov:
  ceedling gcov:all

# Generate coverage HTML report from existing gcov data
[group('coverage')]
gcov-report:
  ceedling utils:gcov

# ---------------------------------------------------------------------------
# Clean
# ---------------------------------------------------------------------------

# Remove the build directory and ceedling cache
[group('clean')]
[confirm("Remove build directory and ceedling cache? [y/N]")]
clean:
  -rm -rf {{build_dir}}
  -rm -rf .cache/ceedling

# ---------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------

# Install the library (requires a completed build)
[group('install')]
[confirm("Install the library to the system? [y/N]")]
install: build
  meson install -C {{build_dir}}

# ---------------------------------------------------------------------------
# Utility
# ---------------------------------------------------------------------------

# Print the current project version from meson.build
[group('utility')]
version:
  @echo "ansi {{version}}"
