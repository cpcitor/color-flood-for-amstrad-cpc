#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/* PLATFORM NATIVE */

#include <stdio.h>

#define platform_print_plain_string(msg) fprintf(stderr, "%s", msg)
#define platform_print_formatted_string(...) fprintf(stderr, __VA_ARGS__)
#define NL "\012"

typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef unsigned short uint16_t;

//#define assert(...)
#include <assert.h>

#define cf_platform_init(...) (void)0

#endif /* __PLATFORM_H__ */
