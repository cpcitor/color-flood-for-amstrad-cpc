#ifndef __SG_ASSERT_H__
#define __SG_ASSERT_H__

#undef assert

#ifdef NDEBUG

/* Debugging disabled -- do not evaluate assertions. */
#define assert(x) ((void)0)

#else

#include "cfwi/cfwi.h"

/* [Stringification - The C Preprocessor](https://gcc.gnu.org/onlinedocs/cpp/Stringification.html#Stringification) */
#define xstr(s) str(s)
#define str(s) #s

/* Debugging enabled -- verify assertions at run time. */

#if ASSERT_CONTINUES == 1
#define assert(x) do { if ((x) == 0) { cfwi_txt_str0_output("Assertion failed: " NL #x NL "File: " __FILE__ NL "Line: " xstr(__LINE__) NL); } } while (0)
#else
#define assert(x) do { if ((x) == 0) { cfwi_txt_str0_output("Assertion failed: " NL #x NL "File: " __FILE__ NL "Line: " xstr(__LINE__) NL); while (1); } } while (0)
#endif

#endif

#endif /* __SG_ASSERT_H__ */
