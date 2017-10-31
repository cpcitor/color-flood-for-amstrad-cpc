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
        ui_element_t *selected_element = first_selected_element;;
        config_gui_mark_selected_element( first_selected_element, mark_here );

        while ( true )
        {
                char userKey = fw_km_wait_key();
                //fw_txt_wr_char( ' ' );
                //pr_uint( userKey );

                ui_element_t *new_element = selected_element->neighbours[userKey - cpc_up]; // uses the fact that cpc keys are un same order as our neighbourhood define order.

                config_gui_mark_selected_element( selected_element, mark_away );

                if ( new_element != NULL )
                {
                        selected_element = new_element;
                }

                config_gui_mark_selected_element( selected_element, mark_here );
        }
}

