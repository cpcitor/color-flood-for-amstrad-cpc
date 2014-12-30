#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/* PLATFORM SDCC */

#include <stdio.h>

#include <cfwi/cfwi.h>

#define platform_print_plain_string(msg) cfwi_txt_str0_output(msg)
#define platform_print_formatted_string(...) printf(__VA_ARGS__)
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

// for memcpy
#include <string.h>
#define ASSIGN(dst, src) memcpy( (&(dst)), (&(src)), sizeof(src) )

#endif /* __PLATFORM_H__ */
