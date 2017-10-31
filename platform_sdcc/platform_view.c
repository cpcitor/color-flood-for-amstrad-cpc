#include "stdio.h"

#include <cfwi/cfwi.h>

#include "platform.h"
#include "platform_ui.h"
#include "platform_view.h"
#include "../print.h"
#include "../model.h"
#include "../controller.h"
#include "../log.h"



static uint8_t cf_grid_byte_offset_from_screen_start;

#define draw_one_byte() screen_write(pos_local, value); ++pos_local
#define grid_origin(row, col, bytes_per_cell_width, chars_height_per_cell_height) ((screen + row * char_stride * chars_height_per_cell_height + col * bytes_per_cell_width + cf_grid_byte_offset_from_screen_start))

const uint8_t state2byte[CF_STATECOUNT] =
{
        0x0C, /* 00001100 2 */
        0xCC, /* 11001100 3 */
        0x30, /* 00110000 4 */
        0xF0, /* 11110000 5 */
        0x3C, /* 00111100 6 */
        0xFC, /* 11111100 7 */
#if CF_COLORCOUNT > 6
        0x03,
        0xC3,
        0x0F,
        0xCF,
        0x33,
        0xF3,
        0x3F,
        0xFF,
#endif /* CF_COLORCOUNT > 6 */
        0x80,
        0x08
};
typedef void cell_draw_function( uint8_t row, uint8_t col, cf_cellState_t const state );

static struct
{
        cell_draw_function *cdf;
        uint8_t bytes_per_cell_width;
} viewparameters;

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

void cf_view_init( cf_model_t *model )
// setup_viewparameters(const cf_grid_t *const this_grid)
{
        cf_grid_t *this_grid = &model->grid;

        if ( ( this_grid->dimensions.row > 16 ) || ( this_grid->dimensions.col > 16 ) )
        {
                viewparameters.cdf = cf_cell_draw_24;
                viewparameters.bytes_per_cell_width = 2;
        }
        else
        {
                if ( ( this_grid->dimensions.row > 12 ) || ( this_grid->dimensions.col > 12 ) )
                {
                        viewparameters.cdf = cf_cell_draw_16;
                        viewparameters.bytes_per_cell_width = 3;
                }
                else
                {
                        viewparameters.cdf = cf_cell_draw_12;
                        viewparameters.bytes_per_cell_width = 4;
                }
        }

        show_key_color_association();
        cf_grid_byte_offset_from_screen_start = 16;
}

void cf_grid_draw( const cf_grid_t *const this_grid )
{
        int8_t row = this_grid->dimensions.row;


        while ( --row >= 0 )
        {
                int8_t col = this_grid->dimensions.col;

                while ( --col >= 0 )
                {
                        cf_cellState_t state = this_grid->cell[row][col];

#ifdef DEBUG

                        if ( state >= CF_STATECOUNT )
                        {
                                printf( "ERR r=%d c=%d s=%d\n", row, col, state );
                        }

#endif /* DEBUG */

                        viewparameters.cdf( row, col, state );
                }
        }
}

#define total_height_exponent 3
#define total_height (1 << total_height_exponent)

void cf_player_area_bars( const cf_model_t *const this_model )
{
        // static const int total_height_exponent = 3;
        // static const int total_height = 1 << total_height_exponent; // SDCC claims "Initializer element is not constant"
        int8_t y = 1 << total_height_exponent;

        while ( y-- != 0 ) // small hack, not really necessary, for shorter ASM
        {
                const uint8_t iplayer = ( y * CF_MAXPLAYERCOUNT ) >> total_height_exponent;

                if ( is_player_enabled( this_model, iplayer ) )
                {
                        const uint16_t area = this_model->domainAreas[iplayer];
                        const cf_cellState_t player_state = cf_model_get_current_player_state( this_model, iplayer );
                        const uint8_t color = state_to_color( player_state );
                        fw_gra_set_pen( color );
                        fw_gra_move_absolute( 0, y << 1 );
                        fw_gra_line_relative( area << 2, 0 ); // A grid 18x18 has area 240, (area<<2) will reach limit when one player area >= 160, not a big deal.
                }
        }
}

void cf_model_draw( const cf_model_t *const model )
{
        cf_grid_draw( &model->grid );
        cf_player_area_bars( model );
}

uint8_t state_to_color( cf_cellState_t state )
{
        return ( ( uint8_t )state + 2 );
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
        fw_gra_initialise();
}

char platform_prompt_next_move( cf_model_t *const this_model )
{
        const uint8_t ip = this_model->nextPlayer;
        const cf_coordinates_t *const ph = &( this_model->playerHomes[ip] );

        const uint8_t cellsize_fw = viewparameters.bytes_per_cell_width * 8;

        //printf( "%u", this_model->nextPlayer );

        uint16_t fwx = cf_grid_byte_offset_from_screen_start * 8 + ph->col * cellsize_fw
                       /*+ 4 * factor*/
                       ;
        uint16_t fwy = 398 - ph->row * cellsize_fw
                       /*- 4 * factor;*/
                       ;

        const uint8_t incellsize_fw_x = cellsize_fw - 4;
        const uint8_t incellsize_fw_y = cellsize_fw - 2;

        fw_gra_set_pen( 0 );

        fw_gra_move_absolute( fwx, fwy );
        fw_gra_line_relative( incellsize_fw_x, -incellsize_fw_y );
        fw_gra_move_relative( -incellsize_fw_x, 0 );
        fw_gra_line_relative( incellsize_fw_x, incellsize_fw_y );

        return fw_km_wait_key();
}


void cf_view_print_podium( const cf_podium_t *const podium )
{
        int irow;

        for ( irow = 0; irow < CF_PODIUM_ROW_COUNT; irow++ )
        {
                const cf_podium_row_t *const row = &( podium->row[irow] );

                uint8_t iseat = 0;

                uint16_t area = row->area;

                if ( area == 0 )
                {
                        break;
                }

                cfwi_txt_str0_output( "Rank " );
                fw_txt_output( '1' + irow ); // Assumes CF_PODIUM_ROW_COUNT <=9
                cfwi_txt_str0_output( NL );

                cfwi_txt_str0_output( "Area " );
                pr_uint( area );
                cfwi_txt_str0_output( NL );

                for ( iseat = 0; iseat < CF_PODIUM_SEATS_PER_ROW; iseat++ )
                {
                        const cf_player_i *const seat = &( row->seat[iseat] );
                        const uint8_t iplayer = *seat;

                        if ( iplayer != CF_PODIUM_EMPTY_SEATS_VALUE )
                        {

                                cfwi_txt_str0_output( "Player " );
                                fw_txt_output( 0xD4 + iplayer );
                                //fw_txt_output( '1' + irow ); // Assumes CF_MAXPLAYERCOUNT <=9
                                cfwi_txt_str0_output( NL );
                        }
                }

                // cfwi_txt_str0_output( NL ); No because "Player N" already overflows.
        }
}

void cf_view_display_endgame_pause( cf_model_t *this_model, cf_podium_t *podium )
{
        fw_scr_clear();
        cf_grid_byte_offset_from_screen_start = 0;
        cf_model_draw( this_model );
        fw_txt_win_enable( 12, 19, 0, 24 );
        cfwi_txt_str0_output( "Game" NL "Over" NL NL );
        cf_view_print_podium( podium );

        cfwi_txt_str0_output( "Press " NL "space" NL "to" NL "continue" );

        {
                char answer;

                do
                {
                        answer = fw_km_wait_key();
                }
                while ( answer != ' ' );
        }
        fw_txt_clear_window();
}
