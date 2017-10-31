#include "../widget_base.h"
#include "platform.h"
#include "../print.h"

const int background_pen = 0;
const int text_pen = 1;
const int window_bright_pen = 2;
const int window_dark_pen = 3;
//const int input_pen = 3;

void cf_platform_prepare_for_config_screen()
{
        fw_scr_set_ink_one( background_pen, rgb_to_cpc_color( 1, 2, 1 ) );
        fw_scr_set_ink_one( text_pen, rgb_to_cpc_color( 0, 0, 0 ) );
        fw_scr_set_ink_one( window_bright_pen, rgb_to_cpc_color( 2, 2, 2 ) );
        fw_scr_set_ink_one( window_dark_pen, rgb_to_cpc_color( 0, 1, 0 ) );
        fw_scr_set_border_one( rgb_to_cpc_color( 1, 1, 2 ) );
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
                        /* fw_txt_set_cursor( 1, 1 );
                        pr_uint( y );
                        fw_txt_wr_char( ',' );
                        pr_uint( left );
                        fw_txt_wr_char( ',' );
                        pr_uint( right );
                        cf_pause(); */
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

void radioButtonDraw( ui_element_t *element )
{
        fw_txt_set_cursor( element->y, element->x );
//pr_int( element->y );
//pr_int( element->x );

        cfwi_txt_str0_output( " * " );
        cfwi_txt_str0_output( element->text );
}

void checkBoxDraw( ui_element_t *element )
{
        fw_txt_set_cursor( element->y, element->x );
        /* cfwi_txt_str0_output( "row " ); */
        /* pr_int( element->y ); */
        /* cfwi_txt_str0_output( "column " ); */
        /* pr_int( element->x ); */
        cfwi_txt_str0_output( " [ ] " );
        cfwi_txt_str0_output( element->text );
}

void textInputDraw( ui_element_t *element )
{
        fw_txt_set_cursor( element->y, element->x );
        // pr_int( element->y );
        // pr_int( element->x );
        cfwi_txt_str0_output( " " );
        cfwi_txt_str0_output( element->text );
}

void buttonDraw( ui_element_t *element )
{
        fw_txt_set_cursor( element->y, element->x );
        // pr_int( element->y );
        // pr_int( element->x );
        cfwi_txt_str0_output( " " );
        cfwi_txt_str0_output( element->text );
}

