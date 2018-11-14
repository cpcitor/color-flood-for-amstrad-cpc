#include <stdbool.h>

#include "log.h"

#include "model.h"

#include "platform.h"
#include "platform_view.h"

#include "stdio.h"
#include "stdlib.h" //rand()

cf_model_t global_model;

void cf_grid_init( cf_grid_t *const this_grid )
{
        assert( this_grid->dimensions.row <= CF_MAXGRIDSIZE );
        assert( this_grid->dimensions.col <= CF_MAXGRIDSIZE );
        assert( this_grid->dimensions.row > 0 );
        assert( this_grid->dimensions.col > 0 );

        {
                int8_t row = this_grid->dimensions.row;

                while ( --row >= 0 )
                {
                        int8_t col = this_grid->dimensions.col;

                        //printf( "\r\nr=%d", row );

                        while ( --col >= 0 )
                        {
                                cf_cellState_t state = ( ( uint8_t )rand() ) % CF_COLORCOUNT; // not exactly uniform but anyway
                                this_grid->cell[row][col] = state;
                                //printf( " c=%d", col );
                        }
                }

                // FIXME should ensure any two players can't have same color.
                // FIXME symmetry for fairness.
        }
}

void cf_model_init( cf_model_t *const this_model )
{
        assert(
                (
                        ( this_model->playerEnableBits )
                        &
                        ( ( ~( ( unsigned int )1 ) ) << CF_MAXPLAYERCOUNT )
                )
                == 0 );
        //assert( processed >= CF_STATECOUNT );
        //assert( to_process >= CF_STATECOUNT );

        cf_grid_init( &( this_model->grid ) );

        {
                cf_player_i iplayer;

                for ( iplayer = 0; iplayer < CF_MAXPLAYERCOUNT; iplayer++ )
                {
                        this_model->domainAreas[iplayer] = 0;
                }
        }

        // FIXME really initialize domainAreas[iplayer] from areas at startup (not always 1).

        {
                cf_coordinates_t *iph = &( this_model->playerHomes[0] );

                iph->row = 0;
                iph->col = 0;
                iph++;

                {
                        uint8_t maxRow = this_model->grid.dimensions.row - 1;
                        uint8_t maxCol = this_model->grid.dimensions.col - 1;

                        iph->row = 0;
                        iph->col = maxCol;
                        iph++;

                        iph->row = maxRow;
                        iph->col = maxCol;
                        iph++;

                        iph->row = maxRow;
                        iph->col = 0;
                        iph++;
                }
        }

        this_model->nextPlayer = 0;
}

#define isObstacle(cellState, oldState, newState) ((cellState==oldState)?false:\
                ((cellState==to_process)?false:\
                 true))

void walkTillObstacle( cf_grid_t *this_grid, uint8_t row, uint8_t col, cf_cellState_t oldState, int8_t direction )
{
        silmark( 2 );
        dbgvar_d( 3, row );
        dbgvar_d( 3, col );
        dbgvar_d( 3, direction );
        dbglog_nl( 3 );

        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 3, cf_grid_draw( this_grid ) );

        do
        {
                this_grid->cell[row][col] = processed;

                silmsg( 3, "marking %d,%d processed", row, col );

                if ( row > 0 )
                {
                        cf_cellState_t localStateNorth = this_grid->cell[row - 1][col];
                        dbgvar_d( 4, localStateNorth );

                        if ( !isObstacle( localStateNorth, oldState, newState ) )
                        {
                                this_grid->cell[row - 1][col] = to_process;
                                silmsg( 3, "marking %d,%d to_process", row, col );
                        }
                }

                if ( row < this_grid->dimensions.row - 1 )
                {
                        cf_cellState_t localStateSouth = this_grid->cell[row + 1][col];
                        dbgvar_d( 4, localStateSouth );

                        if ( !isObstacle( localStateSouth, oldState, newState ) )
                        {
                                this_grid->cell[row + 1][col] = to_process;
                                silmsg( 3, "marking %d,%d to_process", row, col );
                        }
                }

                {
                        int8_t newCol = col + direction;

                        dbgvar_d( 4, newCol );
                        dbglog_nl( 4 );

                        if ( newCol < 0 )
                        {
                                silmsg( 3, "newCol < 0, exiting" );
                                return;
                        }

                        if ( ( ( uint8_t )newCol ) >= this_grid->dimensions.col ) // here we know newCol is positive so we can cast it to allow comparison.
                        {
                                return;
                        }

                        col = newCol;
                        dbgvar_d( 4, col );
                        dbglog_nl( 4 );
                }

                {
                        cf_cellState_t localState = this_grid->cell[row][col];
                        dbgvar_d( 4, localState );

                        if ( isObstacle( localState, oldState, newState ) )
                        {
                                return;
                        }
                }
        }
        while ( 1 );
}

