#include "platform.h"
#include "log.h"
#include "model.h"
#include "model_test.h"
#include "view.h"
#include "platform_ui.h"

int
main()
{
        dbglog( "In C" NL );

        cf_platform_init();

        global_model.playerCount = 2;

        model_test_fill();

        {
                uint8_t size;

                for ( size = 1; size <= CF_MAXGRIDSIZE; size++ )
                {
                        //dbglogf( "Next %d", size );
                        //cf_pause();

                        global_model.grid.dimensions.row = size;
                        global_model.grid.dimensions.col = global_model.grid.dimensions.row;

                        cf_model_init( &global_model );

                        cf_model_draw( &global_model );
                }

                //dbglog( "drawn" NL );
                //cf_pause();
        }

        silmsg( "Returning." );
        return 0;
}
