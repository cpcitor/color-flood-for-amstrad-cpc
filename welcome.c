#include "platform.h"
#include "platform_ui.h"
#include "config_gui.h"
#include <stdio.h>

#define print_literal_line_centered(str) print_literal_line_centered_with_size(str NL, sizeof(str));

void print_literal_line_centered_with_size( char *str, int size )
{
        const char *skip = "                    ";
        const char *margin = ( ( char * )skip ) + ( size >> 1 );
        platform_print_plain_string( margin ); // Center
        platform_print_plain_string( str ); // puts includes NL
}

#define el()         platform_print_plain_string(NL)

void welcome()
{
        /* nt_literal_line_centered( "0123456789012345678901234567890123456789") */
        /* print_literal_line_centered( "Welcome to" ); */
        /* el(); */
        print_literal_line_centered( "Welcome to Color Flood for Amstrad CPC" );
        print_literal_line_centered( "(c)2014-2017 by cpcitor" );
        el();
        platform_print_plain_string( "Each player owns a colored domain." NL );
        platform_print_plain_string( "Each move changes one's domain color and" NL );
        platform_print_plain_string( "annexes neighbours of the target color." NL );
        platform_print_plain_string( "Try to finish with biggest area." NL );
        config_gui_init();
        cf_pause();
}
