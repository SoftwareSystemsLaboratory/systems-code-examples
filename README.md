Build Status
--------------

[![Build Status](https://travis-ci.com/gkthiruvathukal/systems-code-examples.svg?branch=master)](https://travis-ci.com/gkthiruvathukal/systems-code-examples)


Synopsis
---------

A number of example programs to accompany https://os.cs.luc.edu, lecture notes on the Operating Systems course at Loyola University Chicago.

I'm doing some major updating to tehse examples, including merging in many additions I have made over the past 3
semesters of teaching it. Stay tuned for what (I hope) will be some great news.

Things I'm working on
----------------------

- For starters, using continuous integration to make sure our examples build properly on Linux. Students love it when code actually compiles.

- Incorporating GoogleTest as appropriate. Unit Testing is useful to computer systems!

- Having systems examples in C (with occasional C++), Java, and C#. Might add Python soon, too.

- Making sure software engineering is a part of everything we do.

- All examples now build with ``cmake``. I'm sorry, I grew up creating Makefiles, but I am tired of writing them by hand. CMake does a nice job. More to the point, it works across different Unix words. I never found the "auto" tools to be satisfactory. ``cmake`` just works.

Disclosure
-----------

The code compiles. Many programs don't have unit tests yet. And some things in systems are not easily tested with 
unit tests. But some do, and we'll get there.

That said, most programs here are rather well tested (battle tested?) but please do report issues to me.
