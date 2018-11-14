#ifdef SDCC
// Hack necessary to enable auto-enable link with cfwi.
#include <cfwi/cfwi.h>
#endif /* SDCC */

#include "controller.h"
#include "view.h"
#include "../log.h"
#include "widget_classes.h"

const player_key_to_action_t const player_key_to_action_array[CF_MAXPLAYERCOUNT] =
{
        {'e', 'r', 't'},
        {0x87, 0x88, 0x89},
        {0x81, 0x82, 0x83},
        {'v', 'b', 'n'},
//        {'i', 'o', 'p'},
//        {0x89 /* f9 */ , 0x86 /* f6 */ , 0x83 /* f3 */ },
//        {'v', 'b', 'n'},
};

uint8_t
cf_game_one_move( cf_model_t *const this_model )
{
        cf_model_draw( this_model );

        {
                cf_player_i iplayer = this_model->nextPlayer;

                while ( is_player_disabled( this_model, iplayer ) )
                {
                        iplayer = ( iplayer + 1 ) % CF_MAXPLAYERCOUNT;
                }

                this_model->nextPlayer = iplayer;
        }

        platform_show_who_plays_next( this_model );
        cf_model_update_allowed_color_table( this_model );

        {
                cf_cellState_t player_wished_color = platform_show_possible_next_moves( this_model );
                const player_key_to_action_t *const player_key_to_action = &( player_key_to_action_array[this_model->nextPlayer] );

                {
                        unsigned char keycode = 0;

                        do
                        {
                                platform_show_player_wished_color( player_wished_color );
                                keycode = platform_wait_for_key();
                                dbgvar_d( 5, keycode );

                                if ( keycode == player_key_to_action->previous_color )
                                {
                                        dbglog( 5, "User chose 'previous'" NL );

                                        do
                                        {
                                                player_wished_color = color_previous( player_wished_color );
                                                dbgvar_d( 5, player_wished_color );
                                        }
                                        while ( !cf_model_is_color_allowed_for_current_player( this_model, player_wished_color ) );
                                }

                                if ( keycode == player_key_to_action->next_color )
                                {
                                        dbglog( 5, "User chose 'next'" NL );

                                        do
                                        {
                                                player_wished_color = color_next( player_wished_color );
                                                dbgvar_d( 5, player_wished_color );
                                        }
                                        while ( !cf_model_is_color_allowed_for_current_player( this_model, player_wished_color ) );
                                }

                                //platform_print_formatted_string("%d", keycode);

                                if (keycode == 252)
                                {
                                    const int left = 1;
                                    const int right = 12;
                                    const int top = 10;
                                    const int bottom = 15;
                                    draw_window( "Quit?", top, bottom, left, right );
                                    platform_move_cursor( top + 1 , left + 1 );
                                    platform_print_plain_string( "Press q   ");
                                    platform_move_cursor( top + 2 , left + 1 );
                                    platform_print_plain_string( "to quit,  " );
                                    platform_move_cursor( top + 3 , left + 1 );
                                    platform_print_plain_string( "any other " );
                                    platform_move_cursor( top + 4 , left + 1 );
                                    platform_print_plain_string( "continues." );

                                    keycode = platform_wait_for_key();
                                    dbgvar_d( 5, keycode );

                                    if (keycode =='q')
                                    {
                                        return 0;
                                    }

                                    cf_model_draw( this_model );
                                }
                        }
                        while ( keycode != player_key_to_action->confirm );
                }

                dbgvar_d( 5, player_wished_color );
                dbglog_nl( 5 );

                platform_hide_who_plays_next( this_model );

                {
                        uint8_t rv = cf_model_play( this_model, player_wished_color );

                        if ( rv == 1 )
                        {
                                //cf_model_draw( &global_model );
                                return 0;
                        }

                        if ( rv >= 2 )
                        {
                                dbglogf( 1, "%d!", rv );
                        }
                }
        }

        return 1;
}
