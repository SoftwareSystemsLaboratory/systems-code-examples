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

Limitations
------------

- We only support Linux/BSD systems for now. For the most part, this is not a major issue, since my teaching is on Linux (and equivalent systems, e.g. Windows Substem for Linux and Chrome OS/Crostini with Debian). All of these platforms are known to work--and work well.
- Our primary test environment is with the LTS releases of Linux (20.04 LTS is used in our GH Actions setup).
- OS X + Homebrew is in the works. I'm making some progress with gcc@11 but there are problems getting `cmake` to use the GNU libc instead of the OS supplied one, which has some problems with the standard data structures (hsearch and tsearch) in my testing.
- OS X users are recommended to use Docker at this time (Ubuntu base image with build-essential and cmake installed).
