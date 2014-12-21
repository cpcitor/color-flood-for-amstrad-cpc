#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <stdio.h>

#define dbglog(msg) fprintf(stderr, "%s", msg);
#define dbglogf(...) fprintf(stderr, __VA_ARGS__);
#define NL "\012"

typedef unsigned char uint8_t;
typedef signed char sint8_t;

//#define assert(...)
#include <assert.h>

#define cf_platform_init(...) (void)0

#endif /* __PLATFORM_H__ */
