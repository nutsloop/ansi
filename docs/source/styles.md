# Text Styles

## Basic Styles

```cpp
"text"_.red().bold()
"text"_.red().dim()
"text"_.red().italic()
"text"_.red().blink()
"text"_.red().reverse()
"text"_.red().hidden()
"text"_.red().strike_through()
"text"_.red().overline()
```

## Underline Variants

```cpp
"text"_.red().underline()           // Single
"text"_.red().double_underline()    // Double
"text"_.red().curly_underline()     // Wavy/curly
"text"_.red().dotted_underline()    // Dotted
"text"_.red().dashed_underline()    // Dashed
```

## Underline Colors

```cpp
"text"_.white().underline().underline_color({255, 0, 0})
"text"_.white().curly_underline().underline_color<255, 0, 0>()
"text"_.white().underline().underline_hex("#FF0000")
"text"_.white().underline().underline_color256(196)
```

## Style Removal

Remove individual styles without full reset:

```cpp
"text"_.red().bold().italic().no_bold()    // Keeps italic
"text"_.red().underline().no_underline()
"text"_.red().italic().no_italic()
// Also: no_dim, no_blink, no_reverse, no_hidden, no_strike_through, no_overline
```
