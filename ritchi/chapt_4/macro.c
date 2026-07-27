#define forever for (;;) /* infinity loop */

#define dprint(expr) printf(#expr " = %g\n", expr)
dprint(x/y) = printf ("x/y" " = %g\n", expr)

#define paste(front, back) front ## back
/* if write paste(name, 1) it's equal name1    */

#if SYSTEM == SYSV
#define HDR "sysv.h"
#elif SYSTEM == BSD
#define HDR "bsd.h"
#elif SYSTEM == MSDOS
#define HDR "msdos.h"
#else
#define HDR "default.h"
#endif
#include HDR

#if defined  SSA
#if !defined  GRD
