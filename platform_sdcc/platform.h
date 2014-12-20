#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#define dbglog(...) printf(__VA_ARGS__);
#define NL "\015\012"

/* SDCC types */
typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef unsigned short uint16_t;
typedef signed short sint16_t;

//#define assert(...)
#include <assert.h>

#include "screen.h"

#endif /* __PLATFORM_H__ */
