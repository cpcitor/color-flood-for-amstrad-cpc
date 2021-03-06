#include "stdio.h"

#include <cfwi/cfwi.h>

#include "platform.h"
#include "platform_ui.h"
#include "platform_view.h"
#include "../print.h"
#include "../model.h"
#include "../controller.h"
#include "../log.h"
#include "widget_style.h"



static uint8_t cf_grid_byte_offset_from_screen_start;

#define draw_one_byte() screen_write(pos_local, value); ++pos_local
#define grid_origin(row, col, bytes_per_cell_width, chars_height_per_cell_height) ((screen + row * char_stride * chars_height_per_cell_height + col * bytes_per_cell_width + cf_grid_byte_offset_from_screen_start))

enum
{
        PIXEL_ENCODING_BIT_0 = 0x40,
        PIXEL_ENCODING_BIT_1 = 0x04,
        PIXEL_ENCODING_BIT_2 = 0x10,
        PIXEL_ENCODING_BIT_3 = 0x01,
};

static const uint8_t state2byte[CF_STATECOUNT] =
{
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_1 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_1 + PIXEL_ENCODING_BIT_0 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_2 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_2 + PIXEL_ENCODING_BIT_0 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_2 + PIXEL_ENCODING_BIT_1 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_2 + PIXEL_ENCODING_BIT_1 + PIXEL_ENCODING_BIT_0 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_3 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_3 + PIXEL_ENCODING_BIT_0 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_3 + PIXEL_ENCODING_BIT_1 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_3 + PIXEL_ENCODING_BIT_1 + PIXEL_ENCODING_BIT_0 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_3 + PIXEL_ENCODING_BIT_2 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_3 + PIXEL_ENCODING_BIT_2 + PIXEL_ENCODING_BIT_0 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_3 + PIXEL_ENCODING_BIT_2 + PIXEL_ENCODING_BIT_1 ) ),
        ( uint8_t )( 3 * ( PIXEL_ENCODING_BIT_3 + PIXEL_ENCODING_BIT_2 + PIXEL_ENCODING_BIT_1 + PIXEL_ENCODING_BIT_0 ) ),
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
                uint8_t this_cell_row_i;

                for ( this_cell_row_i = 0; this_cell_row_i < 12; this_cell_row_i++ )
                {
                        uint8_t *pos_local = pos_this_sel;
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

static uint8_t player_bar_width_exponent_to_adapt_to_screen_width;

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

        cf_grid_byte_offset_from_screen_start = 16;

        player_bar_width_exponent_to_adapt_to_screen_width = 10;
        cf_view_on_area_grow(2);
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

void cf_view_on_area_grow( uint16_t newArea )
{
        uint8_t old_exponent = player_bar_width_exponent_to_adapt_to_screen_width;

        dbgvar_d( 1, old_exponent );

        while ( ( ( newArea << player_bar_width_exponent_to_adapt_to_screen_width ) >= 640) && (player_bar_width_exponent_to_adapt_to_screen_width>0))
        {
            --player_bar_width_exponent_to_adapt_to_screen_width;
        }

        if (old_exponent == player_bar_width_exponent_to_adapt_to_screen_width)
        {
            return;
        }

        dbgvar_d( 1, player_bar_width_exponent_to_adapt_to_screen_width );
        
        fw_txt_win_enable( 0, 19, 24, 24);
        fw_txt_clear_window();
        CDTC_ON_DEBUGLEVEL_GREATER_THAN_1( fw_txt_win_enable( 0, 19, 4, 23) );
        
        if ( player_bar_width_exponent_to_adapt_to_screen_width >= 3 )
        {
            uint8_t multiplier = 1 << player_bar_width_exponent_to_adapt_to_screen_width;
            
            uint16_t x = multiplier - 1;
            
            fw_gra_set_pen( 15 );
            while (x < 640)
            {
                dbgvar_d( 1, x );
                
                fw_gra_move_absolute( x, 0);
                fw_gra_line_relative( 0, (total_height << 1) - 3);
                x += multiplier;
            }
        }

        CDTC_ON_DEBUGLEVEL_GREATER_THAN_1( cf_pause() );
}

void cf_player_area_bars( const cf_model_t *const this_model )
{
        // static const int total_height_exponent = 3;
        // static const int total_height = 1 << total_height_exponent; // SDCC claims "Initializer element is not constant"
        uint8_t iplayer = CF_MAXPLAYERCOUNT;

        while ( (iplayer--) > 0 )
        {
                if ( is_player_enabled( this_model, iplayer ) )
                {
                        uint8_t fwy = iplayer << 2;
                        const uint16_t area = this_model->domainAreas[iplayer];
                        const cf_cellState_t player_state = cf_model_get_player_cellstate( this_model, iplayer );
                        const uint8_t color = state_to_color( player_state );
                        fw_gra_move_absolute( 0, fwy );
                        fw_gra_set_pen( color );
                        fw_gra_line_absolute( area << (player_bar_width_exponent_to_adapt_to_screen_width), fwy );
                        fw_gra_set_pen( 0 );
                        fw_gra_line_absolute( 640, fwy );
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

typedef struct text_coordinates_t
{
        uint8_t left;
        uint8_t top;
} text_coordinates_t;

static const text_coordinates_t player_windows[CF_MAXPLAYERCOUNT] =
{
        { 0, 0, 0 },
        { 16, 0 },
        { 16, 22 },
        { 0, 22 },
};

void platform_player_controls_show_or_hide( uint8_t ip, bool show )
{
        {
                const text_coordinates_t *const w = &( player_windows[ip] );
                const uint8_t winwidth = 4;
                const uint8_t winheight = 2;
                fw_txt_win_enable( w->left, w->left + ( winwidth - 1 ), w->top, w->top + ( winheight - 1 ) );
                fw_txt_clear_window();
        }

        if ( show )
        {
                const player_key_to_action_t *const kta = &( player_key_to_action_array[ip] );
                fw_txt_output( 0xf4 );
                fw_txt_output( 0xe0 );
                fw_txt_output( 0xf5 );
                fw_txt_output( ' ' );
                fw_txt_output( kta->previous_color );
                fw_txt_output( kta->confirm );
                fw_txt_output( kta->next_color );
        }

        CDTC_ON_DEBUGLEVEL_GREATER_THAN_1( fw_txt_win_enable( 0, 19, 0, 23) );
}

void platform_show_who_plays_next( const cf_model_t *const this_model )
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

        platform_player_controls_show_or_hide( ip, true );
}

void platform_hide_who_plays_next( const cf_model_t *const this_model )
{
        const uint8_t ip = this_model->nextPlayer;
        platform_player_controls_show_or_hide( ip, false );
}

enum
{
        color_pads_xmin = 0,
        color_pads_xmax = 38,
        color_pads_yinnerheight = 22,
        color_pads_ygap = 4,
};

#define __COLOR_PADS_HEIGHT ((color_pads_yinnerheight+color_pads_ygap)*CF_COLORCOUNT-color_pads_ygap)

//const uint16_t color_pads_height = __COLOR_PADS_HEIGHT;
enum
{
        color_pads_ytop = ( ( 398 + __COLOR_PADS_HEIGHT ) / 2 ),
        color_pads_ybottom = ( ( 398 - __COLOR_PADS_HEIGHT ) / 2 ),
        color_pads_youterheight = ( color_pads_yinnerheight + color_pads_ygap ),
};

cf_cellState_t platform_show_possible_next_moves( cf_model_t *const this_model )
{
        uint16_t ytop = color_pads_ybottom - color_pads_ygap;

        cf_cellState_t first_allowed_color = CF_STATECOUNT; /* Set it to avoid warning. */

        dbglog( 5, "platform_show_possible_next_moves" NL );

        fw_gra_win_width( color_pads_xmin, color_pads_xmax );
        fw_gra_set_pen( 0 ); // FIXME hard-coded color number;

        {
                cf_cellState_t icolor = CF_COLORCOUNT;

                do
                {
                        icolor--;

                        dbgvar_d( 5, icolor );

                        ytop = ytop + color_pads_youterheight;

                        {
                                uint8_t ink_color = icolor + 2;

                                fw_gra_set_paper( ink_color );
                        }

                        dbgvar_d( 5, ytop );
                        dbglog( 1, NL );

                        fw_gra_win_height( ytop, ytop - color_pads_yinnerheight );
                        fw_gra_clear_window();

                        if ( cf_model_is_color_allowed_for_current_player( this_model, icolor ) )
                        {
                                first_allowed_color = icolor;
                        }
                        else
                        {
                                fw_gra_move_absolute( 4, ytop - 4 );
                                fw_gra_wr_char( 0xCB /* CROSS */ );
                        }
                }
                while ( icolor != 0 );
        }
        fw_gra_initialise();

        return first_allowed_color;
}

void platform_show_player_wished_color( cf_cellState_t player_wished_action )
{
        uint16_t ytop = color_pads_ytop - color_pads_youterheight * player_wished_action;

        fw_gra_win_width( color_pads_xmax + 4, ( color_pads_xmax + 2 ) * 2 );
        fw_gra_win_height( color_pads_ytop, color_pads_ybottom );
        fw_gra_set_paper( 0 ); // FIXME hard-coded color number;
        fw_gra_clear_window();

        dbgvar_d( 5, ytop );

        fw_gra_set_pen( 1 ); // FIXME hard-coded color number;
        fw_gra_move_absolute( color_pads_xmax + 4, ytop - 4 );
        fw_gra_wr_char( 0xf2 );
        fw_gra_initialise();
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

                fw_txt_set_pen( text_pen );
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
                                const cf_cellState_t player_state = cf_model_get_player_cellstate( &global_model, iplayer );
                                const uint8_t color = state_to_color( player_state );
                                fw_txt_set_pen( color );

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
        cf_platform_prepare_screen_for_game_board();
        cf_grid_byte_offset_from_screen_start = 0;
        cf_model_draw( this_model );
        fw_txt_win_enable( 12, 19, 0, 23 );
        fw_txt_set_pen( text_pen );
        cfwi_txt_str0_output( "Game" NL "Over" NL NL );
        cf_view_print_podium( podium );

        fw_txt_set_pen( text_pen );
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
        fw_txt_set_pen( text_pen );
}
