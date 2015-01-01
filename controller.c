#ifdef SDCC
// Hack necessary to enable auto-enable link with cfwi.
#include <cfwi/cfwi.h>
#endif /* SDCC */

#include "controller.h"
#include "platform_view.h"
#include "../log.h"

typedef struct key_to_action_t
{
        char character;
        uint8_t player;
        cf_cellState_t color;
} key_to_action_t;

enum {key_to_action_count = CF_COLORCOUNT };

const key_to_action_t const key_to_action[key_to_action_count] =
{
        { 's', 2, 0 },
        { 'd', 2, 1 },
        { 'f', 2, 2 },
        { 'g', 2, 3 },
        { 'h', 2, 4 },
        { 'j', 2, 5 },
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

/** Return value: 0 if okay, 1+playerindex if color chosen was same as playerindex' current color. */
uint8_t cf_rungame( cf_model_t *const this_model )
{
        //cf_model_draw( &global_model );
        // wait for key
        while ( 1 )
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

                                if ( rv != 0 )
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
