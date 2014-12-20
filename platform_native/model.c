#include "platform.h"
#include "../model.h"

#include <stdio.h>

void cf_coordinates_dump( cf_coordinates_t *this_coordinates )
{
        fprintf( stderr, "(row %d, col %d)", this_coordinates->row, this_coordinates->col );
}

void cf_grid_dump( cf_grid_t *this_grid )
{
        assert( this_grid->dimensions.row <= CF_MAXGRIDSIZE );
        assert( this_grid->dimensions.col <= CF_MAXGRIDSIZE );

        fprintf( stderr, "[\n" );
        {
                sint8_t row = this_grid->dimensions.row;

                while ( --row >= 0 )
                {
                        fprintf( stderr, "[ " );
                        {
                                sint8_t col = this_grid->dimensions.col;

                                while ( --col >= 0 )
                                {

                                        fprintf( stderr, "%d ", this_grid->cell[row][col] );

                                }
                        }
                        fprintf( stderr, "]\n" );
                }

                fprintf( stderr, "]\n" );
        }
}

void cf_model_dump( cf_model_t *this_model )
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
                cf_coordinates_t *iph = &( this_model->playerHomes[0] );
                fprintf( stderr, "[PlayerHomes: " );

                for ( iplayer = 0; iplayer < CF_MAXPLAYERCOUNT; iplayer++ )
                {
                        cf_coordinates_dump( &iph[iplayer] );
                        fprintf( stderr, "\t" );
                }

                fprintf( stderr, "]\n" );
        }

        fprintf( stderr, "]\n" );
}
