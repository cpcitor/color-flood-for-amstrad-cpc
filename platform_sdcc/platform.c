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
#if CF_PASTEL_COLORS
        16, 25, 22, 23, 14, 17,
#else /* CF_PASTEL_COLORS */
        6, 24, 18, 20, 2, 8,
#endif /* CF_PASTEL_COLORS */
        15, 13,
        3, 12, 9, 10, 1, 4
};

void cf_platform_init()
{
        fw_scr_initialise();
        fw_scr_set_mode( 0 );

        cf_screen_line_to_ptr_init();

        {
                uint8_t i;

                for ( i = 0; i < ink_count; i++ )
                {
                        uint8_t color = inks[i];
                        fw_scr_set_ink( i, color, color );
                }

                fw_scr_set_border( 0, 0 );
        }

        {
                long unsigned int cpctime = fw_kl_time_please();
                dbgvar_lu( 0, cpctime );
                srand( cpctime );
        }

        show_key_color_association();
}
