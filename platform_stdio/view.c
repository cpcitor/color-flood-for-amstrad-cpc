#include "platform.h"
#include "../model.h"
#include "../model_podium.h"
#include "../controller.h"

#include <stdio.h>

void cf_view_init( cf_model_t *model )
{
        ( void ) model;
        puts( "Welcome to Color flood portable interface.\n" );
}

void cf_view_on_area_grow( uint16_t newArea )
{
        fprintf( stderr, "cf_view_on_area_grow(%d)", newArea );
}

void cf_coordinates_dump( const cf_coordinates_t *const this_coordinates )
{
        fprintf( stderr, "(row %d, col %d)", this_coordinates->row, this_coordinates->col );
}

void cf_grid_dump( const cf_grid_t *const this_grid )
{
        assert( this_grid->dimensions.row <= CF_MAXGRIDSIZE );
        assert( this_grid->dimensions.col <= CF_MAXGRIDSIZE );

        fprintf( stderr, "cf_grid_t grid = { .dimensions = { .row = %d, .col= %d }, .cell = {\n",
                 this_grid->dimensions.row,
                 this_grid->dimensions.col );
        {
                uint8_t row;

                for ( row = 0; row < this_grid->dimensions.row; row++ )
                {
                        uint8_t col;
                        fprintf( stderr, "{ " );

                        for ( col = 0; col < this_grid->dimensions.col; col++ )
                        {
                                {
                                        fprintf( stderr, "%d, ", this_grid->cell[row][col] );

                                }
                        }

                        fprintf( stderr, "},\n" );
                }

                fprintf( stderr, "} };\n" );
        }
}

void cf_model_dump( const cf_model_t *const this_model )
{
        fprintf( stderr,
                 "[Model @%p\n"
                 "playerEnableBits=0x%x\n"
                 "nextPlayer=%d\n",
                 this_model,
                 this_model->playerEnableBits,
                 this_model->nextPlayer
               );
        cf_grid_dump( &this_model->grid );

        {
                cf_player_i iplayer;
                const uint16_t *const areas = &( this_model->domainAreas[0] );
                uint16_t unclaimedArea = this_model->grid.dimensions.row * this_model->grid.dimensions.col;

                fprintf( stderr, "[domainAreas: " );

                for ( iplayer = 0; iplayer < CF_MAXPLAYERCOUNT; iplayer++ )
                {
                        uint16_t area = areas[iplayer];

                        if ( is_player_enabled( this_model, iplayer ) )
                        {
                                unclaimedArea -= area;
                        }

                        fprintf( stderr, "%d ", area );
                }

                fprintf( stderr, "] UNCLAIMED=%d\n", unclaimedArea );
        }

        {
                cf_player_i iplayer;
                const cf_coordinates_t *const iph = &( this_model->playerHomes[0] );
                fprintf( stderr, "[PlayerHomes: " );

                for ( iplayer = 0; iplayer < CF_MAXPLAYERCOUNT; iplayer++ )
                {
                        cf_coordinates_dump( &iph[iplayer] );
                        fprintf( stderr, "\t" );
                }

                fprintf( stderr, "]\n" );
        }


        {
                cf_player_i iplayer;
                fprintf( stderr, "[PlayerStates: " );

                for ( iplayer = 0; iplayer < CF_MAXPLAYERCOUNT; iplayer++ )
                {
                        if ( is_player_enabled( this_model, iplayer ) )
                        {
                                const cf_cellState_t state = cf_model_get_player_cellstate( this_model, iplayer );
                                fprintf( stderr, "%d ", state );
                        }
                }

                fprintf( stderr, "]\n" );
        }


        fprintf( stderr, "Model]\n" );
}

void cf_model_draw( cf_model_t *const this_model )
{
        //( void ) this_model;
        // SDCC platform draw the grid, native code only dumps text.
        cf_model_dump( this_model );
}

void cf_grid_draw( const cf_grid_t *const this_grid )
{
        cf_grid_dump( this_grid );
}

void platform_show_who_plays_next( cf_model_t *const this_model )
{
        printf( "Next player is: %d\n", this_model->nextPlayer );
}

void platform_hide_who_plays_next( cf_model_t *const this_model )
{
        printf( "Player made their move: %d\n", this_model->nextPlayer );
}

cf_cellState_t platform_show_possible_next_moves( cf_model_t *const this_model )
{
        cf_cellState_t icolor;
        cf_cellState_t one_wished_color = ~0;

        for ( icolor = 0; icolor < CF_COLORCOUNT ; icolor++ )
        {
                bool okay = cf_model_is_color_allowed_for_current_player( this_model, icolor );

                if ( okay && ( ( one_wished_color ) == ( cf_cellState_t )~0 ) )
                {
                        one_wished_color = icolor;
                }

                printf( "Color %d is %s.\n", icolor, okay ? "OK" : "disallowed" );
        }

        return one_wished_color;
}

void platform_show_player_wished_color( cf_cellState_t player_wished_action )
{
        printf( "Player is considering color: %d\n", player_wished_action );
}


/*char platform_prompt_next_move( cf_model_t *const this_model )
{ FIXME
        ( void )this_model;
        show_key_color_association();
        printf( "Enter your choice:\n" );
        char user_choice_char = getchar();
        return user_choice_char;
}*/

void cf_view_print_podium( const cf_podium_t *const podium )
{
        fprintf( stderr, "[Podium: \n" );
        int irow;

        for ( irow = 0; irow < CF_PODIUM_ROW_COUNT; irow++ )
        {
                const cf_podium_row_t *const row = &( podium->row[irow] );

                uint8_t iseat = 0;

                fprintf( stderr, "Area %03u ", row->area );

                for ( iseat = 0; iseat < CF_PODIUM_SEATS_PER_ROW; iseat++ )
                {
                        const cf_player_i *const seat = &( row->seat[iseat] );

                        if ( ( *seat ) == CF_PODIUM_EMPTY_SEATS_VALUE )
                        {
                                fprintf( stderr, "_ " );
                        }
                        else
                        {
                                fprintf( stderr, "%d ", *seat );
                        }
                }

                fprintf( stderr, "\n" );
        }

        fprintf( stderr, "podium]\n" );
}

void cf_view_display_endgame_pause( cf_model_t *this_model, cf_podium_t *podium )
{
        fprintf( stderr, "********** Game over **********" );
        cf_model_dump( this_model );

        {
                cf_player_i iplayer;
                const uint16_t *const areas = &( this_model->domainAreas[0] );
                fprintf( stderr, "Player scores: \n" );

                for ( iplayer = 0; iplayer < CF_MAXPLAYERCOUNT; iplayer++ )
                {
                        if ( is_player_enabled( this_model, iplayer ) )
                        {
                                uint16_t area = areas[iplayer];
                                fprintf( stderr, "Player %u scored %u\n", iplayer, area );
                        }
                }

                cf_view_print_podium( podium );
                fprintf( stderr, "\n" );
        }

        fprintf( stderr, "********** Game over **********" );

        global_model.playerEnableBits = 0;
}
