srcs = files('main.c++')

exe = executable(
    'ansi_',
    srcs,
    dependencies: [ansi_dep],
    install: false,   # change to true if you want it installed
)

# Register a quick runtime test
test('ansi_runs', exe)