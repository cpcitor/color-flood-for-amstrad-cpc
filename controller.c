#ifdef SDCC
// Hack necessary to enable auto-enable link with cfwi.
#include <cfwi/cfwi.h>
#endif /* SDCC */

#include "controller.h"
#include "view.h"
#include "../log.h"

const key_to_action_t const key_to_action[key_to_action_count] =
{
        { 's', -1, 0 },
        { 'd', -1, 1 },
        { 'f', -1, 2 },
        { 'g', -1, 3 },
        { 'h', -1, 4 },
        { 'j', -1, 5 },
#if CF_COLORCOUNT > 6
        { 'k', -1, 6 },
        { 'l', -1, 7 },
        { '0', -1, 8 },
        { '1', -1, 9 },
        { '2', -1, 10 },
        { '3', -1, 11 },
        { '4', -1, 12 },
        { '5', -1, 13 },
        { 'e', 0, -1 },
        { 'c', 1, -1 },
        { 'n', 2, -1 },
        { 'p', 3, -1 },
#endif
};

/*
enum {key_to_action_count = CF_MAXPLAYERCOUNT * CF_COLORCOUNT };

key_to_action_t key_to_action[key_to_action_count] =
{
        { 'e', 0, 0 },
        { 'r', 0, 1 },
        { 't', 0, 2 },
        { 'y', 0, 3 },
        { 'u', 0, 4 },
        { 'i', 0, 5 },
        { '1', 1, 0 },
        { '2', 1, 1 },
        { '3', 1, 2 },
        { '4', 1, 3 },
        { '5', 1, 4 },
        { '6', 1, 5 }
        { 's', 2, 0 },
        { 'd', 2, 1 },
        { 'f', 2, 2 },
        { 'g', 2, 3 },
        { 'h', 2, 4 },
        { 'j', 2, 5 },
        { '7', 3, 0 },
        { '8', 3, 1 },
        { '9', 3, 2 },
        { 'x', 3, 3 },
        { 'c', 3, 4 },
        { 'v', 3, 5 }
};
*/

/** TODO FIXME Return id of player that won. */
uint8_t cf_rungame( cf_model_t *const this_model )
{
        //cf_model_draw( &global_model );
        // wait for key
        while ( 1 )
        {
                platform_prompt_next_move( this_model );
                {
#ifdef SDCC
                        char user_choice_char = fw_km_wait_key();
#else
                        printf( "Enter you choice:\n" );
                        char user_choice_char = getchar();
#endif /* SDCC */
                        const key_to_action_t *ktap = key_to_action + key_to_action_count;

                        dbgvar_d( 1, user_choice_char );
                        dbglog_nl( 1 );

                        do
                        {
                                ktap--;

                                if ( ktap->character != user_choice_char )
                                {
                                        dbglogf( 4, "!%03d ", ktap->character );
                                        continue;
                                }

                                dbgvar_d( 1, user_choice_char );
                                dbglog_nl( 1 );

                                /* if ( ktap->player != this_model->nextPlayer ) */
                                /* { */
                                /*         continue; */
                                /* } */

                                {
                                        uint8_t rv = cf_model_play( this_model, ktap->color );

                                        if ( rv == 1 )
                                        {
                                                cf_model_draw( &global_model );
                                                return 0;
                                        }

                                        if ( rv >= 2 )
                                        {
                                                dbglogf( 1, "%d!", rv );
                                        }
                                }
                                //cf_model_play( this_model, ktap->color );
                                cf_model_draw( &global_model );
                        }
                        while ( ktap != key_to_action );
                }
        }
}
