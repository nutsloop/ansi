# Terminal Detection

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

## Environment Variables

The library respects standard conventions:

| Variable | Effect |
| --- | --- |
| `NO_COLOR` | Disables all colors |
| `FORCE_COLOR=1/2/3` | Force basic/256/truecolor |
| `COLORTERM=truecolor` | Enable true color |
| `TERM` | Terminal type detection |
