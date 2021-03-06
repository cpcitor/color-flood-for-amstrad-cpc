#include "../model.h"
#include "../widget_classes.h"
#include "../print.h"
#include "../config_gui.h"
#include "widget_style.h"
#include "../widget_configscreen.h"
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

void radioButtonAction( const ui_element_t *const source )
{
        uint8_t new_size = source->data;
        global_model.grid.dimensions.row = new_size;
        global_model.grid.dimensions.col = new_size;

        {
                int i;

                for ( i = 0; i < radioButtonSetGridSizeCount; i++ )
                {
                        // HACK: we rely on the fact that
                        // the radioButtonSetGridSizeCount first ui_element_t
                        // in ui_configscreen
                        // are our radio button group.
                        const ui_element_t *const element = &( ui_configscreen.as_array[i] );
                        radioButtonDraw( element );
                }
        }
}

void checkBoxAction( const ui_element_t *const source )
{
        uint8_t bitmask = source->data;

        global_model.playerEnableBits ^= bitmask;

        checkBoxDraw( source );
}

void buttonAction( const ui_element_t *const source )
{
        uint8_t playerCount = count_bits_in_nibble( global_model.playerEnableBits );
        ( void ) source;
        /*fw_txt_set_cursor( 1, 1 );
        pr_uint( global_model.playerEnableBits );
        cfwi_txt_str0_output( " bits " );
        pr_uint( playerCount );
        cf_pause();*/
        continue_gui_loop = ( playerCount < 2 );

        if ( continue_gui_loop )
        {
                fw_txt_set_cursor( 11, 1 );
                platform_print_plain_string( "\x0E\x02\x0F\x01"
//                                           " Select at least two players positions.  \x0E@" );
                                             " Two to four players needed. Call bros! \x0E@" );
        }
}

void gui_loop( ui_element_t *first_selected_element )
{
        const ui_element_t *selected_element = first_selected_element;
        unsigned char marker = 0x80;
        //config_gui_mark_selected_element( first_selected_element, mark_here );

        fw_scr_set_ink_one( background_pen, rgb_to_cpc_color( 0, 0, 2 ) );
        fw_scr_set_ink_one( text_pen, rgb_to_cpc_color( 2, 1, 1 ) );
        fw_scr_set_ink_one( window_bright_pen, rgb_to_cpc_color( 2, 2, 0 ) );
        fw_scr_set_ink_one( window_dark_pen, rgb_to_cpc_color( 0, 0, 1 ) );
        fw_scr_set_border_one( rgb_to_cpc_color( 0, 1, 2 ) );

        continue_gui_loop = true;

        while ( continue_gui_loop )
        {
                uint16_t userKeyOrNothing = fw_km_read_key();

                if ( userKeyOrNothing & 0xff00 )
                {
                        unsigned char userKey = userKeyOrNothing;
                        //fw_txt_wr_char( ' ' );
                        //pr_uint( userKey );

                        switch ( userKey )
                        {
                                case cpc_space :
                                {
                                        ui_user_action_function_t *acfunc = selected_element->class->action_func;

                                        if ( acfunc != NULL )
                                        {
                                                acfunc( selected_element );
                                        }
                                }
                                break;

                                case 'q':
                                        global_model.playerEnableBits = 0;
                                        continue_gui_loop = false;
                                        break;
                        }

                        {
                                uint8_t delta = userKey - cpc_up;

                                const ui_element_t *const new_element =
                                        ( delta < neighbour_count ) ?
                                        selected_element->neighbours[userKey - cpc_up] // uses the fact that cpc keys are un same order as our neighbourhood define order.
                                        : NULL;

                                config_gui_mark_selected_element( selected_element, mark_away );

                                if ( new_element != NULL )
                                {
                                        selected_element = new_element;
                                }
                        }
                }

                config_gui_mark_selected_element( selected_element, marker );

                fw_mc_wait_flyback();

                marker = ( marker+ 1 ) | 0x80;
        }

        fw_txt_set_cursor( 5, 1 );
}
