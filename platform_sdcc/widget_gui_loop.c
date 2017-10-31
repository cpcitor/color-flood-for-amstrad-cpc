#include "../widget_classes.h"
#include "../print.h"

const char mark_away = ' ';
const char mark_here = '\xF6' ;

enum
{
        cpc_up = 240,
        cpc_down = 241,
        cpc_left = 242,
        cpc_right = 243
};

void gui_loop( ui_element_t *first_selected_element )
{
        ui_element_t *selected_element = first_selected_element;
        unsigned char marker = 0x80;
        //config_gui_mark_selected_element( first_selected_element, mark_here );

        while ( true )
        {
                char userKey = fw_km_read_key();
                //fw_txt_wr_char( ' ' );
                //pr_uint( userKey );

                uint8_t delta = userKey - cpc_up;

                ui_element_t *new_element =
                        ( delta < neighbour_count ) ?
                        selected_element->neighbours[userKey - cpc_up] // uses the fact that cpc keys are un same order as our neighbourhood define order.
                        : NULL;

                config_gui_mark_selected_element( selected_element, mark_away );

                if ( new_element != NULL )
                {
                        selected_element = new_element;
                }

                config_gui_mark_selected_element( selected_element, marker );

                fw_mc_wait_flyback();

                marker = ( ++marker ) | 0x80;
        }
}

