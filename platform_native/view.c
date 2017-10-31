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
                                const cf_cellState_t state = cf_model_get_current_player_state( this_model, iplayer );
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

void show_key_color_association()
{
        int ik;

        for ( ik = 0; ik < key_to_action_count; ik++ )
        {
                const key_to_action_t *const kta = &key_to_action[ik];
                printf( "Key '%c', player %d, state/color %d\n", kta->character, kta->player, kta->color );
        }
}

char platform_prompt_next_move( cf_model_t *const this_model )
{
        ( void )this_model;
        show_key_color_association();
        printf( "Enter your choice:\n" );
        char user_choice_char = getchar();
        return user_choice_char;
}

void cf_view_dump_podium( cf_podium_t *podium )
{
        fprintf( stderr, "[Podium: \n" );
        int irow;

        for ( irow = 0; irow < CF_PODIUM_ROW_COUNT; irow++ )
        {
                cf_podium_row_t *row = &( podium->row[irow] );

                uint8_t iseat = 0;

                fprintf( stderr, "Area %03u ", row->area );

                for ( iseat = 0; iseat < CF_PODIUM_SEATS_PER_ROW; iseat++ )
                {
                        cf_player_i *seat = &( row->seat[iseat] );

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

                cf_view_dump_podium( podium );
                fprintf( stderr, "\n" );
        }

        fprintf( stderr, "********** Game over **********" );

        global_model.playerEnableBits = 0;
}
