# Advanced Usage

## No Color (Plain Text)

```cpp
"text"_.stylish().bold()    // Bold without foreground color
```

## Get ANSI Codes Only

```cpp
auto style = "text"_.red().bold();
std::string codes = style.codes();  // "\033[31;1m"
```

## Output Without Reset

```cpp
std::string no_reset = "red text"_.red().str_no_reset();
// Color continues until explicit reset
```

## Parent Style Restoration

Restore parent styling after embedded colored text:

```cpp
auto parent = ""_.black().rgb_background({255, 255, 255});
std::string inner = "colored"_.red().str(parent);  // Restores to parent after

ansi message("Hello {} world", inner);
std::cout << message.black().rgb_background({255, 255, 255}) << std::endl;
```

## Clear Methods

```cpp
style.clear_foreground()      // Remove foreground color
style.clear_background()      // Remove background color
style.clear_styles()          // Remove bold, italic, etc.
style.clear_underline_color() // Remove underline color
style.clear_hyperlink()       // Remove hyperlink
style.clear_all()             // Remove everything
```
