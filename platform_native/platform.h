#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <stdio.h>

#define dbglog(...) fprintf(stderr, __VA_ARGS__);
#define NL "\012"

typedef unsigned char uint8_t;
typedef signed char sint8_t;

//#define assert(...)
#include <assert.h>

#endif /* __PLATFORM_H__ */
