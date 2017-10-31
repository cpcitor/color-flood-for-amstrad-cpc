#include "platform.h"
#include "welcome.h"
#include "log.h"
#include "model.h"
#include "model_podium.h"
#include "model_test.h"
#include "view.h"
#include "platform_ui.h"

#include "controller.h"

int
main()
{
        dbglog( 0, "In C" NL );

        cf_platform_init();

        welcome();

        global_model.playerEnableBits = 0b0101;

        do
        {
                cf_platform_prepare_for_game_board();

                {
                        const uint8_t size = 12;

                        global_model.grid.dimensions.row = size;
                        global_model.grid.dimensions.col = global_model.grid.dimensions.row;
                }

                cf_model_init( &global_model );

                cf_view_init( &global_model );

                cf_rungame( &global_model );

                {
                        cf_podium_t podium;
                        cf_model_podium_init( &podium );
                        cf_model_podium_compute( &podium, &global_model );

                        if ( !cf_view_display_endgame_should_we_play_again( &global_model, &podium ) )
                        {
                                break ;
                        }
                }
        }
        while ( true );

        silmsg( 0, "Returning to BASIC." );
        return 0;
}
