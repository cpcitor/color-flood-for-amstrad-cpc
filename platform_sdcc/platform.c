#include "platform.h"
#include "screen.h"
#include "../log.h"
#include "stdlib.h"

#include <cfwi/cfwi.h>

#include "platform_view.h"

enum { ink_count = 16 };
const uint8_t const inks[ink_count] =
{
        0, 26,
        rgb_to_cpc_color( 2, 0, 0 ),
        rgb_to_cpc_color( 2, 1, 0 ),
        //rgb_to_cpc_color( 2, 2, 0 ), yellow is too close to green
        rgb_to_cpc_color( 0, 2, 0 ), // not 0,2,1 too bright
        rgb_to_cpc_color( 0, 2, 2 ),
        rgb_to_cpc_color( 0, 0, 2 ), // not 0,1,2 which would be too similar to 1,0,2
        //rgb_to_cpc_color( 1, 0, 2 ), too similar to 0,0,2 on a real CPC

        // rgb_to_cpc_color( 2, 0, 1 ), too aggressive
        //rgb_to_cpc_color( 1, 2, 0 ), too similar to 0,2,1

        rgb_to_cpc_color( 2, 0, 2 ),

//        rgb_to_cpc_color( 1, 0, 1 ), too similar to 1,0,2
        rgb_to_cpc_color( 0, 1, 1 ),
        rgb_to_cpc_color( 1, 1, 0 ),
        rgb_to_cpc_color( 1, 0, 1 ),
        /* #if CF_PASTEL_COLORS */
        /*         16, 25, 22, 23, 14, 17, */
        /* #else /\* CF_PASTEL_COLORS *\/ */
        /*         6, 24, 18, 20, 2, 8, */
        /* #endif /\* CF_PASTEL_COLORS *\/ */
        /*        15, 13,
                  3, 12, 9, 10, 1, 4*/
};

void cf_platform_init()
{
        fw_scr_initialise();
        fw_gra_initialise();
        fw_scr_set_mode( 1 );

        {
                long unsigned int cpctime = fw_kl_time_please();
                dbgvar_lu( 0, cpctime );
                srand( cpctime );
        }
}

void cf_platform_prepare_for_game_board()
{
        fw_scr_set_mode( 0 );
        fw_txt_initialise();

        cf_screen_line_to_ptr_init();

        {
                uint8_t i;

                for ( i = 0; i < ink_count; i++ )
                {
                        uint8_t color = inks[i];
                        fw_scr_set_ink_one( i, color );
                }

                fw_scr_set_border( 0, 0 );
        }

}
