#include "screen.h"

uint8_t *line_to_ptr[screen_line_count];

void cf_screen_line_to_ptr_init()
{
        uint8_t screen_line;
        uint8_t *ptr = screen;
        uint8_t **line_to_ptr_current = line_to_ptr;

        for ( screen_line = 0; screen_line < screen_line_count; screen_line++ )
        {
                //dbglogf( "line %d addr %p" NL, screen_line, ptr );
                *( line_to_ptr_current++ ) = ptr;
                screen_next_line( ptr );
        }
}

