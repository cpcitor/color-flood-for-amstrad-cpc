#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "platform.h"

static uint8_t *const screen = 0xC000;
static const uint8_t char_stride = 80;
static const uint16_t line_stride = 0x800;
enum { screen_line_count = 200 };

/* declare line_to_ptr as array of pointer to uint8_t */
extern uint8_t *line_to_ptr[screen_line_count];

/* WARNING: Only works for screen at 0xC000, other cases would need two tests. */
#define screen_write(ptr, value) do { assert(((unsigned int)ptr)>=0xc000); *ptr = value ; } while (0)
/* #define screen_write(ptr, value) do { assert(((unsigned int)ptr)>=((uint16_t)screen)); *ptr = value ; } while (0) */

#define screen_next_line(ptr) do { ptr += line_stride; if ((uint16_t)ptr<0xC000) { ptr = ptr - 8 * line_stride + char_stride; } } while (0)

void cf_screen_line_to_ptr_init();

#endif /* __SCREEN_H__ */
