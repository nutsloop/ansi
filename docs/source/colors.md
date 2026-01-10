# Colors and Backgrounds

## Named Colors (8/16)

```cpp
"text"_.black()          "text"_.bright_black()
"text"_.red()            "text"_.bright_red()
"text"_.green()          "text"_.bright_green()
"text"_.yellow()         "text"_.bright_yellow()
"text"_.blue()           "text"_.bright_blue()
"text"_.magenta()        "text"_.bright_magenta()
"text"_.cyan()           "text"_.bright_cyan()
"text"_.white()          "text"_.bright_white()
```

## 256 Colors

```cpp
"text"_.color256(208)        // Runtime value
"text"_.color256<208>()      // Compile-time (validated)
```

## RGB (True Color)

```cpp
"text"_.rgb({255, 128, 0})       // Runtime
"text"_.rgb<255, 128, 0>()       // Compile-time
```

## Hex Colors

```cpp
"text"_.hex("#FF8000")       // 6-digit
"text"_.hex("#F80")          // 3-digit shorthand
```

## Backgrounds

All color methods have background equivalents:

```cpp
"text"_.red().white_background()
"text"_.green().rgb_background({30, 30, 30})
"text"_.blue().hex_background("#1a1a1a")
"text"_.cyan().color256_background(236)
```
