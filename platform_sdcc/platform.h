#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/* PLATFORM SDCC */

#include <stdio.h>

#include <cfwi/cfwi.h> // for cfwi_txt_str0_output
#define platform_print_plain_string(msg) cfwi_txt_str0_output(msg)
#define platform_print_formatted_string(...) printf(__VA_ARGS__)
#define NL "\015\012"


#include <stdint.h>

//#define assert(...)
#include "sg_assert.h"

#include "screen.h"

void cf_platform_init();
void cf_platform_prepare_for_game_board();

// for memcpy
#include <string.h>
#define ASSIGN(dst, src) memcpy( (&(dst)), (&(src)), sizeof(src) )

#endif /* __PLATFORM_H__ */
