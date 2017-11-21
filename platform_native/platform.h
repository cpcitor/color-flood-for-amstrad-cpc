#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/* PLATFORM NATIVE */

#include <stdio.h>
#include <stdbool.h> // For portable functions that take or return bool.

#define platform_print_char(c) putchar(c)
#define platform_print_char_safe(c) putchar(c)
#define platform_print_plain_string(msg) fprintf(stderr, "%s", msg)
#define platform_print_formatted_string(...) fprintf(stderr, __VA_ARGS__)
#define NL "\012"

#include <stdint.h>

//#define assert(...)
#include <assert.h>

#define cf_platform_init(...) (void)0
#define cf_platform_prepare_for_game_board(...) (void)0

#endif /* __PLATFORM_H__ */