void fillColorToProcessedState( cf_grid_t *this_grid,
                                uint8_t startRow,
                                uint8_t startCol,
                                cf_cellState_t oldState )
{
        silmark( 1 );
        dbgvar_d( 2, startRow );
        dbgvar_d( 2, startCol );
        dbglog_nl( 2 );

        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 2, cf_grid_draw( this_grid ) );

        this_grid->cell[startRow][startCol] = to_process;

        // First pass: mark to_process and processed.
        {
                uint8_t foundPointsToProcess;

                do
                {
                        foundPointsToProcess = 0;
                        {
                                int8_t row = this_grid->dimensions.row;

                                while ( --row >= 0 )
                                {
                                        int8_t col = this_grid->dimensions.col;

                                        while ( --col >= 0 )
                                        {
                                                cf_cellState_t localState = this_grid->cell[row][col];

                                                if ( localState == to_process )
                                                {
                                                        foundPointsToProcess = true;
                                                        //this_grid->cell[row][col] = processed; redundant

                                                        walkTillObstacle( this_grid, row, col, oldState, 1 );
                                                        walkTillObstacle( this_grid, row, col, oldState, -1 );
                                                }
                                        }
                                }
                        }
                }
                while ( foundPointsToProcess != 0 );

                // Could be optimized for speed by not looping all grid each time.
        }

        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 2, cf_grid_draw( this_grid ) );
}

//Second pass: mark processed to newstate and count them.


uint16_t finishFillAndcountArea( cf_grid_t *this_grid,
                                 cf_cellState_t newState )
{
        uint16_t newArea = 0;

        int8_t row = this_grid->dimensions.row;

        while ( --row >= 0 )
        {
                int8_t col = this_grid->dimensions.col;

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

        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 2, cf_grid_draw( this_grid ) );
        silmsg( 2, "== return %d ==" NL, newArea );

        return newArea;
}

/** Return value: 0 if played okay, 1 if game ended, 2 if color chosen was not allowed. */
uint8_t cf_model_play( cf_model_t *const this_model, cf_cellState_t const newState )
{
        cf_player_i iplayer;
        cf_cellState_t oldState;
        cf_coordinates_t *fillStartCoordinates;
        cf_grid_t *grid = &this_model->grid;

        if ( !cf_model_is_color_allowed_for_current_player( this_model, newState ) )
        {
                return 2;
        }

        iplayer = this_model->nextPlayer;

        fillStartCoordinates = &( this_model->playerHomes[iplayer] );
        oldState = grid->cell[fillStartCoordinates->row][fillStartCoordinates->col];

        /* silmark( 2 ); */
        /* dbgvar_d( 2, iplayer ); */

        fillColorToProcessedState( grid,
                                   fillStartCoordinates->row,
                                   fillStartCoordinates->col,
                                   oldState );

        finishFillAndcountArea( grid, newState );

        fillColorToProcessedState( grid,
                                   fillStartCoordinates->row,
                                   fillStartCoordinates->col,
                                   newState );

        {
                uint16_t newDomainArea = finishFillAndcountArea( grid,
                                         newState );
                dbglogf( 2, "New area for player %d: %d" NL, iplayer, newDomainArea );
                this_model->domainAreas[iplayer] = newDomainArea;
        }

        {
                uint16_t unclaimedArea = grid->dimensions.row * grid->dimensions.col;

                for ( iplayer = 0; iplayer < CF_MAXPLAYERCOUNT; iplayer++ )
                {
                        if ( is_player_enabled( this_model, iplayer ) )
                        {
                                unclaimedArea -= this_model->domainAreas[iplayer];
                        }
                }

                dbgvar_d( 2, unclaimedArea );

                if ( unclaimedArea == 0 )
                {
                        return 1;
                }
        }

        return 0;
}

cf_cellState_t cf_model_get_player_cellstate( const cf_model_t *const this_model, cf_player_i const iplayer )
{
        const cf_coordinates_t *player_home = &( this_model->playerHomes[iplayer] );
        const cf_cellState_t state = this_model->grid.cell[player_home->row][player_home->col];
        return state;
}

void cf_model_update_allowed_color_table( cf_model_t *const this_model )
{
        // All colors allowed a priori.
        cf_onebitpercolor_t bits = ( ( 1 << CF_COLORCOUNT ) - 1 ) ;

        cf_player_i iplayer;

        for ( iplayer = 0; iplayer < CF_MAXPLAYERCOUNT; iplayer++ )
        {
                if ( is_player_disabled( this_model, iplayer ) )
                {
                        continue;
                }

                {
                        cf_coordinates_t *fillStartCoordinates = &( this_model->playerHomes[iplayer] );
                        cf_cellState_t iplayer_state = this_model->grid.cell[fillStartCoordinates->row][fillStartCoordinates->col];

                        bits &= ~( 1 << iplayer_state );
                }
        }

        this_model->allowedNextColorBits = bits;
}

//#define cf_model_is_color_allowed_for_current_player( const cf_model_t *const this_model, cf_cellState_t new_state )

bool cf_model_is_color_allowed_for_current_player( const cf_model_t *const this_model, const cf_cellState_t new_state )
{
        cf_onebitpercolor_t bits = this_model->allowedNextColorBits;

        return ( bits & ( 1 << new_state ) ) != 0;
}
