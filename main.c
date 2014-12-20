#include "model.h"
#include "view.h"

int main()
{
        dbglog( "In C" NL );
        //dbglogf( "sizeof(cf_model_t) = %lud" NL, sizeof( cf_model_t ) );

        {
                cf_model_t model;

                model.playerCount = 2;
                model.grid.dimensions.row = 12;
                model.grid.dimensions.col = 12;

                cf_model_init( &model );

                cf_model_draw( &model );
                cf_model_dump( &model );
        }

        dbglog( "Returning..." NL );
        return 0;
}
