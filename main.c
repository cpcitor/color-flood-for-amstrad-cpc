#include "platform.h"
#include "model.h"
//#include "model_test.h"
#include "view.h"
#include "platform_ui.h"

int
main()
{
        dbglog( "In C" NL );

        cf_platform_init();

        model.playerCount = 2;

        model_test_fill();

        {
                uint8_t size;

                for ( size = 1; size <= CF_MAXGRIDSIZE; size++ )
                {
                        //dbglogf( "Next %d", size );
                        //pause();

                        model.grid.dimensions.row = size;
                        model.grid.dimensions.col = model.grid.dimensions.row;

                        cf_model_init( &model );

                        cf_model_draw( &model );
                }

                //dbglog( "drawn" NL );
                //pause();
        }

        dbglog( "Returning..." NL );
        return 0;
}
