// square_root.hh
// This header ensures C linkage is enforced when running C++ unit tessts on C code.

#include <math.h>

#ifdef __cplusplus

extern "C" {

#include "point.h"

}

#else

#include "point.h"

#endif
