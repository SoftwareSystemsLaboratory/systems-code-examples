// square_root.hh
// This header ensures C linkage is enforced when running C++ unit tessts on C code.

#include <math.h>

#ifdef __cplusplus

extern "C" {

#include "rational.h"

}

#else

#include "rational.h"

#endif
