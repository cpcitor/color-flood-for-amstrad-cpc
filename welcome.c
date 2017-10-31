#include "platform.h"
#include "platform_ui.h"
#include "config_gui.h"
#include "widget_style.h"
#include <stdio.h>

#define print_literal_line_centered(str) print_literal_line_centered_with_size(str NL, sizeof(str));

/*void print_literal_line_centered_with_size( char *str, int size )
{
        const char *skip = "                    ";
        const char *margin = ( ( char * )skip ) + ( size >> 1 );
        platform_print_plain_string( margin ); // Center
        platform_print_plain_string( str ); // puts includes NL
}*/

#define el()         platform_print_plain_string(NL)

void welcome()
{
        cf_platform_prepare_for_config_screen();
        /* nt_literal_line_centered( "0123456789012345678901234567890123456789") */
        /* print_literal_line_centered( "Welcome to" ); */
        el();
        platform_print_plain_string( " Welcome to Color Flood for Amstrad CPC" NL );
        platform_print_plain_string( " \xa4" "2014-2017  https://github.com/cpcitor" NL );
        el();
        platform_print_plain_string( " Coded in C + SDCC + cpc-dev-tool-chain" NL );
        el();
        platform_print_plain_string( " Each player owns a colored domain." NL );
        platform_print_plain_string( " At each move change your domain color" NL );
        platform_print_plain_string( " and annex neighbours of target color." NL );
        platform_print_plain_string( " *** Player with biggest area wins. ***" NL );
        el();
        platform_print_plain_string( "========== Choose your options =========" );
        config_gui_init();
        cf_pause();
}
