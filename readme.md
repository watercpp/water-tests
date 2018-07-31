# Water C++ Library Tests

This is a program to run the tests in the Water C++ library.

It can be built as a command line application by simply compiling all cpp files.
The application will return 0 if the tests succeeded, non-0 if they failed.

It can also be built into another program. Add all cpp files except main.cpp to
that program, and then call me::run(). It returns true if the tests succeeded.
This can be useful to test on Android and iOS.

This depends on the Water C++ library, you need to add it to your compilers
include path so that `#include <water/water.hpp>` works.