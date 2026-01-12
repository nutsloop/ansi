# Repository Guidelines

## Policy
- WARNING: Never run `sudo` unless the user explicitly requests it; even then, always ask for confirmation before running any `sudo` command.

### use of Emoticons
**IMPORTANT:** Avoid emoji in docs/logs/source everywhere; use plain Unicode symbols.
Recommended Unicode symbols:
- ✓ check
- ✗ cross
- • bullet
- ‣ bullet (alt)
- ◦ bullet (alt)
- → arrow right
- ← arrow left
- ↑ arrow up
- ↓ arrow down
- ↳ return/branch
- ⇢ arrow right (alt)
- ⇒ implies
- ⇐ implies (rev)
- ⇔ iff
- ↔ bidirectional
- ⟶ long arrow
- ⟵ long arrow (rev)
- ⟷ long bidirectional
- ∎ end marker
- □ empty square
- ■ filled square
- ◆ filled diamond
- ◇ empty diamond
- ○ empty circle
- ● filled circle
- ▸ triangle right
- ▾ triangle down
- ▲ triangle up
- ▼ triangle down (alt)
- ⌁ wave
- ⋯ ellipsis (midline)
- ≈ approximately
- ≠ not equal
- ≤ less-than-or-equal
- ≥ greater-than-or-equal
- ± plus/minus
- ∞ infinity
- ∅ empty set
- ∈ member of
- ∉ not member of
- ⊂ subset
- ⊃ superset
- ¬ logical not

Expressive symbols:
- ✦ star
- ✧ star (outline)
- ✶ star (alt)
- ✷ star (alt)
- ✸ star (alt)
- ✹ star (alt)
- ✺ star (alt)
- ✻ star (alt)
- ✼ star (alt)
- ✽ star (alt)
- ✾ star (alt)
- ✿ floral
- ❀ floral (alt)
- ❁ floral (alt)
- ❂ sun
- ❃ floral (alt)
- ❄ snowflake
- ❅ snowflake (alt)
- ❆ snowflake (alt)
- ❇ sparkle
- ❈ sparkle (alt)
- ❉ sparkle (alt)
- ❊ sparkle (alt)
- ❋ sparkle (alt)
- ❖ ornamental diamond
- ✱ asterisk star
- ✲ asterisk star (alt)
- ✳ asterisk star (alt)
- ❘ light vertical
- ❘̸ barred vertical
- ❙ heavy vertical
- ❚ heavy vertical (alt)
- ❛ single quote (ornate)
- ❜ single quote (ornate)
- ❝ double quote (ornate)
- ❞ double quote (ornate)
- ❦ floral heart
- ❧ rotated floral heart
- ❥ heart (ornate)
- ❍ ring
- ⊕ circled plus
- ⊗ circled times
- ⊙ circled dot
- ⊚ circled dot (alt)
- ⊛ circled star
- ⊜ circled equal
- ♠ spade (ace)
- ♥ heart (ace)
- ♦ diamond (ace)
- ♣ club (ace)
- ✦ future...

## A modern C++23 library for beautiful terminal styling.

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
