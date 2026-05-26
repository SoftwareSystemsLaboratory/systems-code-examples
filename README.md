Build Status
--------------

[![OS Examples](https://github.com/SoftwareSystemsLaboratory/systems-code-examples/actions/workflows/cmake.yml/badge.svg)](https://github.com/SoftwareSystemsLaboratory/systems-code-examples/actions/workflows/cmake.yml)

Synopsis
---------

A number of example programs to accompany the [os.cs.luc.edu](https://os.cs.luc.edu) lecture notes for the Operating Systems course at Loyola University Chicago.

Recent Developments
----------------------

- Updated CMake build process. All examples are driven by a top-level `CMakeLists.txt`. CMake is pretty awesome. I just don't have the time to write Makefiles by hand, and I never enjoyed working with autoconf.

- Establish foundation for using `GoogleTest`. 

- Modular structure to allow various examples to be standalone programs, possibly with internal library dependencies. 

- Many new examples with *pthreads*.


Building
---------

The default build compiles the example programs. GoogleTest-based test binaries
are optional and are enabled with `-DBUILD_TESTING=ON`.

Default build:

- `git clone https://github.com/SoftwareSystemsLaboratory/systems-code-examples`
- `cd systems-code-examples`
- `cmake -S . -B build`
- `cmake --build build`

Build and run tests:

- `cmake -S . -B build -DBUILD_TESTING=ON`
- `cmake --build build`
- `ctest --test-dir build --output-on-failure`

Build the Linux-only optional examples:

- `cmake -S . -B build -DBUILD_OPTIONAL_EXAMPLES=ON`
- `cmake --build build`

Debian/Linux/GNU Systems
-------------------------

- `git clone https://github.com/SoftwareSystemsLaboratory/systems-code-examples`
- `apt install build-essential cmake`
- `cd systems-code-examples`
- `cmake -S . -B build`
- `cmake --build build`

OS X via Homebrew
------------------

We only provide limited support for OS X and Homebrew at this time.
The core examples from https://os.cs.luc.edu work. However, some of the newer examples rely on some GNU-specific (and sometimes GNU-only) features that don't seem to have a clear equivalent on OS X (even via Homebrew).
I'm still working on it.

Nevertheless, if you want to try, do the following:


- `git clone https://github.com/SoftwareSystemsLaboratory/systems-code-examples`
- `brew install cmake`
- `cd systems-code-examples`
- `cmake -S . -B build`
- `cmake --build build`

To build the GoogleTest-based test binaries, configure with `-DBUILD_TESTING=ON`.
This requires network access during CMake configuration unless GoogleTest has
already been downloaded or supplied through CMake's FetchContent options.

Hopefully, by end of the Fall semester, I will be able to get the 5 pesky examples to build/run on OS X.
It's not a matter of *if* but *when*.
