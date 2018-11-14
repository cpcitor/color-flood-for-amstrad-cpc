#include "platform.h"
#include "welcome.h"
#include "log.h"
#include "model.h"
#include "model_podium.h"
#include "view.h"
#include "platform_ui.h"
#include "platform_view.h"
#include "widget_classes.h"

#include "controller.h"

int
main()
{
        dbglog( 0, "In C. Compiled with CF_DEBUGLEVEL=" CF_DEBUGLEVEL_STRINGIFIED NL );

        cf_platform_init();

        global_model.playerEnableBits = ( 1 << 0 ) | ( 1 << 2 );

        {
                const uint8_t size = 12;

                global_model.grid.dimensions.row = size;
                global_model.grid.dimensions.col = global_model.grid.dimensions.row;
        }

        do
        {
                welcome();

                if ( global_model.playerEnableBits == 0 )
                {
                        break;
                }

                cf_platform_prepare_for_game_board();

                cf_model_init( &global_model );

                cf_view_init( &global_model );

                {
                    uint8_t moveResult;
                    while ( (moveResult = cf_game_one_move( &global_model )) )
                    {
                        if (moveResult==2) // Esc pressed
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

                            {
                                unsigned char keycode = platform_wait_for_key();
                                dbgvar_d( 5, keycode );

                                if (keycode =='q')
                                {
                                        break; // abort game
                                }
                            }
                        }
                    }
                }

                {
                        cf_podium_t podium;
                        cf_model_podium_init( &podium );
                        cf_model_podium_compute( &podium, &global_model );

                        cf_view_display_endgame_pause( &global_model, &podium );
                }
        }
        while ( true );

        //silmsg( 0, "Returning to BASIC." );
        platform_print_plain_string( "Exiting C." NL );
        return 0;
}
