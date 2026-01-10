# Repository Guidelines

## Policy
- WARNING: Never run `sudo` unless the user explicitly requests it; even then, always ask for confirmation before running any `sudo` command.

## Coding Style & Naming Conventions
- Use C++23 features; prefer `std::format` for logging/string assembly over manual concatenation/streams. C++ uses 2-space indentation, RAII, and standard library utilities;

Keep headers in `include` paired with `src/ansi/` implementations.
- Keep files lowercase with `snake_case.c++`/`.h++`.
- private member of classes always suffixed with a low-dash `_`
- the implementation of methods of a class should be stored into a file named after the method under a directory named after the class. constructors are implemented in the c++ file named after the class.
- the implementation of methods of a struct should be stored into a file named after the method under a directory named after the struct. constructors are implemented in the c++ file named after the struct.

## Commit & Pull Request Guidelines
- Always wait to commit when requested, never do for every change
- Use concise, descriptive commits; conventional prefixes seen here (`feat:`, `fix:`, `chore:`). Example: `feat: add SSE memory stream`.
- Always follow the subject with a blank line and a short body explaining the change (what/why); keep commits scoped and avoid committing build artifacts unless required.
- PRs should summarize changes, mention affected modules, list verification steps (builds, curl/browser checks, load tests), and include screenshots/GIFs for UI updates.
- Use detailed description for every commit
- try to logical commit file related by mean.