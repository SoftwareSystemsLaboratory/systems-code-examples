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

Disclosure
-----------

The code compiles. Many programs don't have unit tests yet. And some things in systems are not easily tested with 
unit tests. But some do, and we'll get there.

That said, most programs here are rather well tested (battle tested?) but please do report issues to me.
