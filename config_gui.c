#include "platform.h"
#include "model.h"
#include "widget_classes.h"
#include "config_gui.h"
#include "gui_loop.h"
#include "widget_configscreen.h"

void config_gui_init( void )
{
        draw_window( ( char * )0, 1, 4, 1, 40 );
        draw_window( "Rules", 5, 10, 1, 40 );
        draw_window( "Grid size", win_radio_top, win_radio_top + win_radio_height - 1, 1, 40 );
        draw_window( "Player up left", win_player_row1_top, win_player_row1_top + win_player_height - 1, 1, 20 );
        draw_window( "Player up right", win_player_row1_top, win_player_row1_top + win_player_height - 1, 21, 40 );
        draw_window( "Player down left", win_player_row2_top, win_player_row2_top + win_player_height - 1, 1, 20 );
        draw_window( "Player down right", win_player_row2_top, win_player_row2_top + win_player_height - 1, 21, 40 );

        {
                //uint8_t i;
                //const uint8_t widgetCount = sizeof( ui_configscreen_t ) / sizeof( ui_element_t );
                const ui_element_t *element_p = ui_configscreen.as_array + ui_configscreen_element_count;

                do
                {
                        ui_element_draw( --element_p );
                }
                while ( element_p != ui_configscreen.as_array );
        }

        gui_loop( &ui_configscreen.as_struct.rbGrid12 );
}
