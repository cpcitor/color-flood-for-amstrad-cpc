#include "model.h"

#include "stdio.h"

void cf_grid_init( cf_grid_t *const this_grid )
{
        assert( this_grid->dimensions.row <= CF_MAXGRIDSIZE );
        assert( this_grid->dimensions.col <= CF_MAXGRIDSIZE );

        {
                sint8_t row = this_grid->dimensions.row;

                while ( --row >= 0 )
                {
                        sint8_t col = this_grid->dimensions.col;

                        //printf( "\r\nr=%d", row );

                        while ( --col >= 0 )
                        {
                                cf_cellState_t state = ( row * col ) % CF_STATECOUNT;
                                this_grid->cell[row][col] = state;
                                //printf( " c=%d", col );

                        }
                }
        }
}

void cf_model_init( cf_model_t *const this_model )
{
        assert( this_model->playerCount < CF_MAXPLAYERCOUNT );

        cf_grid_init( &( this_model->grid ) );

        {
                cf_coordinates_t *iph = &( this_model->playerHomes[0] );

                iph->row = 0;
                iph->col = 0;
                iph++;

                {
                        int maxRowCol = CF_MAXGRIDSIZE - 1;

                        if ( this_model->playerCount >= 3 )
                        {
                                iph->row = maxRowCol;
                                iph->col = 0;
                                iph++;
                        }

                        iph->row = maxRowCol;
                        iph->col = maxRowCol;
                        iph++;

                        iph->row = 0;
                        iph->col = maxRowCol;
                        iph++;
                }
        }

        this_model->nextPlayer = 0;
}

void play( cf_model_t *const thisModel, cf_cellState_t const chosenState )
{
        ( void )thisModel; // FIXME
        ( void )chosenState; // FIXME
}
