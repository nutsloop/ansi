# Quick Start

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
