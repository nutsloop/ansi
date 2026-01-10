# Installation

## Meson (recommended)

```meson
ansi_dep = dependency('ansi', fallback: ['ansi', 'ansi_dep'])
```

## Manual

```bash
meson setup build
meson compile -C build
meson install -C build
```
