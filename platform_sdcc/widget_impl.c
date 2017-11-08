#include "../widget_base.h"
#include "platform.h"
#include "../model.h"
#include "../print.h"
#include "widget_style.h"

void cf_platform_prepare_for_config_screen()
{
        fw_scr_set_mode( 1 );
        fw_scr_set_ink_one( 0, rgb_to_cpc_color( 0, 0, 2 ) );
        fw_scr_set_ink_one( 1, rgb_to_cpc_color( 0, 0, 2 ) );
        fw_scr_set_ink_one( 2, rgb_to_cpc_color( 0, 0, 2 ) );
        fw_scr_set_ink_one( 3, rgb_to_cpc_color( 0, 0, 2 ) );
        fw_scr_set_ink_one( background_pen, rgb_to_cpc_color( 0, 0, 1 ) );
        fw_scr_set_ink_one( text_pen, rgb_to_cpc_color( 1, 0, 0 ) );
        fw_scr_set_ink_one( window_bright_pen, rgb_to_cpc_color( 1, 1, 0 ) );
        fw_scr_set_ink_one( window_dark_pen, rgb_to_cpc_color( 0, 0, 0 ) );
        fw_scr_set_border_one( rgb_to_cpc_color( 0, 0, 0 ) );
        fw_txt_set_cursor( 25, 1 );
        cfwi_txt_str0_output( "\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x18-----"
                              "-----\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x18" );
        fw_txt_set_cursor( 1, 1 );
}

void draw_window( const char *title, const uint8_t top, const uint8_t bottom, const uint8_t left, const uint8_t right )
{
        fw_scr_set_border( 2, 2 );

        fw_txt_set_cursor( top, left );
        fw_txt_set_pen( window_bright_pen );
        fw_txt_wr_char( 0x96 );

        {
                int x = left;

                if ( title != 0 )
                {
                        while ( ++x < right )
                        {
                                fw_txt_wr_char( *title );

                                if ( *( ++title ) == 0 )
                                {
                                        break;
                                }
                        }
                }

                while ( ++x < right )
                {
                        fw_txt_wr_char( 0x9A );
                }

                fw_txt_wr_char( 0x9C );
        }

        {
                int y = top;

                while ( ++y < bottom )
                {
                        fw_txt_set_cursor( y, left );
                        fw_txt_set_pen( window_bright_pen );
                        fw_txt_wr_char( 0x95 );
                        fw_txt_set_cursor( y, right );
                        fw_txt_set_pen( window_dark_pen );
                        fw_txt_wr_char( 0x95 );

                }
        }

        fw_txt_set_cursor( bottom, left );
        fw_txt_wr_char( 0x93 );
        {
                int x = left;

                while ( ++x < right )
                {
                        fw_txt_wr_char( 0x9A );
                }

                fw_txt_wr_char( 0x99 );
        }
        fw_txt_set_pen( text_pen );
}

void radioButtonDraw( const ui_element_t *const element )
{
        const bool selected = ( element->data == global_model.grid.dimensions.row );
        fw_txt_set_pen( selected ? window_bright_pen : text_pen );
        fw_txt_set_cursor( element->y, element->x );
        fw_txt_wr_char( ' ' );
        fw_txt_wr_char( selected ? cpc_circle_full : cpc_circle_open );
        fw_txt_wr_char( ' ' );
        cfwi_txt_str0_output( element->text );
}

void checkBoxDraw( const ui_element_t *const element )
{
        const bool selected = ( global_model.playerEnableBits & element->data );
        fw_txt_set_cursor( element->y, element->x );
        fw_txt_wr_char( ' ' );
        fw_txt_set_pen( selected ? window_bright_pen : text_pen );
        fw_txt_wr_char( selected ? cpc_square_full : cpc_square_open );
        fw_txt_wr_char( ' ' );
        fw_txt_set_pen( text_pen );
        cfwi_txt_str0_output( element->text );
}

/*void textInputDraw( const ui_element_t *const element )
{
        fw_txt_set_cursor( element->y, element->x );
        cfwi_txt_str0_output( " " );
        cfwi_txt_str0_output( element->text );
        }*/

void buttonDraw( const ui_element_t *const element )
{
        fw_txt_set_cursor( element->y, element->x );
        cfwi_txt_str0_output( " " );
        cfwi_txt_str0_output( element->text );
}


void config_gui_mark_selected_element( const ui_element_t *const element, const char c )
{
        fw_txt_set_cursor( element->y, element->x );
        fw_txt_set_pen( window_bright_pen );
        fw_txt_wr_char( c );
}
