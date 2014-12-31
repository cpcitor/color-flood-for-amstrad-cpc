#include "platform.h"
#include "screen.h"
#include "../log.h"
#include "stdlib.h"

#include <cfwi/cfwi.h>

void cf_platform_init()
{
        cf_screen_line_to_ptr_init();


        {
                long unsigned int cpctime = fw_kl_time_please();
                long unsigned int seed = cpctime ^ ( cpctime >> 16 );
                dbgvar_lu( 0, cpctime );
                dbgvar_u( 0, seed );
                srand( seed );
        }

}
