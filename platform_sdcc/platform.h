#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/* PLATFORM SDCC */

#include <stdio.h>

#include <cfwi/cfwi.h> // for cfwi_txt_str0_output
#define platform_print_char(c) fw_txt_output(c)
#define platform_print_char_safe(c) fw_txt_wr_char(c)
#define platform_print_plain_string(msg) cfwi_txt_str0_output(msg)
#define platform_print_formatted_string(...) printf(__VA_ARGS__)
#define NL "\015\012"

#define platform_wait_for_key fw_km_wait_key

#include <stdint.h>

//#define assert(...)
#include "sg_assert.h"

#include "screen.h"

void cf_platform_init();
void cf_platform_prepare_screen_for_game_board();
void cf_platform_prepare_for_game_board();

// for memcpy
#include <string.h>
#define ASSIGN(dst, src) memcpy( (&(dst)), (&(src)), sizeof(src) )

#define fw_scr_set_ink_one(ink, color1) fw_scr_set_ink((ink), (color1), (color1))
#define fw_scr_set_border_one(color1) fw_scr_set_border( (color1), (color1))
#define rgb_to_cpc_color(r, g, b) (9*(g) + 3*(r)+(b))

#endif /* __PLATFORM_H__ */
