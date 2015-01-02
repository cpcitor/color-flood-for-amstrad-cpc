#include "stdio.h"

#include <cfwi/cfwi.h>

#include "platform.h"
#include "platform_ui.h"
#include "../model.h"
#include "../controller.h"





enum { cf_grid_byte_offset_from_screen_start = 16 };

#define draw_one_byte() screen_write(pos_local, value); ++pos_local
#define grid_origin(row, col, bytes_per_cell_width, chars_height_per_cell_height) ((screen + row * char_stride * chars_height_per_cell_height + col * bytes_per_cell_width + cf_grid_byte_offset_from_screen_start))

const uint8_t state2byte[CF_STATECOUNT] =
{
        0x0C, /* 00001100 2 */
        0xCC, /* 11001100 3 */
        0x30, /* 00110000 4 */
        0xF0, /* 11000000 5 */
        0x3C, /* 00111100 6 */
        0xFC, /* 11111100 7 */
        0x80,
        0x08
};
typedef void cell_draw_function( uint8_t row, uint8_t col, cf_cellState_t const state );

void cf_cell_draw_12( uint8_t row, uint8_t col, cf_cellState_t const state )
{
        uint8_t value = state2byte[state];
        {
                const uint8_t bytes_per_cell_width = 4;
                uint8_t *pos_global = grid_origin( row, col, bytes_per_cell_width, 2 );
                uint8_t *pos_this_sel = pos_global;
                uint8_t *pos_local;
#define draw_one_line_of_four_bytes() pos_local = pos_this_sel; draw_one_byte(); draw_one_byte(); draw_one_byte(); draw_one_byte(); pos_this_sel += line_stride;
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                pos_this_sel = pos_global + char_stride;
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
                draw_one_line_of_four_bytes();
        }
}

void cf_cell_draw_16( uint8_t row, uint8_t col, cf_cellState_t const state )
{
        uint8_t value = state2byte[state];
        {
                const uint8_t bytes_per_cell_width = 3;
                uint8_t *pos_this_sel = line_to_ptr[row * 12] + cf_grid_byte_offset_from_screen_start + col * bytes_per_cell_width;
                uint8_t *pos_local;
                uint8_t this_cell_row_i;

                for ( this_cell_row_i = 0; this_cell_row_i < 12; this_cell_row_i++ )
                {
                        pos_local = pos_this_sel;
                        draw_one_byte();
                        draw_one_byte();
                        draw_one_byte();
                        screen_next_line( pos_this_sel );
                }
        }
}

void cf_cell_draw_24( uint8_t row, uint8_t col, cf_cellState_t const state )
{
        uint8_t value = state2byte[state];
        {
                const uint8_t bytes_per_cell_width = 2;
                uint8_t *pos_this_sel = grid_origin( row, col, bytes_per_cell_width, 1 );
                uint8_t *pos_local;
#define draw_one_line_of_two_bytes() pos_local = pos_this_sel; draw_one_byte(); draw_one_byte(); pos_this_sel += line_stride;
                draw_one_line_of_two_bytes();
                draw_one_line_of_two_bytes();
                draw_one_line_of_two_bytes();
                draw_one_line_of_two_bytes();
                draw_one_line_of_two_bytes();
                draw_one_line_of_two_bytes();
                draw_one_line_of_two_bytes();
                draw_one_line_of_two_bytes();
        }
}

void cf_grid_draw( const cf_grid_t *const this_gris )
{
        int8_t row = this_gris->dimensions.row;

        cell_draw_function *cdf;

        if ( ( this_gris->dimensions.row > 16 ) || ( this_gris->dimensions.col > 16 ) )
        {
                cdf = cf_cell_draw_24;
        }
        else
        {
                if ( ( this_gris->dimensions.row > 12 ) || ( this_gris->dimensions.col > 12 ) )
                {
                        cdf = cf_cell_draw_16;
                }
                else
                {
                        cdf = cf_cell_draw_12;
                }
        }

        while ( --row >= 0 )
        {
                int8_t col = this_gris->dimensions.col;

                while ( --col >= 0 )
                {
                        cf_cellState_t state = this_gris->cell[row][col];

                        if ( state >= CF_STATECOUNT )
                        {
                                printf( "ERR r=%d c=%d s=%d\n", row, col, state );
                        }

                        cdf( row, col, state );
                }
        }
}

void cf_model_draw( const cf_model_t *const model )
{
        cf_grid_draw( &model->grid );
}

void show_key_color_association()
{
        const uint8_t xmin = 0;
        const uint8_t xmax = 38;
        uint16_t ymin = 398;
        const uint8_t yheight = 22;

        fw_gra_win_width( xmin, xmax );
        fw_gra_set_pen( 0 ); // FIXME hard-coded color number;

        {
                const key_to_action_t *ktap;

                for ( ktap = key_to_action; ktap < ( key_to_action + key_to_action_count ); ktap++ )
                {
                        if ( ktap->color >= CF_COLORCOUNT )
                        {
                                break;
                        }

                        {
                                uint8_t ink_color = ktap->color + 2;

                                fw_gra_set_paper( ink_color );
                        }

                        fw_gra_win_height( ymin, ymin - yheight );
                        fw_gra_clear_window();

                        {
                                char c = ktap->character;
                                fw_gra_move_absolute( 4, ymin - 4 );
                                fw_gra_wr_char( ktap->character );
                        }

                        ymin = ymin - yheight - 4;
                }
        }
}
