#include "platform.h"
#include "log.h"
#include "model.h"
#include "model_test.h"
#include "view.h"
#include "platform_ui.h"

int
main()
{
        dbglog( 0, "In C" NL );

        cf_platform_init();

        global_model.playerCount = 2;

        {
                const uint8_t size = 12;

                global_model.grid.dimensions.row = size;
                global_model.grid.dimensions.col = global_model.grid.dimensions.row;

                cf_model_init( &global_model );

                cf_model_draw( &global_model );

                {
                        uint8_t count = 6 * CF_COLORCOUNT;

                        while ( count-- > 0 )
                        {
                                cf_model_play( &global_model, count % CF_COLORCOUNT );
                                cf_model_draw( &global_model );
                                CDTC_ON_DEBUGLEVEL_GREATER_THAN( 1, cf_pause() );
                        }
                }

        }

        silmsg( 0, "Returning to BASIC." );
        return 0;
}
