#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "platform.h"

static uint8_t *const screen = 0xC000;
static const uint8_t char_stride = 80;
static const uint16_t line_stride = 0x800;

/* WARNING: Only works for screen at 0xC000, other cases would need two tests. */
#define screen_write(ptr, value) do { assert(((unsigned int)ptr)>=0xc000); *ptr = value ; } while (0)
/* #define screen_write(ptr, value) do { assert(((unsigned int)ptr)>=((uint16_t)screen)); *ptr = value ; } while (0) */

#endif /* __SCREEN_H__ */
