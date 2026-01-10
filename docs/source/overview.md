# Overview

A modern C++23 library for beautiful terminal styling.

```cpp
#include "ansi.h++"
using namespace nutsloop;

std::cout << "Hello"_.red().bold() << " " << "World"_.green().underline() << std::endl;
```

## Features

- **Zero dependencies**: pure C++ standard library.
- **Fluent API**: chain methods naturally, like `.red().bold().underline()`.
- **User-defined literals**: write `"text"_` instead of `ansi{"text"}`.
- **Complete color support**: 8/16, 256, RGB, and hex colors.
- **All text styles**: bold, italic, underline variants, strikethrough, and more.
- **Hyperlinks**: clickable terminal links (OSC 8).
- **Terminal detection**: auto-detect color capabilities.
- **Modern C++**: requires C++23 and uses `std::format`.
