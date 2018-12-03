#include <cfwi/cfwi.h>

#include "platform.h"

#ifdef DEBUG

void cf_pause()
{
        cfwi_txt_str0_output( "?" );
        fw_km_wait_key();
}

void cf_pause_message( char *msg )
{
        cfwi_txt_str0_output( msg );
        fw_km_wait_key();
}

#endif
