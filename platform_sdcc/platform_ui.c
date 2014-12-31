#include <cfwi/cfwi.h>

#include "platform.h"

void cf_pause()
{
        cfwi_txt_str0_output( "?" );
        fw_km_wait_key();
}
