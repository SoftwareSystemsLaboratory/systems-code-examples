// square_root.hh
// This header ensures C linkage is enforced when running C++ unit tessts on C code.

#ifdef __cplusplus

extern "C" {

#include "int_stack.h"

}

#else

#include "int_stack.h"

#endif
