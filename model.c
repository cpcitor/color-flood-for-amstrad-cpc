#include <stdbool.h>

#include "log.h"

#include "model.h"

#include "platform.h"
#include "platform_view.h"

#include "stdio.h"

cf_model_t global_model;

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
                                cf_cellState_t state = ( row * col ) % CF_COLORCOUNT;
                                this_grid->cell[row][col] = state;
                                //printf( " c=%d", col );

                        }
                }
        }
}

void cf_model_init( cf_model_t *const this_model )
{
        assert( this_model->playerCount < CF_MAXPLAYERCOUNT );
        //assert( processed >= CF_STATECOUNT );
        //assert( to_process >= CF_STATECOUNT );

        cf_grid_init( &( this_model->grid ) );

        // FIXME initialize domainAreas[iplayer]

        {
                cf_coordinates_t *iph = &( this_model->playerHomes[0] );

                iph->row = 0;
                iph->col = 0;
                iph++;

                {
                        uint8_t maxRowCol = CF_MAXGRIDSIZE - 1;

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

#define isObstacle(cellState, oldState, newState) ((cellState==oldState)?false:\
                ((cellState==to_process)?false:\
                 true))

void walkTillObstacle( cf_grid_t *this_grid, uint8_t row, uint8_t col, cf_cellState_t oldState, cf_cellState_t newState, sint8_t direction )
{
        silmark();
        dbgvar_d( row );
        dbgvar_d( col );
        dbgvar_d( direction );
        dbglog_nl();

        cf_grid_draw( this_grid );

        do
        {
                this_grid->cell[row][col] = processed;

                silmsg( "marking %d,%d processed", row, col );
                dbgvar_d( col );
                dbglog_nl();

                if ( row > 0 )
                {
                        cf_cellState_t localStateNorth = this_grid->cell[row - 1][col];
                        dbgvar_d( localStateNorth );

                        if ( !isObstacle( localStateNorth, oldState, newState ) )
                        {
                                this_grid->cell[row - 1][col] = to_process;
                                silmsg( "marking %d,%d to_process", row, col );
                        }
                }

                if ( row < this_grid->dimensions.row - 1 )
                {
                        cf_cellState_t localStateSouth = this_grid->cell[row + 1][col];
                        dbgvar_d( localStateSouth );

                        if ( !isObstacle( localStateSouth, oldState, newState ) )
                        {
                                this_grid->cell[row + 1][col] = to_process;
                                silmsg( "marking %d,%d to_process", row, col );
                        }
                }

                {
                        sint8_t newCol = col + direction;

                        dbgvar_d( newCol );
                        dbglog_nl();

                        if ( newCol < 0 )
                        {
                                silmsg( "newCol < 0, exiting" );
                                return;
                        }

                        if ( ( ( uint8_t )newCol ) >= this_grid->dimensions.col ) // here we know newCol is positive so we can cast it to allow comparison.
                        {
                                return;
                        }

                        col = newCol;
                        dbgvar_d( col );
                        dbglog_nl();
                }

                {
                        cf_cellState_t localState = this_grid->cell[row][col];
                        dbgvar_d( localState );

                        if ( isObstacle( localState, oldState, newState ) )
                        {
                                return;
                        }
                }
        }
        while ( 1 );
}

uint16_t fillColor( cf_grid_t *this_grid,
                    uint8_t startRow,
                    uint8_t startCol,
                    cf_cellState_t oldState,
                    cf_cellState_t newState )
{
        silmark();
        dbgvar_d( startRow );
        dbgvar_d( startCol );
        dbglog_nl();

        cf_grid_draw( this_grid );

        this_grid->cell[startRow][startCol] = to_process;

        // First pass: mark to_process and processed.
        {
                uint8_t foundPointsToProcess;

                do
                {
                        foundPointsToProcess = 0;
                        {
                                sint8_t row = this_grid->dimensions.row;

                                while ( --row >= 0 )
                                {
                                        sint8_t col = this_grid->dimensions.col;

                                        while ( --col >= 0 )
                                        {
                                                cf_cellState_t localState = this_grid->cell[row][col];

                                                if ( localState == to_process )
                                                {
                                                        foundPointsToProcess = true;
                                                        this_grid->cell[row][col] = processed;

                                                        walkTillObstacle( this_grid, row, col, oldState, newState, 1 );
                                                        walkTillObstacle( this_grid, row, col, oldState, newState, -1 );
                                                }
                                        }
                                }
                        }
                }
                while ( foundPointsToProcess != 0 );

                // Could be optimized for speed by not looping all grid each time.
        }

        cf_grid_draw( this_grid );

        //Second pass: mark processed to newstate and count them.

        {
                uint16_t newArea = 0;

                sint8_t row = this_grid->dimensions.row;

                while ( --row >= 0 )
                {
                        sint8_t col = this_grid->dimensions.col;

                        while ( --col >= 0 )
                        {
                                cf_cellState_t localState = this_grid->cell[row][col];

                                if ( localState == processed )
                                {
                                        this_grid->cell[row][col] = newState;
                                        newArea++;
                                }
                        }
                }

                cf_grid_draw( this_grid );
                silmsg( "== return %d ==" NL, newArea );

                return newArea;
        }
}

/** Return value: 0 if okay, 1+playerindex if color chosen was same as playerindex' current color. */
uint8_t cf_model_play( cf_model_t *const this_model, cf_cellState_t const newState )
{
        uint8_t iplayer = this_model->nextPlayer;
        // FIXME check if color is different from any player's current color.

        cf_coordinates_t *fillStartCoordinates = &( this_model->playerHomes[iplayer] );

        cf_grid_t *grid = &this_model->grid;

        cf_cellState_t oldState = grid->cell[fillStartCoordinates->row][fillStartCoordinates->col];

        uint16_t newDomainArea = fillColor( grid,
                                            fillStartCoordinates->row,
                                            fillStartCoordinates->col,
                                            oldState,
                                            newState );

        this_model->domainAreas[iplayer] = newDomainArea;

        return 0;
}
