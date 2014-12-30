#include "log.h"
#include "platform.h"
#include "platform_ui.h"
#include "platform_view.h"
#include "model_test.h"

void model_test_fill_22()
{
        silmsg( 1, "Test begin" );
        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 1, cf_pause() );

        global_model.playerCount = 1;
        global_model.grid.dimensions.row = 2;
        global_model.grid.dimensions.col = 2;

        cf_model_init( &global_model );

        global_model.grid.cell[0][0] = 0;
        global_model.grid.cell[0][1] = 0;
        global_model.grid.cell[1][0] = 0;
        global_model.grid.cell[1][1] = 1;

        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 1, cf_model_draw( &global_model ) );

        cf_model_play( &global_model, 2 );

        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 1, cf_model_draw( &global_model ) );
        silmsg( 1, "Test end" );
        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 1, cf_pause() );
}

void model_test_fill_fork()
{
        silmsg( 1, "Test begin" );
        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 1, cf_pause() );

        global_model.playerCount = 1;
        global_model.grid.dimensions.row = 7;
        global_model.grid.dimensions.col = 7;

        cf_model_init( &global_model );

        global_model.grid.cell[0][0] = 0;
        global_model.grid.cell[0][1] = 0;
        global_model.grid.cell[0][2] = 0;
        global_model.grid.cell[0][3] = 1;
        global_model.grid.cell[0][4] = 0;
        global_model.grid.cell[0][5] = 0;
        global_model.grid.cell[0][6] = 0;

        global_model.grid.cell[1][0] = 0;
        global_model.grid.cell[1][1] = 2;
        global_model.grid.cell[1][2] = 0;
        global_model.grid.cell[1][3] = 1;
        global_model.grid.cell[1][4] = 0;
        global_model.grid.cell[1][5] = 2;
        global_model.grid.cell[1][6] = 0;

        global_model.grid.cell[2][0] = 0;
        global_model.grid.cell[2][1] = 1;
        global_model.grid.cell[2][2] = 2;
        global_model.grid.cell[2][3] = 1;
        global_model.grid.cell[2][4] = 2;
        global_model.grid.cell[2][5] = 1;
        global_model.grid.cell[2][6] = 0;

        global_model.grid.cell[3][0] = 0;
        global_model.grid.cell[3][1] = 0;
        global_model.grid.cell[3][2] = 0;
        global_model.grid.cell[3][3] = 0;
        global_model.grid.cell[3][4] = 0;
        global_model.grid.cell[3][5] = 0;
        global_model.grid.cell[3][6] = 0;

        global_model.grid.cell[4][0] = 2;
        global_model.grid.cell[4][1] = 0;
        global_model.grid.cell[4][2] = 1;
        global_model.grid.cell[4][3] = 0;
        global_model.grid.cell[4][4] = 2;
        global_model.grid.cell[4][5] = 0;
        global_model.grid.cell[4][6] = 1;

        global_model.grid.cell[5][0] = 0;
        global_model.grid.cell[5][1] = 2;
        global_model.grid.cell[5][2] = 0;
        global_model.grid.cell[5][3] = 0;
        global_model.grid.cell[5][4] = 0;
        global_model.grid.cell[5][5] = 1;
        global_model.grid.cell[5][6] = 0;

        global_model.grid.cell[6][0] = 0;
        global_model.grid.cell[6][1] = 0;
        global_model.grid.cell[6][2] = 0;
        global_model.grid.cell[6][3] = 0;
        global_model.grid.cell[6][4] = 0;
        global_model.grid.cell[6][5] = 0;
        global_model.grid.cell[6][6] = 0;

        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 1, cf_model_draw( &global_model ) );
        silmsg( 1, "Will fill" );
        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 1, cf_pause() );

        cf_model_play( &global_model, 1 );

        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 1, cf_model_draw( &global_model ) );

        silmsg( 1, "Test end" );
        CDTC_ON_DEBUGLEVEL_GREATER_THAN( 1, cf_pause() );
}

void model_test_fill()
{
        model_test_fill_22();
        model_test_fill_fork();
}
