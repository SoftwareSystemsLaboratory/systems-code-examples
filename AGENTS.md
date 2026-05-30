# Repository Guidelines

## Project Structure & Module Organization

This repository contains small operating-systems and systems-programming examples. Most examples live in top-level directories with their own `CMakeLists.txt`, source files, and local headers, such as `fork/`, `bounded-buffer/`, `simple_adt/`, and `std-queue/`. The root `CMakeLists.txt` drives the normal C/C++ build and writes executables under `build/bin`. GoogleTest tests are colocated with examples and usually end in `_tests.cc`. C# examples are under `threads_csharp/`; kernel samples are under `linux-kernel/` and `minix-kernel/`.

## Build, Test, and Development Commands

- `cmake -S . -B build`: configure the default CMake build.
- `cmake --build build`: compile the standard examples.
- `cmake -S . -B build -DBUILD_TESTING=ON`: configure with GoogleTest test binaries enabled.
- `ctest --test-dir build --output-on-failure`: run enabled tests and show failing output.
- `cmake -S . -B build -DBUILD_OPTIONAL_EXAMPLES=ON`: include Linux-only optional examples such as `monitor/`, `mutex/`, and `semaphore/`.
- `scripts/build-cmake-examples.sh`: legacy per-directory CMake helper; prefer the top-level workflow.

## Coding Style & Naming Conventions

Apply style cleanup only to original C/C++ examples in directories with a `CMakeLists.txt`. Do not reformat non-CMake examples, scripts, generated files, or imported/reference code unless the change targets them. Use K&R braces with 2-space indentation:

```c
void point_init(point_t *point, double x, double y) {
  point->x = x;
  point->y = y;
}
```

Use `snake_case` for C functions, variables, and struct fields. Keep `_t` typedef aliases where already used. Use `UPPER_CASE` only for macros and constants. In C++, class names may use PascalCase, but methods and ordinary variables should use `snake_case`.

## Testing Guidelines

Tests use GoogleTest and are disabled unless `BUILD_TESTING=ON` is set. Add tests near the module they cover using names like `<module>_tests.cc`. Prefer focused API and edge-case tests. After changing tests, run:

```sh
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## Commit & Pull Request Guidelines

Recent history uses short, imperative or descriptive commit subjects such as `Make tests optional in CMake builds`. Keep commits scoped to one example or build concern. Pull requests should describe affected directories, list build/test commands run, and call out platform assumptions, especially for GNU/Linux-only or macOS-limited code.

## Security & Configuration Tips

Do not commit generated build directories, downloaded GoogleTest content, binaries, or local IDE files. Some examples exercise low-level APIs, processes, threads, sockets, and kernel interfaces; document elevated permissions or Linux-only requirements in the relevant example README.
