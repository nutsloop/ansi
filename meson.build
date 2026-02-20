project(
    'ansi',
    'cpp',
    version : '1.0.1',
    license : 'Apache-2.0',
    license_files : 'LICENSE',
    default_options : [
        'cpp_std=c++23',
        'warning_level=3',
        'default_library=both',
    ],
)

inc = include_directories('include')

srcs = files(
    #constructors
    'src/ansi.c++',
    'src/terminal.c++',
    #methods
    'src/ansi/stylish.c++',
    'src/ansi/str.c++',
    #colors
    'src/ansi/color/black.c++',
    'src/ansi/color/blue.c++',
    'src/ansi/color/cyan.c++',
    'src/ansi/color/green.c++',
    'src/ansi/color/magenta.c++',
    'src/ansi/color/red.c++',
    'src/ansi/color/white.c++',
    'src/ansi/color/yellow.c++',
    #rgb & 256color & hex
    'src/ansi/color/color256.c++',
    'src/ansi/color/rgb.c++',
    'src/ansi/color/hex.c++',
)

libansi = library(
    'ansi',
    srcs,
    include_directories : inc,
    install : true,
    version : meson.project_version(),
    soversion : '0',
)

# Install headers preserving your include/ layout
install_subdir('include', install_dir : get_option('includedir'))

# Generate a pkg-config file
pkg = import('pkgconfig')
pkg.generate(
    name : 'ansi',
    description : 'ANSI styling helpers',
    version : meson.project_version(),
    libraries : libansi,
    subdirs : '', # headers land directly under includedir because we install the whole include/ tree
)

# Optionally expose for subprojects
ansi_dep = declare_dependency(
    include_directories : inc,
    link_with : libansi,
)
