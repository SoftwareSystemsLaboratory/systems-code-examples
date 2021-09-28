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


Debian/Linux/GNU Systems
-------------------------

- `git clone https://github.com/SoftwareSystemsLaboratory/systems-code-examples`
- `apt install build-essential cmake`
- Install GoogleTest using instructions at https://github.com/SoftwareSystemsLaboratory/googletest-mva.
- `cd systems-code-examples`
- `mkdir build`
- `cd build`
- `cmake ..`
- `make`

OS X via Homebrew
------------------

We only provide limited support for OS X and Homebrew at this time.
The core examples from https://os.cs.luc.edu work. However, some of the newer examples rely on some GNU-specific (and sometimes GNU-only) features that don't seem to have a clear equivalent on OS X (even via Homebrew).
I'm still working on it.

Nevertheless, if you want to try, do the following:


- `git clone https://github.com/SoftwareSystemsLaboratory/systems-code-examples`
- `brew install cmake gcc@11`
- Install GoogleTest using instructions at https://github.com/SoftwareSystemsLaboratory/googletest-mva.
- `cd systems-code-examples`
- `mkdir build`
- `cd build`
- `cmake -DCMAKE_C_COMPILER=$(which gcc-11) -DCMAKE_CXX_COMPILER=$(which g++-11) ..`
- `make`

Hopefully, by end of the Fall semester, I will be able to get the 5 pesky examples to build/run on OS X.
It's not a matter of *if* but *when*.
