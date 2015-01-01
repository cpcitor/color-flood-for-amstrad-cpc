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
                dbgvar_lu( 0, cpctime );
                srand( cpctime );
        }

}
