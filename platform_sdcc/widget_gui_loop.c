#include "../model.h"
#include "../widget_classes.h"
#include "../print.h"
#include "count_bits_in_nibble.h"
#include <cfwi/cfwi.h>

const char mark_away = ' ';
const char mark_here = '\xF6' ;

enum
{
        cpc_up = 240,
        cpc_down = 241,
        cpc_left = 242,
        cpc_right = 243,
        cpc_space = ' '
};

static bool continue_gui_loop;

void buttonAction( ui_element_t *source )
{
        uint8_t playerCount = count_bits_in_nibble( global_model.playerEnableBits );
        ( void ) source;
        /*fw_txt_set_cursor( 1, 1 );
        pr_uint( global_model.playerEnableBits );
        cfwi_txt_str0_output( " bits " );
        pr_uint( playerCount );
        cf_pause();*/
        continue_gui_loop = ( playerCount < 2 );
}

void gui_loop( ui_element_t *first_selected_element )
{
        ui_element_t *selected_element = first_selected_element;
        unsigned char marker = 0x80;
        //config_gui_mark_selected_element( first_selected_element, mark_here );

        continue_gui_loop = true;

        while ( continue_gui_loop )
        {
                char userKey = fw_km_read_key();
                //fw_txt_wr_char( ' ' );
                //pr_uint( userKey );

                if ( userKey == cpc_space )
                {
                        ui_user_action_function_t *acfunc = selected_element->class->action_func;

                        if ( acfunc != NULL )
                        {
                                acfunc( selected_element );
                        }
                }

                {
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
                }

                config_gui_mark_selected_element( selected_element, marker );

                fw_mc_wait_flyback();

                marker = ( ++marker ) | 0x80;
        }
}
