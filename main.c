#include <stdio.h>

#include "model.h"

int main()
{
        printf( "Hello World, hello stephane.\n" );

        {
                cf_model_t model;

                model.playerCount = 2;
                model.grid.dimensions.row = 12;
                model.grid.dimensions.col = 12;

                cf_model_init( &model );

                cf_model_dump( &model );

                printf( "Program end.\n" );

                return 0;
        }
}
