#include "platform.h"
#include "../model.h"

#include "stdio.h"

#define draw_one_byte() screen_write(pos_local, value); ++pos_local
#define draw_one_line_of_two_bytes() pos_local = pos_this_sel; draw_one_byte(); draw_one_byte(); pos_this_sel += line_stride;
#define draw_one_line_of_four_bytes() pos_local = pos_this_sel; draw_one_byte(); draw_one_byte(); draw_one_byte(); draw_one_byte(); pos_this_sel += line_stride;

const uint8_t state2byte[CF_STATECOUNT] = { 0x0C, 0xCC, 0x30, 0xF0, 0x3C, 0xFC };
typedef void cell_draw_function( uint8_t row, uint8_t col, cf_cellState_t const state );

void cf_cell_draw_12( uint8_t row, uint8_t col, cf_cellState_t const state )
{
        uint8_t value = state2byte[state];
        {
                static const int bytes_per_cell_width = 4;
                uint8_t *pos_global = screen + row * char_stride * 2 + col * bytes_per_cell_width;
                uint8_t *pos_this_sel = pos_global;
                uint8_t *pos_local;
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

void cf_cell_draw_24( uint8_t row, uint8_t col, cf_cellState_t const state )
{
        uint8_t value = state2byte[state];
        {
                static const int bytes_per_cell_width = 2;
                uint8_t *pos_this_sel = screen + row * char_stride + col * bytes_per_cell_width;
                uint8_t *pos_local;
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

void cf_grid_draw( const cf_grid_t *const grid )
{
        sint8_t row = grid->dimensions.row;

        cell_draw_function *cdf;

        if ( ( grid->dimensions.row > 12 ) || ( grid->dimensions.col > 12 ) )
        {
                cdf = cf_cell_draw_24;
        }
        else
        {
                cdf = cf_cell_draw_12;
        }

        while ( --row >= 0 )
        {
                sint8_t col = grid->dimensions.col;

                while ( --col >= 0 )
                {
                        cf_cellState_t state = grid->cell[row][col];

                        if ( state >= CF_STATECOUNT )
                        {
                                printf( "r=%d c=%d col=%d ", row, col, state );
                        }

                        cdf( row, col, state );
                }
        }
}

void cf_model_draw( const cf_model_t *const model )
{
        cf_grid_draw( &model->grid );
}
