#include "model_podium.h"
#include "log.h"
#include <string.h>


void cf_model_podium_init( cf_podium_t *this_podium )
{
        uint8_t irow;

        memset( this_podium, CF_PODIUM_EMPTY_SEATS_VALUE, sizeof( cf_podium_t ) );

        for ( irow = 0; irow < CF_PODIUM_ROW_COUNT; irow++ )
        {
                this_podium->row[irow].area = 0;
        }
}

cf_podium_row_t *cf_model_podium_insert_row( cf_podium_t *const this_podium, uint16_t area, uint8_t irow )
{
        const uint8_t const number_of_rows_to_copy = CF_PODIUM_ROW_COUNT - irow - 1;
        cf_podium_row_t *const where_new_row_will_be = &( this_podium->row[irow] );

        // dbglogf_unconditional( "Copying %d rows from %d to %d\n", number_of_rows_to_copy, irow, irow + 1 );

        // cf_view_print_podium( this_podium );

        if ( number_of_rows_to_copy > 0 )
        {
                cf_podium_row_t *const where_shifted_row_goes = where_new_row_will_be + 1;
                memmove( where_shifted_row_goes, where_new_row_will_be, number_of_rows_to_copy * sizeof( cf_podium_row_t ) );
        }

        // dbglog_unconditional( "After memcopy" );
        // cf_view_print_podium( this_podium );

        {
                cf_podium_row_t *const new_row = where_new_row_will_be;
                // The memset() below also overwrites the area field,
                // which is okay, we write it just after.
                memset( new_row, CF_PODIUM_EMPTY_SEATS_VALUE, sizeof( cf_podium_row_t ) );
                new_row->area = area;
                return new_row;
        }
}

void cf_model_podium_add_player_at_row( cf_podium_row_t *const this_row, const cf_player_i iplayer )
{
        cf_player_i *seat = &( this_row->seat[0] );

        uint8_t iseat = 0;

        // dbglogf_unconditional( "Inserting player %d in row with score %d\n", iplayer, this_row->area );

        for ( iseat = 0; iseat < CF_PODIUM_SEATS_PER_ROW; iseat++ )
        {
                if ( ( *seat ) == CF_PODIUM_EMPTY_SEATS_VALUE )
                {
                        ( *seat ) = iplayer;
                        // dbglogf_unconditional( "Inserted at position %d\n", iseat );
                        return;
                }

                ++seat;
        }

        dbglog_unconditional( "Podium row overflow." );
}

void cf_model_podium_compute( cf_podium_t *const this_podium, const cf_model_t *const this_model )
{
//        cf_model_podium_init();

        cf_player_i iplayer;

        for ( iplayer = 0; iplayer < CF_MAXPLAYERCOUNT; iplayer++ )
        {
                uint16_t this_player_area = this_model->domainAreas[iplayer];

                if ( is_player_enabled( this_model, iplayer ) )
                {
                        /** First row we're strictly above -> insert new row. */
                        /** First row we're equal -> add to row. */
                        int irow;

                        for ( irow = 0; irow < CF_PODIUM_ROW_COUNT; irow++ )
                        {
                                cf_podium_row_t *row = &this_podium->row[irow];
                                uint16_t this_row_area = row->area;

                                if ( this_player_area < this_row_area )
                                {
                                        // dbglogf_unconditional( "player %d score %d does not fit in row %d of score %d\n",
                                        //              iplayer, this_player_area, irow, this_row_area );
                                        continue;
                                }

                                if ( this_player_area > this_row_area )
                                {
                                        // dbglogf_unconditional( "player %d score %d needs insertion before row %d of score %d\n",
                                        //                     iplayer, this_player_area, irow, this_row_area );
                                        cf_model_podium_insert_row( this_podium, this_player_area, irow );
                                        // Actually, local variable row already holds the return value of cf_model_podium_insert_row.
                                }

                                // Whether we reach an existing row, or inserted one, we add our player here.
                                cf_model_podium_add_player_at_row( row, iplayer );
                                break; // next player
                        }
                }
        }
}
