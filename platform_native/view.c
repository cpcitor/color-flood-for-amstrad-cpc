#include "platform.h"
#include "../model.h"

#include <stdio.h>

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
                 "playerCount=%d\n"
                 "nextPlayer=%d\n",
                 this_model,
                 this_model->playerCount,
                 this_model->nextPlayer
               );
        cf_grid_dump( &this_model->grid );

        {
                cf_player_i iplayer;
                const cf_coordinates_t *const iph = &( this_model->playerHomes[0] );
                fprintf( stderr, "[PlayerHomes: " );

                for ( iplayer = 0; iplayer < this_model->playerCount; iplayer++ )
                {
                        cf_coordinates_dump( &iph[iplayer] );
                        fprintf( stderr, "\t" );
                }

                fprintf( stderr, "]\n" );
        }

        fprintf( stderr, "]\n" );
}

void cf_model_draw( cf_model_t *const this_model )
{
        ( void ) this_model;
        // SDCC platform draw the grid, native code only dumps text.
        //cf_model_dump( this_model );
}

void cf_grid_draw( const cf_grid_t *const this_grid )
{
        cf_grid_dump( this_grid );
}
