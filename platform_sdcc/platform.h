#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <stdio.h>

#include <cfwi/cfwi.h>

#define dbglog(str) cfwi_txt_str0_output(str)
#define dbglogf(...) printf(__VA_ARGS__) // looks like SDCC's printf introduces bugs in program...
#define NL "\015\012"

/* SDCC types */
typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef unsigned short uint16_t;
typedef signed short sint16_t;

//#define assert(...)
#include "sg_assert.h"

#include "screen.h"

void cf_platform_init();

#endif /* __PLATFORM_H__ */
